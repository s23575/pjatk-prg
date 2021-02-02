#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

auto main() -> int
{
    auto client_sock = socket(AF_INET, SOCK_STREAM, 0);

    auto const ip   = std::string{"127.0.0.1"};
    auto const port = uint16_t{8080};

    {
        auto const opt = int{1};
        setsockopt(client_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        setsockopt(client_sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    }

    sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htobe16(port);
    inet_pton(addr.sin_family, ip.c_str(), &addr.sin_addr);

    auto const m =
        connect(client_sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    if (m == -1) {
        perror("connect(2) ");
    } else {
        std::cout << "connected to " << ip << ": " << port << "\n";

        while (true) {
            auto buf = std::string{};
            std::cout << "send to server : ";
            std::getline(std::cin, buf);
            buf.append("\n");

            write(client_sock, buf.data(), buf.size());

            auto buf2     = std::string{};
            auto wielkosc = int{4096};
            buf2.resize(wielkosc);

            auto const n = read(client_sock, buf2.data(), buf2.size());
            std::cout << "got from server"
                      << " : "
                      << std::string{buf2.data(), static_cast<size_t>(n)};
        }

        shutdown(client_sock, SHUT_RDWR);
        close(client_sock);
    }

    return 0;
}
