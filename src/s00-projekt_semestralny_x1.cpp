#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>


/*
auto oblicz_wyznacznik(std::vector<std::vector<int>> macierz) -> int
{
    auto wyznacznik = int{};

    auto macierz_dwa = std::vector<std::vector<int>>{};

    auto macierz_trzy = std::vector<std::vector<int>>{};


    if (macierz.size() == 1) {
        wyznacznik = macierz[0][0];

    } else {
        macierz_dwa = macierz;

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
    }

    return wyznacznik;
}
*/
auto main() -> int
{
    auto macierz_dane =
        std::vector<int>{1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4};

    auto macierz_1 = std::vector<std::vector<int>>{};
    auto macierz_2 = std::vector<std::vector<int>>{};

    auto licznik = int(sqrt(macierz_dane.size()));

    for (auto i = int{0}; i < licznik; i++) {
        //        auto wiersz = std::vector<int>{macierz_dane.begin() + (i *
        //        licznik), macierz_dane.begin() + ((i * licznik) + licznik)};

        auto wiersz_1 = std::vector<int>{
            &macierz_dane[i * licznik], &macierz_dane[(i * licznik) + licznik]};

        macierz_1.push_back(wiersz_1);
    }

    for (auto each_1 : macierz_1) {
        for (auto each_2 : each_1) {
            std::cout << "| " << each_2 << "\t";
        }

        std::cout << " |\n";
    }

    for (auto j = int{0}; j < licznik; j++) {
        auto wiersz_2 = std::vector<int>{};

        for (auto each_1 : macierz_1) {
            wiersz_2.push_back(each_1[j]);
        }

        macierz_2.push_back(wiersz_2);
    }

    std::cout << "transponowana:\n";

    for (auto each_1 : macierz_2) {
        for (auto each_2 : each_1) {
            std::cout << "| " << each_2 << "\t";
        }

        std::cout << " |\n";
    }

    std::cout << "\033[1;31mtestowy\033[0m\n";

    /*
       auto macierz = std::vector<std::vector<int>>{
           {0, 0, -1, 5}, {0, 3, 1, 4}, {12, 0, 0, -2}, {4, 0, 15, 0}};

       std::cout << oblicz_wyznacznik(macierz) << "\n";
   */
    return 0;
}
