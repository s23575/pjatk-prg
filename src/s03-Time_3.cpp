#include <s23575/Time.h>

#include <iostream>

// <-- Konstruktor -->

s23575::Czas::Czas(int const g, int const m, int const s)
        : godzina{g}, minuta{m}, sekunda{s}
{
    validate_time();
}

// <-- Funkcja validate_time -->

/* Funkcja validate_time służy odpowiedniemu przeliczeniu podanych wartości
 * godzin, minut i sekund w sytuacji, gdy są one większe niż (odpowiednio) 24,
 * 60 i 60 (przykładowo: 72 sekundy zostaną przelioczne na 1 minutę i 12 sekund)
 * oraz gdy są one wartościami ujemnymi (przykładowo: 2 minuty i -1 sekunda
 * zostanie przekształcone na 1 minutę i 59 sekund) */

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

// <-- Funkcja to_string() (s04-data-structures.pdf, s. 25) -->

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

// <-- Funkcje next_hour(), next_minute() i next_second()
// (s04-data-structures.pdf, s. 25) -->

auto s23575::Czas::next_hour() -> void
{
    ++godzina;
    validate_time();
    std::cout << "Funkcja zwiększająca czas o jedną godzinę:\n"
              << to_string() << "\n";  //<-- std::cout zwracany w celach
                                       // weryfikacji działania funkcji
}

auto s23575::Czas::next_minute() -> void
{
    ++minuta;
    validate_time();
    std::cout << "Funkcja zwiększająca czas o jedną minutę:\n"
              << to_string() << "\n";  //<-- std::cout zwracany w celach
                                       // weryfikacji działania funkcji
}

auto s23575::Czas::next_second() -> void
{
    ++sekunda;
    validate_time();
    std::cout << "Funkcja zwiększająca czas o jedną sekundę:\n"
              << to_string() << "\n";  //<-- std::cout zwracany w celach
                                       // weryfikacji działania funkcji
}

// <-- Funkcje time_of_day() i to_string(time_of_day) (s04-data-structures.pdf,
// s. 26) -->

auto s23575::Czas::time_of_day() const -> Time_of_day
{
    s23575::Czas::Time_of_day pora;

    if (godzina < 7) {
        pora = Time_of_day::noc;
    } else if (godzina >= 7 && godzina < 12) {
        pora = Time_of_day::rano;
    } else if (godzina >= 12 && godzina < 19) {
        pora = Time_of_day::dzien;
    } else {
        pora = Time_of_day::wieczor;
    }

    return pora;
}

auto s23575::Czas::to_string(Time_of_day pora) const -> std::string
{
    auto pora_str = std::string{};

    /* Czy jest prosty (automatyczny) sposób na przekonwertowanie poszczególnych
     * typów wyliczeniowych na stringi? Niestety, nic prostszego, niż switch nie
     * udało mi się opracować... */

    switch (pora) {
    case Time_of_day::noc:
        pora_str = "Noc (od 00:00:00 do 06:59:59)";
        break;
    case Time_of_day::rano:
        pora_str = "Rano (od 07:00:00 do 11:59:59)";
        break;
    case Time_of_day::dzien:
        pora_str = "Dzień (od 12:00:00 do 18:59:59)";
        break;
    case Time_of_day::wieczor:
        pora_str = "Wieczór (od 19:00:00 do 23:59:59)";
        break;
    }

    auto out = std::ostringstream{};
    out << pora_str;
    return out.str();
}

// <-- Funkcje artmetyczne dotyczące czasu (s04-data-structures.pdf, s. 27) -->

auto s23575::Czas::operator+(Czas const& druga_godzina) const -> Czas
{
    /* Funkcje dotyczące dodawania i odejmowania skontrutowałem w taki prosty
     * sposób, bo za odpowiednie przeliczanie wartości godzin, minut i sekund
     * (gdy ich wartości są zbyt duże lub ujemne) odpowiada funkcja
     * validate_time() */

    auto czas_wynik = s23575::Czas{godzina + druga_godzina.godzina,
                                   minuta + druga_godzina.minuta,
                                   sekunda + druga_godzina.sekunda};

    return czas_wynik;
}

auto s23575::Czas::operator-(Czas const& druga_godzina) const -> Czas
{
    auto czas_wynik = s23575::Czas{godzina - druga_godzina.godzina,
                                   minuta - druga_godzina.minuta,
                                   sekunda - druga_godzina.sekunda};

    return czas_wynik;
}

auto s23575::Czas::operator<(Czas const& druga_godzina) const -> bool
{
    auto wynik_porownania = bool{};

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
    auto wynik_porownania = bool{};

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
    auto wynik_porownania = bool{};

    if (godzina == druga_godzina.godzina && minuta == druga_godzina.minuta
        && sekunda == druga_godzina.sekunda) {
        wynik_porownania = true;
    }

    return wynik_porownania;
}

auto s23575::Czas::operator!=(Czas const& druga_godzina) const -> bool
{
    auto wynik_porownania = bool{};

    if (godzina != druga_godzina.godzina || minuta != druga_godzina.minuta
        || sekunda != druga_godzina.sekunda) {
        wynik_porownania = true;
    }

    return wynik_porownania;
}

// <-- Funkcje count_seconds(), count_minutes() i time_to_midnight()
// (s04-data-structures.pdf, s. 28) -->

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
    auto czas = s23575::Czas{};

    czas = s23575::Czas{14, 75, -1};  //<-- do zmiany dla potrzeb testów

    // <-- Funkcja to_string() (s04-data-structures.pdf, s. 25) -->

    std::cout << "Funkcja pokazująca czas w formacie HH:MM:SS:\n"
              << czas.to_string() << "\n";

    // <-- Funkcje next_hour(), next_minute() i next_second()
    // (s04-data-structures.pdf, s. 25) -->

    czas.next_hour();
    czas.next_minute();
    czas.next_second();

    czas = s23575::Czas(23, 59, 59);

    std::cout << "Zweryfikowanie działania struktury danych dla godziny:\n"
              << czas.to_string() << "\n";

    czas.next_second();

    // <-- Funkcje time_of_day() i to_string(time_of_day)
    // (s04-data-structures.pdf, s. 26) -->

    czas = s23575::Czas(3, 0, 2);  //<-- do zmiany dla potrzeb testów

    s23575::Czas::Time_of_day pora = czas.time_of_day();

    std::cout << "Funkcja zwracająca porę dnia dla wybranej godziny ("
              << czas.to_string() << "):\n"
              << czas.to_string(pora) << "\n";

    // <-- Funkcje artmetyczne dotyczące czasu (s04-data-structures.pdf, s. 27)
    // -->

    auto czas_1     = s23575::Czas{};
    auto czas_2     = s23575::Czas{};
    auto czas_wynik = s23575::Czas{};

    czas_1 = s23575::Czas{23, 59, 59};  //<-- do zmiany dla potrzeb testów
    czas_2 = s23575::Czas{0, 1, 0};     //<-- do zmiany dla potrzeb testów

    czas_wynik = czas_1 + czas_2;

    std::cout << "Funkcja pozwalająca na dodawanie czasu ("
              << czas_1.to_string() << " + " << czas_2.to_string() << "):\n"
              << czas_wynik.to_string() << "\n";

    czas_wynik = czas_1 - czas_2;

    std::cout << "Funkcja pozwalająca na odejmowanie czasu ("
              << czas_1.to_string() << " - " << czas_2.to_string() << "):\n"
              << czas_wynik.to_string() << "\n";

    auto wynik_porownania     = bool{};
    auto wynik_porownania_str = std::string{};

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

    // <-- Funkcje count_seconds(), count_minutes() i time_to_midnight()
    // (s04-data-structures.pdf, s. 28) -->

    czas = s23575::Czas(0, 1, 31);  //<-- do zmiany dla potrzeb testów

    std::cout << "Funkcja zwracająca liczbę sekund od północy do godziny "
              << czas.to_string() << ":\n"
              << czas.count_seconds() << "\n";

    std::cout << "Funkcja zwracająca liczbę minut od północy do godziny "
              << czas.to_string() << " (w zaokrągleniu):\n"
              << czas.count_minutes() << "\n";

    auto czas_do_polnocy = s23575::Czas{};

    czas_do_polnocy = czas.time_to_midnight();

    std::cout << "Funkcja zwracają czas pozostały do północy od godziny "
              << czas.to_string() << ":\n"
              << czas_do_polnocy.to_string() << "\n";

    return 0;
}
