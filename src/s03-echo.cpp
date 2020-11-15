#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    auto liczba_argumentow = int{argc};

    if (liczba_argumentow == 1) {
        std::cerr << "Błąd! Nie podano żadnych argumentów.\n";
        return 1;
    }

    auto argument = std::string{};

    auto opcja_n = bool{};
    auto opcja_r = bool{};
    auto opcja_l = bool{};

    auto numer_argumentu = int{1};

    for (numer_argumentu = 1; numer_argumentu < 3; numer_argumentu++) {
        argument = argv[numer_argumentu];
        if (argument.at(0) == '-' && argument.length() == 2) {
            if (argument.at(1) == 'n' && opcja_n == 0 && opcja_l == 0) {
                opcja_n = true;
            } else if (argument.at(1) == 'r' && numer_argumentu == 1) {
                opcja_r = true;
            } else if (argument.at(1) == 'l' && opcja_l == 0 && opcja_n == 0) {
                opcja_l = true;
            } else {
                break;
            }
            if (numer_argumentu == liczba_argumentow - 1) {
                std::cerr
                    << "Błąd! Nie podano żadnych argumentów (poza opcjami).\n";
                return 1;
            }
        } else {
            break;
        }
    }

    do {
        if (opcja_r == 1) {
            std::cout << argv[liczba_argumentow - 1] << " ";
            liczba_argumentow = liczba_argumentow - 1;
        } else {
            std::cout << argv[numer_argumentu] << " ";
            numer_argumentu = numer_argumentu + 1;
        }
        if (opcja_l == 1) {
            std::cout << "\n";
        }
    } while (liczba_argumentow != numer_argumentu);

    if (opcja_n == 0) {
        std::cout << "\n";
    }

    return 0;
}
