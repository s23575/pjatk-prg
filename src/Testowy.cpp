#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

auto main() -> int
{
    auto macierz_dane =
        std::vector<int>{3, -2, 0, 5, -2, 1, -2, 0, 0, -2, 5, 3, 5, 2, 0, 4};

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

    return 0;
}
