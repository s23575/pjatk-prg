#include <s23575/Macierz.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

s23575::Element_Macierzy::Element_Macierzy(int const wi,
                                           int const ko,
                                           int const wa)
        : wiersz{wi}, kolumna{ko}, wartosc{wa}
{}

auto drukuj_macierz(std::vector<s23575::Element_Macierzy> macierz) -> void
{
    for (auto kazdy : macierz) {
        if (kazdy.kolumna == 1) {
            std::cout << "| ";
        }

        std::cout << kazdy.wartosc << " ";
        if (kazdy.kolumna == wielkosc_macierzy) {
            std::cout << "|\n";
        }
    }
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

    auto losowa_macierz    = bool{false};
    auto wielkosc_macierzy = int{0};

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
            } catch (const std::invalid_argument&) {
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

    auto macierz          = std::vector<s23575::Element_Macierzy>{};
    auto element_macierzy = s23575::Element_Macierzy{};

    if (losowa_macierz == true) {
    } else {
        for (auto i = int{1}; i <= wielkosc_macierzy; i++) {
            for (auto j = int{1}; j <= wielkosc_macierzy; j++) {
                if (j == 1) {
                    std::cout << "| ";
                }

                auto wpisana_wartosc = std::string{};
                std::getline(std::cin, wpisana_wartosc);
                element_macierzy =
                    s23575::Element_Macierzy{i, j, std::stoi(wpisana_wartosc)};
                macierz.push_back(element_macierzy);
                std::cout << "\n";

                //                for (auto kazdy : macierz) {
                //
                //                    if (kazdy.kolumna == 1) {
                //                        std::cout << "| ";
                //                    }
                //
                //                    std::cout << kazdy.wartosc << " ";
                //                    if (kazdy.kolumna == wielkosc_macierzy) {
                //
                //                        std::cout << "|\n";
                //
                //                    }
                //
                //                }
            }
        }
    }

    return 0;
}
