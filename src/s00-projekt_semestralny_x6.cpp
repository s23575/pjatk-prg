#include <s23575/Macierz.h>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

s23575::Macierz::Macierz(std::vector<int> el, int const ro, size_t const ro_el)
        : elementy{el}, rozmiar{ro}, rozmiar_elementu{ro_el}
{}

auto s23575::Macierz::operator^(int const& wykladnik) const -> int
{
    auto wynik = int{};

    for (auto i = int{0}; i < wykladnik; i++) {
        wynik *= int{this};
    }

    return wynik;
}


auto wybierz_wiersz(const std::vector<std::vector<int>> macierz,
                    const std::vector<std::vector<int>> macierz_t,
                    bool& czy_wiersz) -> int
{
    auto wybrany_wiersz = int{};
    auto wiersz_licznik = int{};

    for (auto i = size_t{0}; i < macierz.size(); i++) {
        auto licznik = std::count(macierz[i].begin(), macierz[i].end(), 0);
        if (licznik > wiersz_licznik) {
            wybrany_wiersz = i;
            wiersz_licznik = licznik;
            if (wiersz_licznik == static_cast<int>(macierz[i].size())) {
                return wybrany_wiersz;
            }
        }
    }

    for (auto i = size_t{0}; i < macierz_t.size(); i++) {
        auto licznik = std::count(macierz_t[i].begin(), macierz_t[i].end(), 0);
        if (licznik > wiersz_licznik) {
            wybrany_wiersz = i;
            wiersz_licznik = licznik;
            czy_wiersz     = false;
            if (wiersz_licznik == static_cast<int>(macierz[i].size())) {
                break;
            }
        }
    }

    return wybrany_wiersz;
}

auto s23575::Macierz::oblicz_wyznacznik() const -> int
{
    auto wyznacznik = int{};

    if (rozmiar == 1) {
        wyznacznik = elementy[0];

    } else {
        auto macierz   = std::vector<std::vector<int>>{};
        auto macierz_t = std::vector<std::vector<int>>{};

        for (auto i = int{}; i < rozmiar; i++) {
            macierz.push_back(std::vector<int>{});
            macierz_t.push_back(std::vector<int>{});
        }

        for (auto i = size_t{0}; i < elementy.size(); i++) {
            auto j = static_cast<int>(i / rozmiar);
            macierz[j].push_back(elementy[i]);

            auto k = static_cast<int>(i % rozmiar);
            macierz_t[k].push_back(elementy[i]);
        }

        auto czy_wiersz = bool{true};
        auto wiersz     = int{wybierz_wiersz(macierz, macierz_t, czy_wiersz)};

        if (czy_wiersz == false) {
            macierz = macierz_t;
        }

        //        for (auto kazdy : macierz[wiersz]) {
        //            std::cout << kazdy << " ";
        //        }
        //        std::cout << "\n";


        for (auto i = int{0}; i < rozmiar; i++) {
            auto macierz_pomniejszona = std::vector<std::vector<int>>{macierz};
            macierz_pomniejszona.erase(macierz_pomniejszona.begin() + wiersz);

            auto macierz_pomniejszona_dane    = s23575::Macierz{{}};
            macierz_pomniejszona_dane.rozmiar = rozmiar - 1;

            for (auto kazdy : macierz_pomniejszona) {
                kazdy.erase(kazdy.begin() + i);

                macierz_pomniejszona_dane.elementy.reserve(
                    macierz_pomniejszona_dane.elementy.size() + kazdy.size());
                macierz_pomniejszona_dane.elementy.insert(
                    macierz_pomniejszona_dane.elementy.end(),
                    kazdy.begin(),
                    kazdy.end());
            }

            for (auto kazdy : macierz_pomniejszona_dane.elementy) {
                auto rozmiar_wartosci = size_t{};
                rozmiar_wartosci      = std::to_string(kazdy).length();

                if (rozmiar_wartosci
                    > macierz_pomniejszona_dane.rozmiar_elementu) {
                    macierz_pomniejszona_dane.rozmiar_elementu =
                        rozmiar_wartosci;
                }
            }

            if (macierz[wiersz][i] != 0) {
                wyznacznik += pow((-1), (wiersz + 1) + (i + 1))
                              * macierz[wiersz][i]
                              * macierz_pomniejszona_dane.oblicz_wyznacznik();
            }
        }
    }

    return wyznacznik;
}

// auto oblicz_wyznacznik(const std::vector<int>& macierz_dane, const int&
// wielkosc_macierzy) -> int
//{
//    auto wyznacznik = int{};
//
//    if (wielkosc_macierzy == 1) {
//
//        wyznacznik = macierz_dane[0];
//
//    } else {
//
//        auto macierz = std::vector<std::vector<int>>{};
//        auto macierz_t = std::vector<std::vector<int>>{};
//
//        for (auto i = int{}; i < wielkosc_macierzy; i++) {
//            macierz.push_back(std::vector<int>{});
//            macierz_t.push_back(std::vector<int>{});
//        }
//
//        for (auto i = size_t{0}; i < macierz_dane.size(); i++) {
//
//            auto j = static_cast<int>(i / wielkosc_macierzy);
//            macierz[j].push_back(macierz_dane[i]);
//
//            auto k = static_cast<int>(i % wielkosc_macierzy);
//            macierz_t[k].push_back(macierz_dane[i]);
//
//        }
//
//        auto czy_wiersz = bool{true};
//        auto wiersz = int{wybierz_wiersz(macierz, macierz_t, czy_wiersz)};
//
//        if (czy_wiersz == false) {
//            macierz = macierz_t;
//        }
//
//        for (auto kazdy : macierz[wiersz]) {
//            std::cout << kazdy << " ";
//        }
//        std::cout << "\n";
//
//
//        for (auto i = int{0}; i < wielkosc_macierzy; i++) {
//
//            auto macierz_pomniejszona =
//            std::vector<std::vector<int>>{macierz};
//            macierz_pomniejszona.erase(macierz_pomniejszona.begin()+wiersz);
//
//            auto macierz_pomniejszona_dane = std::vector<int>{};
//            auto wielkosc_macierz_pomniejszona = wielkosc_macierzy - 1;
//
//            for (auto kazdy : macierz_pomniejszona) {
//
//                kazdy.erase(kazdy.begin()+i);
//
//                macierz_pomniejszona_dane.reserve(macierz_pomniejszona_dane.size()
//                + kazdy.size());
//                macierz_pomniejszona_dane.insert(macierz_pomniejszona_dane.end(),
//                kazdy.begin(), kazdy.end());
//
//            }
//
//            if (macierz[wiersz][i] != 0) {
//
//                wyznacznik += pow((-1), (wiersz+1)+(i+1)) * macierz[wiersz][i]
//                * oblicz_wyznacznik(macierz_pomniejszona_dane,
//                wielkosc_macierz_pomniejszona);
//            }
//
//        }
//    }
//
//    return wyznacznik;
//}

auto s23575::Macierz::drukuj_macierz() -> void
{
    for (auto i = size_t{0}; i < elementy.size(); i++) {
        if (static_cast<int>(i % rozmiar) == 0) {
            std::cout << " │  ";
        }

        std::cout << std::setw(rozmiar_elementu) << std::setfill(' ')
                  << elementy[i] << "  ";

        if (static_cast<int>(i % rozmiar) == rozmiar - 1) {
            std::cout << "│\n";
        }
    }
}

// auto drukuj_macierz(const std::vector<int> &macierz, const int
// &wielkosc_macierzy, const int &najwiekszy_rozmiar_wartosci) -> void
//{
//
//    for (auto i = size_t{0}; i < macierz.size(); i++) {
//        if (static_cast<int>(i % wielkosc_macierzy) == 0) {
//            std::cout << " │  ";
//        }
//
//        std::cout << std::setw(najwiekszy_rozmiar_wartosci) << std::setfill('
//        ') << macierz[i] << "  ";
//
//        if (static_cast<int>(i % wielkosc_macierzy) == wielkosc_macierzy-1) {
//            std::cout << "│\n";
//        }
//    }
//}

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

    auto macierz_dane_s    = s23575::Macierz{{}};
    macierz_dane_s.rozmiar = wielkosc_macierzy;

    for (auto i = size_t{0};
         i < (macierz_dane_s.rozmiar * macierz_dane_s.rozmiar);
         i++) {
        auto rozmiar_wartosci = size_t{};

        if (losowa_macierz == true) {
            macierz_dane_s.elementy.push_back(losowa_wartosc());
            rozmiar_wartosci =
                std::to_string(macierz_dane_s.elementy.back()).length();

        } else {
            auto wpisana_wartosc = std::string{};

            while (true) {
                macierz_dane_s.drukuj_macierz();
                if (static_cast<int>(i % macierz_dane_s.rozmiar) == 0) {
                    std::cout << " |  ";
                }
                std::getline(std::cin, wpisana_wartosc);
                try {
                    macierz_dane_s.elementy.push_back(
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

        if (rozmiar_wartosci > macierz_dane_s.rozmiar_elementu) {
            macierz_dane_s.rozmiar_elementu = rozmiar_wartosci;
        }
    }

    macierz_dane_s.drukuj_macierz();

    std::cout << macierz_dane_s.oblicz_wyznacznik() << "\n";

    std::cout << (2 ^ 2) << "\n";

    return 0;
}
