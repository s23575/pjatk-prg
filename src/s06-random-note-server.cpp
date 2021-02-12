#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

//#include <fcntl.h>
//#include <sys/socket.h>
//#include <sys/stat.h>
//#include <sys/types.h>
//#include <sys/select.h>
//#include <errno.h>
//#include <stdio.h>

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

auto losowa_wiadomosc(std::vector<std::string> const wiadomosci) -> std::string
{
    std::random_device rd;
    std::uniform_int_distribution<int> losowa_liczba(0, wiadomosci.size() - 1);

    auto const wylosowana_liczba = losowa_liczba(rd);

    auto wiadomosc = std::string{wiadomosci[wylosowana_liczba]};

    return wiadomosc;
}

auto main_loop(int const server_sock) -> void
{
    auto clients = std::vector<int>{};
    auto msg     = std::vector<std::string>{};

    // Ograniczenie czasowe, żeby serwer nie działał bez końca (limit ustawiony
    // na 30 sek.).

    auto poczatek_czasu = std::chrono::steady_clock::now();
    auto i              = int{30};

    while (true) {
        auto biezacy_czas = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(biezacy_czas
                                                             - poczatek_czasu)
                .count()
            >= i) {
            if (clients.size() > 0) {
                i += 30;
            } else {
                break;
            }
        }

        auto client_sock =
            accept4(server_sock, nullptr, nullptr, SOCK_NONBLOCK);

        if (client_sock == -1) {
        } else {
            std::cout << "got new client! client No. " << client_sock << "\n";
            clients.push_back(client_sock);
        }

        for (auto i = unsigned{0}; i < clients.size(); i++) {
            auto wielkosc = int{4096};
            auto buf      = std::string{};
            buf.resize(wielkosc);

            auto const n = read(clients[i], buf.data(), buf.size());

            if (n == -1) {
            } else if (n == 0) {
                // Kiedy klient się rozłącza (CTRL+C po stronie klienta),
                // program zwracam n == 0, nie n == -1. Jeżeli klient się
                // odłączył, to jest on usuwany z wektora klientów.

                std::cout << "no more data from client No. " << clients[i]
                          << "\n";
                shutdown(clients[i], SHUT_RDWR);
                close(clients[i]);
                clients.erase(clients.begin() + i);
                i--;

            } else {
                std::cout << "got from client No. " << clients[i] << " : "
                          << std::string{buf.data(), static_cast<size_t>(n)};
                msg.push_back(buf.data());

                auto wiadomosc = std::string{losowa_wiadomosc(msg)};

                write(clients[i], wiadomosc.data(), wiadomosc.size());
            }
        }
    }
}

auto main() -> int
{
    auto server_sock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    auto const ip   = std::string{"127.0.0.1"};
    auto const port = uint16_t{8080};

    {
        auto const opt = int{1};
        setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        setsockopt(server_sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    }

    sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htobe16(port);
    inet_pton(addr.sin_family, ip.c_str(), &addr.sin_addr);

    bind(server_sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    listen(server_sock, SOMAXCONN);
    std::cout << "listening on " << ip << ": " << port << "\n";

    main_loop(server_sock);

    std::cout << "no (more) data from any client (shutdown)\n";

    shutdown(server_sock, SHUT_RDWR);
    close(server_sock);

    return 0;
}
