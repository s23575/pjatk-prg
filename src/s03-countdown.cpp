#include <iostream>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cerr << "Błąd! W wierszu poleceń nie podano argumentu (dodatniej "
                     "liczby całkowitej).\n";
        return 1;
    }

    auto liczba = int{};

    try {
        liczba = std::stoi(argv[1]);
    } catch (std::invalid_argument&) {
        std::cerr
            << "Błąd! Argument podany w wierszu poleceń nie jest dodatnią "
               "liczbą całkowitą.\n";
        return 1;
    }

    if (liczba < 0) {
        std::cerr << "Błąd! Podana liczba całkowita nie jest dodatnia.\n";
        return 1;
    }

    for (auto i = liczba; i >= 0; i--) {
        std::cout << i << "...\n";
    }
    return 0;
}
