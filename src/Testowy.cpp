#include <s23575/Macierz.h>
#include <time.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <string>
#include <vector>

// s23575::Element_Macierzy::Element_Macierzy(int const wi,
//                                           int const ko,
//                                           int const wa)
//        : wiersz{wi}, kolumna{ko}, wartosc{wa}
//{}
//
// s23575::Macierz::Macierz(std::vector<Element_Macierzy> za, int const wi)
//        : zawartosc{za}, wielkosc{wi}
//{}
//
// auto losowa_liczba() -> double
//{
//    std::random_device rd;
//    std::uniform_int_distribution<int> losowa_liczba(0, 100);
//
//    auto const wylosowana_liczba = losowa_liczba(rd);
//
//    return wylosowana_liczba;
//
//}
//
// auto indeks(const std::vector<int> wektor, const int element) -> int
//{
//
//    auto indeks = std::find(wektor.begin(), wektor.end(), element) -
//    wektor.begin();
//
//    return indeks;
//
//}

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
    //    //
    //        auto t = std::string{};
    //        std::getline(std::cin, t);
    //        auto i = int{};
    //        auto j = size_t{};
    //        try {
    //        i = std::stoi(t,&j);
    //        } catch (const std::exception&) {
    //            std::cerr << "Błąd!\n";
    //            return 1;
    //        }
    //        std::cout << std::to_string(i).length();
    //        std::cout << i << "\n";
    //        std::cout << j << "\n";
    //        t = std::string{"25"};
    //        i = std::stold(t,&j);
    //        std::cout << std::setprecision(j) << i << "\n";
    //        std::cout << j << "\n";
    //        if (j < static_cast<size_t>(i)) {
    //            std::cout << "OK\n";
    //        }
    //
    //
    //    auto element = s23575::Element_Macierzy{1, 2, 3};
    //    auto macierz = s23575::Macierz{{}, 7};
    //    std::cout << element.kolumna << "\n";
    //    macierz.zawartosc.push_back(element);
    //    for (auto kazdy : macierz.zawartosc) {
    //        std::cout << kazdy.kolumna << "\n";
    //    }
    //

    //    std::cout << typeid(losowa_liczba()).name() << "\n";

    //    typedef std::pair<std::string, std::string> klucz;
    //    auto m = std::map<std::pair<std::string, std::string>, int>{};
    //
    //    m.insert(std::make_pair(klucz("A", "B"), 43));
    //    m.insert(std::make_pair(klucz("C", "D"), 18));
    //
    //    if (m.find(klucz("X","Y")) != m.end()) {
    //        std::cout << "OK!\n";
    //    } else {
    //        std::cout << "Nie OK!\n";
    //    }
    //    for (auto each : m) {
    //        std::cout << each.second << "\n";
    //    }
    //
    //    m.erase(klucz("C","D"));
    //
    //    for (auto each : m) {
    //        std::cout << each.second << "\n";
    //    }

    //    auto test = std::vector<std::vector<int>>{{1, 2, 3},{4,5,6},{7, 8,
    //    9}};
    //
    //    for (auto i = size_t{0}; i < test.size(); i++) {
    //        std::cout << test[i][i] << "\n";
    //    }
    //
    //    test[0].push_back(4);
    //    std::cout << test[0][3] << "\n";
    //

    //    auto test = std::vector<std::vector<int>>{{1, 2, 3},{4,5,6},{7, 8,
    //    9}}; auto test_pomniejszony = std::vector<int>{};
    //
    //    for (auto each : test) {
    //
    //        test_pomniejszony.reserve(test_pomniejszony.size() + each.size());
    //        test_pomniejszony.insert(test_pomniejszony.end(), each.begin(),
    //        each.end());
    //
    //    }
    //
    //    std::cout << test_pomniejszony.size() << "\n";
    //    for (auto each : test_pomniejszony) {
    //        std::cout << each << "\n";
    //    }
    //
    //    struct length {
    //        bool operator() ( const int& a, const int& b )
    //        {
    //            auto x = std::to_string(a).length();
    //            auto y = std::to_string(b).length();
    //            return x < y;
    //        }
    //
    //    };
    //    auto test = std::vector<int>{12, 243, 33, 41,5,-163, 7, 8, 9 };
    //    std::cout << std::to_string(*max_element(test.begin(),
    //    test.end())).length() << "\n";
    //
    //

    //    std::cout << std::setw(4) << std::setfill('.') << "";
    //    std::cout << "test";
    //
    //    auto test = int{5};
    //    std::cout << (test > 0 ? "(" :) << test << (test > 0 ? ")" :);

    auto previous_time = std::chrono::steady_clock::now();

    while (true) {
        auto current_time = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(current_time
                                                             - previous_time)
                .count()
            >= 5) {
            break;
        }
    }

    std::cout << "ok!\n";

    return 0;
}
