#include <fcntl.h>
#include <s23575/Student.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

s23575::Student::Student(std::string im,
                         std::string naz,
                         std::string ind,
                         unsigned const sem,
                         double const sred)
        : imie{std::move(im)}
        , nazwisko{std::move(naz)}
        , indeks{std::move(ind)}
        , semestr{sem}
        , srednia{sred}
{}

auto s23575::Student::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    out << imie << "\n"
        << nazwisko << "\n"
        << indeks << "\n"
        << semestr << "\n"
        << srednia;
    return out.str();
}

auto main() -> int
{
    auto name = std::string{"student.txt"};

    std::cout << "--> Dane zostaną odczytane z pliku: " << name << "\n";

    auto fd = open(name.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

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

    if (n == 1) {
        perror("read(2)");
    }

    close(fd);

    // Podzielenie zawartości std::string na elementy wektora - według znaku \n

    auto vect = std::vector<std::string>{};
    auto tmp  = std::string{};
    auto str  = std::stringstream(buf);
    while (getline(str, tmp, '\n')) {
        vect.push_back(tmp);
    }

    // Zapisanie zawartości poszczególnych elementów wektora do zmiennej student

    auto student = s23575::Student(
        vect[0], vect[1], vect[2], std::stoi(vect[3]), std::stod(vect[4]));

    std::cout << student.to_string() << "\n";

    return 0;
}
