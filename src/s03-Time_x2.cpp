#include <s23575/Time.h>

#include <iostream>

s23575::Czas::Czas(unsigned const g, unsigned const m, unsigned const s)
        : godzina{g}, minuta{m}, sekunda{s}
{
    auto zwieksz = int{};

    if (sekunda >= 60) {
        zwieksz = sekunda / 60;
        minuta += zwieksz;
        sekunda = sekunda % 60;
    }
    if (minuta >= 60) {
        zwieksz = minuta / 60;
        godzina += zwieksz;
        minuta = minuta % 60;
    }
    if (godzina >= 24) {
        godzina = godzina % 24;
    }
}

auto s23575::Czas::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    if (godzina < 10) {
        out << "0";
    }
    out << godzina << ":";
    if (minuta < 10) {
        out << "0";
    }
    out << minuta << ":";
    if (sekunda < 10) {
        out << "0";
    }
    out << sekunda;
    return out.str();
}


auto s23575::Czas::next_hour() -> void
{
    ++godzina;
    if (godzina >= 24) {
        godzina = godzina % 24;
    }
    std::cout << to_string() << "\n";
}

auto s23575::Czas::next_minute() -> void
{
    ++minuta;
    if (minuta >= 60) {
        godzina += 1;
        minuta = minuta % 60;
    }
    std::cout << to_string() << "\n";
}

auto s23575::Czas::next_second() -> void
{
    ++sekunda;
    if (sekunda >= 60) {
        minuta  = 1;
        sekunda = sekunda % 60;
    }
    std::cout << to_string() << "\n";
}

auto main() -> int
{
    auto czas = s23575::Czas(1, 1, 1);

    std::cout << czas.to_string() << "\n";

    czas.next_hour();
    czas.next_minute();
    czas.next_second();

    czas = s23575::Czas(23, 59, 59);
    czas.next_second();

    return 0;
}
