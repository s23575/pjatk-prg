#include <s23575/Macierz.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

s23575::Element_Macierzy::Element_Macierzy(int const wi,
                                           int const ko,
                                           int const wa)
        : wiersz{wi}, kolumna{ko}, wartosc{wa}
{}

s23575::Macierz::Macierz(std::vector<Element_Macierzy> za,
                         int const wi,
                         size_t const ro)
        : zawartosc{za}, wielkosc{wi}, rozmiar_liczby{ro}
{}

auto s23575::Macierz::drukuj_macierz() -> void
{
    for (auto kazdy : zawartosc) {
        if (kazdy.kolumna == 1) {
            std::cout << " │  ";
        }

        std::cout << std::setw(rozmiar_liczby) << std::setfill(' ')
                  << kazdy.wartosc << "  ";

        if (kazdy.kolumna == wielkosc) {
            std::cout << "│\n";
        }
    }
}

auto s23575::Macierz::wybierz_wiersz_kolumne() -> int
{}

auto s23575::Macierz::oblicz_wyznacznik() -> int
{
    auto wyznacznik = int{};

    if (zawartosc.size() == 1) {
        wyznacznik = zawartosc[0].wartosc;

    } else {
        auto macierz_dwa = s23575::Macierz{{zawartosc}, wielkosc};

        for (auto i = int{1}; i <= macierz_dwa.wielkosc; i++) {
        }


/*        macierz_dwa = macierz;

        for (auto j = unsigned{0}; j < macierz_dwa.size(); j++) {
            macierz_dwa[j].erase(macierz_dwa[j].begin());

            //           std::cout << "macierz_dwa: " << macierz_dwa[j][0] <<
            //           "\n";
        }

        for (auto i = unsigned{0}; i < macierz.size(); i++) {
            macierz_trzy = macierz_dwa;

            macierz_trzy.erase(macierz_trzy.begin() + i);

            //            std::cout << "macierz_trzy: " << macierz_trzy[0][0] <<
            //            "\n";

            wyznacznik += pow((-1), ((i + 1) + 1)) * macierz[i][0]
                          * oblicz_wyznacznik(macierz_trzy);
        }
*/    }

return wyznacznik;
}

auto losowa_wartosc() -> int
{
    std::random_device rd;
    std::uniform_int_distribution<int> losowa_liczba(-100, 100);

    auto const wylosowana_liczba = losowa_liczba(rd);

    return wylosowana_liczba;
}

auto main(int argc, char* argv[]) -> int
{
    auto liczba_argumentow = int{argc};

    if (liczba_argumentow == 1) {
        std::cerr << "Błąd! Nie podano żadnych argumentów.\n";
        return 1;
    }

    auto argumenty = std::vector<std::string>{};
    std::copy(argv + 1, argv + argc, std::back_inserter(argumenty));

    auto losowa_macierz    = bool{};
    auto wielkosc_macierzy = int{};

    for (auto kazdy : argumenty) {
        if (kazdy == "-r") {
            losowa_macierz = true;

            // } else if (argument == "-v") {

            // tryb_opisowy = "-v";

        } else {
            auto ostatni_znak = size_t{};
            try {
                wielkosc_macierzy = std::stoi(kazdy, &ostatni_znak);
                if (ostatni_znak != kazdy.size()) {
                    wielkosc_macierzy = -1;
                }
            } catch (const std::exception&) {
                wielkosc_macierzy = -1;
            }
            break;
        }
    }

    if (wielkosc_macierzy <= 0) {
        std::cerr << "Błąd! Nie podano wielkości macierzy lub podana wielkość "
                     "nie jest prawidłowa.\n";
        return 1;
    }

    auto macierz          = s23575::Macierz{{}, wielkosc_macierzy};
    auto element_macierzy = s23575::Element_Macierzy{};

    for (auto i = int{1}; i <= macierz.wielkosc; i++) {
        for (auto j = int{1}; j <= macierz.wielkosc; j++) {
            auto wpisana_wartosc  = std::string{};
            auto rozmiar_wartosci = size_t{};

            if (losowa_macierz == true) {
                element_macierzy =
                    s23575::Element_Macierzy{i, j, losowa_wartosc()};
                rozmiar_wartosci =
                    std::to_string(element_macierzy.wartosc).length();

            } else {
                while (true) {
                    macierz.drukuj_macierz();
                    if (j == 1) {
                        std::cout << " |  ";
                    }
                    std::getline(std::cin, wpisana_wartosc);
                    try {
                        element_macierzy = s23575::Element_Macierzy{
                            i,
                            j,
                            std::stoi(wpisana_wartosc, &rozmiar_wartosci)};
                    } catch (const std::exception&) {
                        std::cerr << "Błąd! Podana wartość nie jest "
                                     "prawidłowa. Spróbuj ponownie:\n";
                        continue;
                    }
                    std::cout << "\n";
                    break;
                }
            }

            macierz.zawartosc.push_back(element_macierzy);
            if (rozmiar_wartosci > macierz.rozmiar_liczby) {
                macierz.rozmiar_liczby = rozmiar_wartosci;
            }
        }
    }

    macierz.drukuj_macierz();

    std::cout << macierz.oblicz_wyznacznik() << "\n";

    return 0;
}
