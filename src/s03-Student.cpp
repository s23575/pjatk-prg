#include <s23575/Student.h>

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
{
    std::cout << "Utworzono studenta.\n";
}

auto s23575::Student::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    out << "Dane studenta:\n"
        << "Imię: " << imie << "\n"
        << "Nazwisko: " << nazwisko << "\n"
        << "Indeks: " << indeks << "\n"
        << "Semestr: " << semestr << "\n"
        << "Średnia: " << srednia;
    return out.str();
}

auto main() -> int
{
    auto student = s23575::Student("Jan", "Kowalski", "s12345", 1, 3.25);

    std::cout << student.to_string() << "\n";

    return 0;
}
