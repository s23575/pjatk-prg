#include <iostream>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cerr << "Błąd! W wierszu poleceń nie podano argumentu (liczby).\n";
        return 1;
    }

    auto liczba = int{};

    try {
        liczba = std::stoi(argv[1]);
    } catch (std::invalid_argument&) {
        std::cerr
            << "Błąd! Argument podany w wierszu poleceń nie jest liczbą.\n";
        return 1;
    }

    for (auto i = 1; i <= liczba; i++) {
        std::cout << i << " ";
        if (i % 3 == 0) {
            std::cout << "Fizz";
        }
        if (i % 5 == 0) {
            std::cout << "Buzz";
        }
        std::cout << "\n";
    }

    return 0;
}
