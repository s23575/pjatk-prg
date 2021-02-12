#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>


auto drukuj_macierz(const std::map<std::pair<int, int>, int> macierz,
                    const int wielkosc_macierzy,
                    const int najwiekszy_rozmiar_wartosci) -> void
{
    for (auto kazdy : macierz) {
        if (kazdy.first.second == 1) {
            std::cout << " │  ";
        }

        std::cout << std::setw(najwiekszy_rozmiar_wartosci) << std::setfill(' ')
                  << kazdy.second << "  ";

        if (kazdy.first.second == wielkosc_macierzy) {
            std::cout << "│\n";
        }
    }
}

auto oblicz_wyznacznik(const std::map<std::pair<int, int>, int> macierz,
                       const int wielkosc_macierzy) -> int
{
    typedef std::pair<int, int> klucz_def;
    typedef std::map<klucz_def, int> macierz_def;

    auto wyznacznik = int{};

    if (wielkosc_macierzy == 1) {
        wyznacznik = std::prev(macierz.end())->second;

    } else {
        auto w = int{macierz.begin()->first.first};

        auto macierz_dwa = macierz_def{macierz};

        std::cout << "Macierz dwa:\n";

        for (auto i = int{1}; i <= wielkosc_macierzy; i++) {
            std::cout << w << " | " << i << " | ";

            if (macierz_dwa.find(klucz_def(w, i)) != macierz_dwa.end()) {
                macierz_dwa.erase(klucz_def(w, i));
                std::cout << "OK\n";
            } else {
                std::cout << "\n";
            }
        }

        for (auto i = int{1}; i <= wielkosc_macierzy; i++) {
            auto macierz_trzy = macierz_def{macierz_dwa};

            std::cout << "Macierz trzy:\n";

            for (auto j = int{1}; j <= wielkosc_macierzy; j++) {
                std::cout << j << " | " << i << " | ";

                if (macierz_trzy.find(klucz_def(j, i)) != macierz_trzy.end()) {
                    macierz_trzy.erase(klucz_def(j, i));
                    std::cout << "OK\n";
                } else {
                    std::cout << "\n";
                }
            }

            wyznacznik += pow((-1), (w + i)) * macierz.at(klucz_def(w, i))
                          * oblicz_wyznacznik(macierz_trzy, wielkosc_macierzy);
        }

        /*        for (auto i = int{1}; i <= macierz_dwa.wielkosc; i++) {

                }


                macierz_dwa = macierz;

                for (auto j = unsigned{0}; j < macierz_dwa.size(); j++) {
                    macierz_dwa[j].erase(macierz_dwa[j].begin());

                    //           std::cout << "macierz_dwa: " <<
           macierz_dwa[j][0] <<
                    //           "\n";
                }

                for (auto i = unsigned{0}; i < macierz.size(); i++) {
                    macierz_trzy = macierz_dwa;

                    macierz_trzy.erase(macierz_trzy.begin() + i);

                    //            std::cout << "macierz_trzy: " <<
           macierz_trzy[0][0] <<
                    //            "\n";

                    wyznacznik += pow((-1), ((i + 1) + 1)) * macierz[i][0]
                                  * oblicz_wyznacznik(macierz_trzy);
                } */
    }

    return wyznacznik;
}

auto losowa_wartosc() -> int
{
    std::random_device rd;
    std::uniform_int_distribution<int> losowa_liczba(-101, 101);

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

    typedef std::pair<int, int> klucz_def;
    typedef std::map<klucz_def, int> macierz_def;

    auto macierz                     = macierz_def{};
    auto najwiekszy_rozmiar_wartosci = size_t{};

    for (auto i = int{1}; i <= wielkosc_macierzy; i++) {
        for (auto j = int{1}; j <= wielkosc_macierzy; j++) {
            auto wpisana_wartosc  = std::string{};
            auto rozmiar_wartosci = size_t{};

            if (losowa_macierz == true) {
                macierz.insert(
                    macierz_def::value_type(klucz_def(i, j), losowa_wartosc()));
                rozmiar_wartosci =
                    std::to_string(std::prev(macierz.end())->second).length();

            } else {
                while (true) {
                    drukuj_macierz(macierz,
                                   wielkosc_macierzy,
                                   najwiekszy_rozmiar_wartosci);
                    if (j == 1) {
                        std::cout << " |  ";
                    }
                    std::getline(std::cin, wpisana_wartosc);
                    try {
                        macierz.insert(macierz_def::value_type(
                            klucz_def(i, j),
                            std::stoi(wpisana_wartosc, &rozmiar_wartosci)));
                    } catch (const std::exception&) {
                        std::cerr << "Błąd! Podana wartość nie jest "
                                     "prawidłowa. Spróbuj ponownie:\n";
                        continue;
                    }
                    std::cout << "\n";
                    break;
                }
            }

            if (rozmiar_wartosci > najwiekszy_rozmiar_wartosci) {
                najwiekszy_rozmiar_wartosci = rozmiar_wartosci;
            }
        }
    }

    drukuj_macierz(macierz, wielkosc_macierzy, najwiekszy_rozmiar_wartosci);

    std::cout << oblicz_wyznacznik(macierz, wielkosc_macierzy) << "\n";

    return 0;
}
