#ifndef S23575_MACIERZ_H
#define S23575_MACIERZ_H

#include <vector>

namespace s23575 {

struct Element_Macierzy {
    constexpr static int WIERSZ = 0;
    int wiersz{WIERSZ};
    constexpr static int KOLUMNA = 0;
    int kolumna{KOLUMNA};
    constexpr static int WARTOSC = 0;
    int wartosc{wartosc};

    Element_Macierzy(int const = WIERSZ,
                     int const = KOLUMNA,
                     int const = WARTOSC);
};

struct Macierz {
    std::vector<Element_Macierzy> zawartosc;
    constexpr static int WIELKOSC = 0;
    int wielkosc{WIELKOSC};

    Macierz(std::vector<Element_Macierzy>, int const = WIELKOSC);

    auto drukuj_macierz(Macierz) const -> void;
};

}  // namespace s23575

#endif
