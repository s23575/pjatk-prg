#include <cmath>
#include <iostream>
#include <string>
#include <vector>

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

auto main() -> int
{
    auto macierz = std::vector<std::vector<int>>{
        {3, -2, 0, 5}, {-2, 1, -2, 0}, {0, -2, 5, 3}, {5, 2, 0, 4}};

    std::cout << oblicz_wyznacznik(macierz) << "\n";

    return 0;
}
