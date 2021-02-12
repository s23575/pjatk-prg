#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

auto wiersz(const int indeks, const int wielkosc_macierzy) -> int
{
    auto numer_wiersza = int{};
    numer_wiersza      = static_cast<int>(indeks / wielkosc_macierzy) + 1;

    return numer_wiersza;
}

auto kolumna(const int indeks, const int wielkosc_macierzy) -> int
{
    auto numer_kolumny = int{};
    numer_kolumny      = static_cast<int>(indeks % wielkosc_macierzy) + 1;

    return numer_kolumny;
}

// auto indeks(const std::vector<int> wektor, const int element) -> int
//{
//    auto it = std::find(wektor.begin(), wektor.end(), element);
//    auto indeks = int{};
//
//    if (it != wektor.end()) {
//        indeks = it - wektor.begin();
//    }
//
//    return indeks;
//}


auto drukuj_macierz(const std::vector<int> macierz,
                    const int wielkosc_macierzy,
                    const int najwiekszy_rozmiar_wartosci) -> void
{
    for (auto i = size_t{0}; i < macierz.size(); i++) {
        if (kolumna(i, wielkosc_macierzy) == 1) {
            std::cout << " │  ";
        }

        std::cout << std::setw(najwiekszy_rozmiar_wartosci) << std::setfill(' ')
                  << macierz[i] << "  ";

        if (kolumna(i, wielkosc_macierzy) == wielkosc_macierzy) {
            std::cout << "│\n";
        }
    }
}

auto oblicz_wyznacznik(const std::vector<int> macierz,
                       const int wielkosc_macierzy) -> int
{
    auto wyznacznik = int{};

    if (wielkosc_macierzy == 1) {
        wyznacznik = macierz[0];

    } else {
        auto w = int{2};

        for (auto k = int{1}; k <= wielkosc_macierzy; k++) {
            auto macierz_pomniejszona = std::vector<int>{};
            auto j                    = int{};

            for (auto i = size_t{0}; i < macierz.size(); i++) {
                if (wiersz(i, wielkosc_macierzy) != w
                    && kolumna(i, wielkosc_macierzy) != k) {
                    macierz_pomniejszona.push_back(macierz[i]);

                } else if (wiersz(i, wielkosc_macierzy) == w
                           && kolumna(i, wielkosc_macierzy) == k) {
                    j = macierz[i];
                }
            }

            wyznacznik += pow((-1), (w + k)) * j
                          * oblicz_wyznacznik(macierz_pomniejszona,
                                              wielkosc_macierzy - 1);
        }

        //        for (auto i = int{0}, j = int{0}; i <
        //        static_cast<int>(macierz_dwa.size()); i++, j++) {
        //
        //           if (wiersz(j, wielkosc_macierzy) == 1) {
        //                macierz_dwa.erase(macierz_dwa.begin()+i);
        //                i--;
        //            }
        //
        //        }
        //
        //        for (auto i = size_t{0}; i < macierz_dwa.size(); i++) {
        //
        //            auto macierz_trzy = std::vector<int>{macierz_dwa};
        //
        //            for (auto j = int{0}; j <
        //            static_cast<int>(macierz_trzy.size()); j++) {
        //
        //               if (kolumna(i, wielkosc_macierzy) == 1) {
        //                    macierz_trzy.erase(macierz_trzy.begin()+j);
        //                    j--;
        //                }
        //            }
        //
        //            wyznacznik += pow((-1), (1 + kolumna(i,
        //            wielkosc_macierzy))) * macierz[i] *
        //            oblicz_wyznacznik(macierz_trzy, wielkosc_macierzy-1);
        //        }
        //
        //        for (auto i = int{1}; i <= macierz_dwa.wielkosc; i++) {
        //
        //        }
        //
        //
        //        macierz_dwa = macierz;
        //
        //        for (auto j = unsigned{0}; j < macierz_dwa.size(); j++) {
        //            macierz_dwa[j].erase(macierz_dwa[j].begin());
        //
        //            //           std::cout << "macierz_dwa: " <<
        //            macierz_dwa[j][0] <<
        //            //           "\n";
        //        }
        //
        //        for (auto i = unsigned{0}; i < macierz.size(); i++) {
        //            macierz_trzy = macierz_dwa;
        //
        //            macierz_trzy.erase(macierz_trzy.begin() + i);
        //
        //            //            std::cout << "macierz_trzy: " <<
        //            macierz_trzy[0][0] <<
        //            //            "\n";
        //
        //            wyznacznik += pow((-1), ((i + 1) + 1)) * macierz[i][0]
        //                          * oblicz_wyznacznik(macierz_trzy);
        //        }
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

    auto macierz                     = std::vector<int>{};
    auto najwiekszy_rozmiar_wartosci = size_t{};

    for (auto i = size_t{0}; i < (wielkosc_macierzy * wielkosc_macierzy); i++) {
        auto rozmiar_wartosci = size_t{};

        if (losowa_macierz == true) {
            macierz.push_back(losowa_wartosc());
            rozmiar_wartosci = std::to_string(macierz.back()).length();

        } else {
            auto wpisana_wartosc = std::string{};

            while (true) {
                drukuj_macierz(
                    macierz, wielkosc_macierzy, najwiekszy_rozmiar_wartosci);
                if (kolumna(i, wielkosc_macierzy) == 1) {
                    std::cout << " |  ";
                }
                std::getline(std::cin, wpisana_wartosc);
                try {
                    macierz.push_back(
                        std::stoi(wpisana_wartosc, &rozmiar_wartosci));
                } catch (const std::exception&) {
                    std::cerr << "Błąd! Podana wartość nie jest prawidłowa. "
                                 "Spróbuj ponownie:\n";
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

    drukuj_macierz(macierz, wielkosc_macierzy, najwiekszy_rozmiar_wartosci);

    std::cout << oblicz_wyznacznik(macierz, wielkosc_macierzy) << "\n";

    return 0;
}
