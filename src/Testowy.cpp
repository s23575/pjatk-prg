#include <time.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

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

    std::default_random_engine rd;
    std::uniform_int_distribution<int> losowa_liczba(0, 100);
    std::uniform_int_distribution<int> losowa_liczba_2(losowa_liczba.param());

    std::cout << losowa_liczba(rd) << "\n";
    std::cout << losowa_liczba_2(rd) << "\n";


    return 0;
}
