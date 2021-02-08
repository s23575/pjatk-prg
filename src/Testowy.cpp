#include <s23575/Macierz.h>
#include <time.h>

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

s23575::Element_Macierzy::Element_Macierzy(int const wi,
                                           int const ko,
                                           int const wa)
        : wiersz{wi}, kolumna{ko}, wartosc{wa}
{}

s23575::Macierz::Macierz(std::vector<Element_Macierzy> za, int const wi)
        : zawartosc{za}, wielkosc{wi}
{}

auto main() -> int
{
    /*
        auto macierz_dane =
            std::vector<int>{3, -2, 0, 5, -2, 1, -2, 0, 0, -2, 5, 3, 5, 2, 0,
       4};

        auto macierz = std::vector<std::vector<int>>{};

        auto licznik = int(sqrt(macierz_dane.size()));

        for (auto i = int{0}; i < licznik; i++) {
            auto wiersz = std::vector<int>{};

            std::cout << "kopiuj jeden\n";

            std::copy(macierz_dane.begin() + (i * licznik),
                      macierz_dane.begin() + ((i + 1) * licznik),
                      std::back_inserter(wiersz));

            macierz.push_back(wiersz);
        }

        for (auto n : macierz) {
            for (auto x : n) {
                std::cout << x << ", ";
            }

            std::cout << macierz.size() << "\n";
        }
    */
    /*
        auto koniec_czasu = time_t{};
        auto czas_sek = int{20};
        koniec_czasu = time(NULL)+czas_sek;
        while (time(NULL)<koniec_czasu) {

        }
        std::cout << "Koniec czasu\n";
    */
    /*    auto wektor = std::vector<std::string>{"A","B","C", "D","E","F"};
        std::cout << wektor.at(wektor.begin() << "\n";

        for (auto i = unsigned{0}; i < wektor.size(); i++) {
            std::cout << i << " " << wektor[i] << "\n";
            if (wektor[i] == "C") {
                wektor.erase(wektor.begin()+i);
                i--;
            }
        }
    */

    //    std::default_random_engine rd;
    //    std::uniform_int_distribution<int> losowa_liczba(0, 100);
    //    std::uniform_int_distribution<int>
    //    losowa_liczba_2(losowa_liczba.param());
    //
    //    std::cout << losowa_liczba(rd) << "\n";
    //    std::cout << losowa_liczba_2(rd) << "\n";

    //    auto test = std::vector<std::string>{"a", "b", "c"};
    //    for (auto & each : test) {
    //        std::cout << & each << " / " << test.back() << "\n";
    //    }

    //    auto test = std::vector<std::string>{};
    //    auto nowy = std::string{};
    //
    //    std::getline(std::cin, nowy);
    //    test.push_back(nowy);
    //    std::cout << test[0] << "\n";
    //    std::cout << "jaki jest test: ";
    //    std::getline(std::cin, nowy);
    //
    //    auto t = std::string{"45335.25"};
    //    auto i = double{};
    //    auto j = size_t{};
    //    i = std::stold(t,&j);
    //    std::cout << std::setprecision(j)<< i << "\n";
    //    std::cout << j << "\n";
    //    t = std::string{"25"};
    //    i = std::stold(t,&j);
    //    std::cout << std::setprecision(j) << i << "\n";
    //    std::cout << j << "\n";
    //


    auto element = s23575::Element_Macierzy{1, 2, 3};
    auto macierz = s23575::Macierz{{}};
    std::cout << element.kolumna << "\n";
    macierz.zawartosc.push_back(element);
    for (auto kazdy : macierz.zawartosc) {
        std::cout << kazdy.kolumna << "\n";
    }


    return 0;
}
