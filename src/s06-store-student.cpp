#include <fcntl.h>
#include <s23575/Student.h>
#include <unistd.h>

#include <iostream>


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
    auto student = s23575::Student("Jan", "Kowalski", "s12345", 1, 3.25);

    std::cout << student.to_string() << "\n";

    auto name = std::string{"student.txt"};

    std::cout << "<-- Powyższe dane zostaną zapisane do pliku: " << name
              << "\n";

    auto fd = open(name.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    auto n = write(fd, student.to_string().data(), student.to_string().size());
    if (n == -1) {
        perror("write(2)");
    }

    close(fd);

    return 0;
}
