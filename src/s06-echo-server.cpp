#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>

auto serwer() -> std::string
{
    auto sock = socket(AF_INET, SOCK_STREAM, 0);

    auto const ip = std::string{"127.0.0.1"};

    auto const port = uint16_t{8080};

    sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htobe16(port);
    inet_pton(addr.sin_family, ip.c_str(), &addr.sin_addr);

    const int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

    bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

    listen(sock, SOMAXCONN);

    auto client_sock = accept(sock, nullptr, nullptr);

    auto wielkosc = int{1024};
    auto buf      = std::string{};
    buf.resize(wielkosc);

    auto n = read(client_sock, &buf[0], buf.size());
    if (n == -1) {
        perror("read(2)");
    }

    shutdown(sock, SHUT_RDWR);

    close(sock);

    return buf;
}

auto klient(std::string buf2) -> std::string
{
    auto sock = socket(AF_INET, SOCK_STREAM, 0);

    auto const ip = std::string{"127.0.0.2"};

    auto const port = uint16_t{8181};

    sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htobe16(port);
    inet_pton(addr.sin_family, ip.c_str(), &addr.sin_addr);

    const int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

    auto server_sock =
        connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));


    while (server_sock == -1) {
        server_sock =
            connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    }
    //        perror("connect(2)");


    auto n = write(sock, &buf2[0], buf2.size());
    if (n == -1) {
        perror("write(2)");
    }

    shutdown(sock, SHUT_RDWR);

    close(sock);

    return buf2;
}

auto main() -> int
{
    auto str = std::string{serwer()};

    std::cout << "Odebrano wiadomość: " << str << "\n";

    auto str2 = std::string{str.append(" (wiadomość odsyłana)")};

    std::cout << "Wiadomość wysłana: " << klient(str2) << "\n";

    return 0;
}
