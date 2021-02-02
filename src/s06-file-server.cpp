#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

//#include <sys/socket.h>
//#include <sys/types.h>
//#include <sys/select.h>
//#include <errno.h>
//#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

auto open_and_send_file(std::string nazwa_pliku) -> std::string
{
    auto zawartosc = std::string{};

    nazwa_pliku.pop_back();

    auto fd = open(nazwa_pliku.c_str(), O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open(2) ");
    } else {
        struct stat info;
        memset(&info, 0, sizeof(info));
        auto const r = fstat(fd, &info);

        if (r == -1) {
            perror("fstat(2) ");
        } else {
            auto buf = std::string{};
            buf.resize(info.st_size);
            auto const n = read(fd, buf.data(), buf.size());

            if (n == -1) {
                perror("read(2) ");
            } else {
                close(fd);
                zawartosc = nazwa_pliku;
                zawartosc.append("\n");
                zawartosc.append(buf);
                zawartosc.append("\n");
            }
        }
    }

    return zawartosc;
}

auto main_loop(int const server_sock) -> void
{
    auto clients = std::vector<int>{};

    // Ograniczenie czasowe, żeby serwer nie działał bez końca (limit ustawiony
    // na 30 sek.).

    auto koniec_czasu = time_t{};
    auto czas_sek     = int{30};
    koniec_czasu      = time(NULL) + czas_sek;

    while (time(NULL) < koniec_czasu) {
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

                auto zawartosc_pliku =
                    std::string{open_and_send_file(buf.data())};

                if (zawartosc_pliku.size() == 0) {
                    zawartosc_pliku = ":-(\n";
                }
                write(
                    clients[i], zawartosc_pliku.data(), zawartosc_pliku.size());
            }
        }

        // Jeżeli klienci są podłączeni, czas działania serwera się zwiększa (o
        // kolejne 30 sek.).

        if (clients.size() > 0) {
            koniec_czasu = time(NULL) + czas_sek;
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
