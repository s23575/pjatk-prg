#include <s23575/Time.h>

#include <iostream>

s23575::Czas::Czas(int const g, int const m, int const s)
        : godzina{g}, minuta{m}, sekunda{s}
{
    validate_time();
}

auto s23575::Czas::validate_time() -> int
{
    auto zwieksz = int{};
    if (sekunda >= 60) {
        zwieksz = sekunda / 60;
        minuta += zwieksz;
        sekunda = sekunda % 60;
    } else if (sekunda < 0) {
        zwieksz = sekunda / 60 - 1;
        minuta += zwieksz;
        sekunda = 60 + sekunda;
    }

    if (minuta >= 60) {
        zwieksz = minuta / 60;
        godzina += zwieksz;
        minuta = minuta % 60;
    } else if (minuta < 0) {
        zwieksz = minuta / 60 - 1;
        godzina += zwieksz;
        minuta = 60 + minuta;
    }

    if (godzina >= 24) {
        godzina = godzina % 24;
    } else if (godzina < 0) {
        godzina = 24 + godzina;
    }

    return 0;
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
    validate_time();
    std::cout << "Funkcja zwiększająca czas o jedną godzinę:\n"
              << to_string() << "\n";
}

auto s23575::Czas::next_minute() -> void
{
    ++minuta;
    validate_time();
    std::cout << "Funkcja zwiększająca czas o jedną minutę:\n"
              << to_string() << "\n";
}

auto s23575::Czas::next_second() -> void
{
    ++sekunda;
    validate_time();
    std::cout << "Funkcja zwiększająca czas o jedną sekundę:\n"
              << to_string() << "\n";
}

auto s23575::Czas::time_of_day() const -> Time_of_day
{
    s23575::Czas::Time_of_day t;

    if (godzina < 7) {
        t = Time_of_day::noc;
    } else if (godzina >= 7 && godzina < 12) {
        t = Time_of_day::rano;
    } else if (godzina >= 12 && godzina < 19) {
        t = Time_of_day::dzien;
    } else {
        t = Time_of_day::wieczor;
    }

    return t;
}

auto s23575::Czas::to_string(Time_of_day t) const -> std::string
{
    auto pora_str = std::string{};

    switch (t) {
    case Time_of_day::noc:
        pora_str = "noc";
        break;
    case Time_of_day::rano:
        pora_str = "rano";
        break;
    case Time_of_day::dzien:
        pora_str = "dzień";
        break;
    case Time_of_day::wieczor:
        pora_str = "wieczór";
        break;
    }

    auto out = std::ostringstream{};
    out << pora_str;
    return out.str();
}

auto s23575::Czas::operator+(Czas const& druga_godzina) const -> Czas
{
    auto czas_wynik = s23575::Czas(godzina + druga_godzina.godzina,
                                   minuta + druga_godzina.minuta,
                                   sekunda + druga_godzina.sekunda);

    return czas_wynik;
}

auto s23575::Czas::operator-(Czas const& druga_godzina) const -> Czas
{
    auto czas_wynik = s23575::Czas(godzina - druga_godzina.godzina,
                                   minuta - druga_godzina.minuta,
                                   sekunda - druga_godzina.sekunda);

    return czas_wynik;
}

auto s23575::Czas::operator<(Czas const& druga_godzina) const -> bool
{
    auto wynik_porownania = bool();

    if (godzina < druga_godzina.godzina) {
        wynik_porownania = true;
    } else if (godzina == druga_godzina.godzina) {
        if (minuta < druga_godzina.minuta) {
            wynik_porownania = true;
        } else if (minuta == druga_godzina.minuta) {
            if (sekunda < druga_godzina.sekunda) {
                wynik_porownania = true;
            }
        }
    }

    return wynik_porownania;
}

auto s23575::Czas::operator>(Czas const& druga_godzina) const -> bool
{
    auto wynik_porownania = bool();

    if (godzina > druga_godzina.godzina) {
        wynik_porownania = true;
    } else if (godzina == druga_godzina.godzina) {
        if (minuta > druga_godzina.minuta) {
            wynik_porownania = true;
        } else if (minuta == druga_godzina.minuta) {
            if (sekunda > druga_godzina.sekunda) {
                wynik_porownania = true;
            }
        }
    }

    return wynik_porownania;
}

auto s23575::Czas::operator==(Czas const& druga_godzina) const -> bool
{
    auto wynik_porownania = bool();

    if (godzina == druga_godzina.godzina && minuta == druga_godzina.minuta
        && sekunda == druga_godzina.sekunda) {
        wynik_porownania = true;
    }

    return wynik_porownania;
}

auto s23575::Czas::operator!=(Czas const& druga_godzina) const -> bool
{
    auto wynik_porownania = bool();

    if (godzina != druga_godzina.godzina || minuta != druga_godzina.minuta
        || sekunda != druga_godzina.sekunda) {
        wynik_porownania = true;
    }

    return wynik_porownania;
}

auto s23575::Czas::count_seconds() const -> uint64_t
{
    auto sekundy_od_polnocy = uint64_t{};

    sekundy_od_polnocy = (godzina * 3600) + (minuta * 60) + sekunda;

    return sekundy_od_polnocy;
}

auto s23575::Czas::count_minutes() const -> uint64_t
{
    auto minuty_od_polnocy = uint64_t{};

    minuty_od_polnocy = (godzina * 60) + minuta;

    if (sekunda >= 30) {
        minuty_od_polnocy += 1;
    }

    return minuty_od_polnocy;
}

auto s23575::Czas::time_to_midnight() const -> Czas
{
    auto czas_do_polnocy =
        s23575::Czas{23 - godzina, 59 - minuta, 60 - sekunda};

    return czas_do_polnocy;
}

auto main() -> int
{
    auto czas = s23575::Czas{12, 0, -6};
    std::cout << "Funkcja pokazująca czas w formacie HH:MM:SS:\n"
              << czas.to_string() << "\n";

    czas.next_hour();
    czas.next_minute();
    czas.next_second();

    czas = s23575::Czas(23, 59, 59);
    std::cout << "Zweryfikowanie działania struktury danych dla godziny:\n"
              << czas.to_string() << "\n";
    czas.next_second();

    czas                           = s23575::Czas(12, 5, 00);
    s23575::Czas::Time_of_day pora = czas.time_of_day();
    std::cout << "Funkcja zwracająca porę dnia dla wybranej godziny ("
              << czas.to_string() << "):\n"
              << czas.to_string(pora) << "\n";

    auto czas_1     = s23575::Czas{23, 59, 59};
    auto czas_2     = s23575::Czas{0, 1, 0};
    auto czas_wynik = s23575::Czas{};

    czas_wynik = czas_1 + czas_2;
    std::cout << "Funkcja pozwalająca na dodawanie czasu ("
              << czas_1.to_string() << " + " << czas_2.to_string() << "):\n"
              << czas_wynik.to_string() << "\n";

    czas_1     = s23575::Czas{12, 00, 00};
    czas_2     = s23575::Czas{00, 00, 1};
    czas_wynik = czas_1 - czas_2;
    std::cout << "Funkcja pozwalająca na odejmowanie czasu ("
              << czas_1.to_string() << " - " << czas_2.to_string() << "):\n"
              << czas_wynik.to_string() << "\n";

    auto wynik_porownania     = bool{};
    auto wynik_porownania_str = std::string{};

    czas_1 = s23575::Czas{12, 10, 00};
    czas_2 = s23575::Czas{24, 20, 00};

    wynik_porownania = czas_1 < czas_2;
    if (wynik_porownania) {
        wynik_porownania_str = "Prawda";
    } else {
        wynik_porownania_str = "Fałsz";
    }
    std::cout << "Funkcja pozwalająca na porównywanie czasu (czy godzina "
              << czas_1.to_string() << " jest wcześniejsza od godziny "
              << czas_2.to_string() << "):\n"
              << wynik_porownania_str << "\n";

    czas_1 = s23575::Czas{23, 10, 00};
    czas_2 = s23575::Czas{20, 20, 00};

    wynik_porownania = czas_1 > czas_2;
    if (wynik_porownania) {
        wynik_porownania_str = "Prawda";
    } else {
        wynik_porownania_str = "Fałsz";
    }
    std::cout << "Funkcja pozwalająca na porównywanie czasu (czy godzina "
              << czas_1.to_string() << " jest późniejsza od godziny "
              << czas_2.to_string() << "):\n"
              << wynik_porownania_str << "\n";

    czas_1 = s23575::Czas{13, 10, 00};
    czas_2 = s23575::Czas{13, 10, 00};

    wynik_porownania = czas_1 == czas_2;
    if (wynik_porownania) {
        wynik_porownania_str = "Prawda";
    } else {
        wynik_porownania_str = "Fałsz";
    }
    std::cout << "Funkcja pozwalająca na porównywanie czasu (czy godzina "
              << czas_1.to_string() << " jest taka sama jak godzina "
              << czas_2.to_string() << "):\n"
              << wynik_porownania_str << "\n";

    wynik_porownania = czas_1 != czas_2;
    if (wynik_porownania) {
        wynik_porownania_str = "Prawda";
    } else {
        wynik_porownania_str = "Fałsz";
    }
    std::cout << "Funkcja pozwalająca na porównywanie czasu (czy godzina "
              << czas_1.to_string() << " jest różna od godziny "
              << czas_2.to_string() << "):\n"
              << wynik_porownania_str << "\n";

    czas = s23575::Czas(1, 1, 150);
    std::cout << "Funkcja zwracająca liczbę sekund od północy do godziny "
              << czas.to_string() << ":\n"
              << czas.count_seconds() << "\n";

    std::cout << "Funkcja zwracająca liczbę minut od północy do godziny "
              << czas.to_string() << " (w zaokrągleniu):\n"
              << czas.count_minutes() << "\n";

    auto czas_do_polnocy = s23575::Czas{};

    czas            = s23575::Czas(23, 58, 00);
    czas_do_polnocy = czas.time_to_midnight();
    std::cout << czas_do_polnocy.to_string();

    return 0;
}
