#ifndef S23575_MACIERZ_H
#define S23575_MACIERZ_H

#include <vector>

namespace s23575 {

struct Macierz {
    std::vector<int> elementy;
    constexpr static int ROZMIAR = 0;
    int rozmiar{ROZMIAR};
    constexpr static size_t ROZMIAR_ELEMENTU = 0;
    size_t rozmiar_elementu{ROZMIAR_ELEMENTU};

    Macierz(std::vector<int>,
            int const    = ROZMIAR,
            size_t const = ROZMIAR_ELEMENTU);

    auto drukuj_macierz() -> void;
    auto oblicz_wyznacznik() const -> int;
};

}  // namespace s23575

#endif
