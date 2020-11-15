#include <iostream>

int main(int argc, char* argv[])
{
    auto liczba_butelek = int{};

    if (argc > 1) {
        try {
            liczba_butelek = std::stoi(argv[1]);
        } catch (std::invalid_argument&) {
            std::cerr
                << "Błąd! Argument podany w wierszu poleceń nie jest dodatnią "
                   "liczbą całkowitą.\n";
            return 1;
        }
    } else {
        liczba_butelek = 99;
    }

    if (liczba_butelek < 0) {
        std::cerr << "Błąd! Podana liczba całkowita nie jest dodatnia.\n";
        return 1;
    }

    for (auto i = liczba_butelek; i >= 1; i--) {
        std::cout << i << " bottles of beer on the wall, " << i
                  << " bottles of beer.\nTake one down, pass it around, "
                  << i - 1 << " bottles of beer on the wall...\n";
    }

    std::cout
        << "No more bottles of beer on the wall, no more bottles of beer.\nGo "
           "to the store and buy some more, "
        << liczba_butelek << " bottles of beer on the wall...\n";

    return 0;
}
