#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cerr << "Błąd! W wierszu poleceń nie podano argumentu (nazwy "
                     "pliku do odczytu).\n";
        return 1;
    }

    auto const nazwa_pliku = std::string{argv[1]};
    auto fd = open(nazwa_pliku.c_str(), O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        std::cerr << "Błąd! Plik o podanej nazwie nie istnieje.\n";
        return 1;
    }

    // Sprawdzenie wielkości pliku

    struct stat info;
    memset(&info, 0, sizeof(info));
    auto const r = fstat(fd, &info);
    if (r == -1) {
        perror("stat(2)");
    }

    // Zapisanie zawartości pliku do std::string

    auto buf = std::string{};
    buf.resize(info.st_size);
    auto const n = read(fd, &buf[0], buf.size());

    if (n == -1) {
        perror("read(2)");
    }

    close(fd);

    std::cout << buf << "\n";

    return 0;
}
