#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cerr << "Błąd! W wierszu poleceń nie podano argumentu (hasła).\n";
        return 1;
    }

    auto const haslo       = argv[1];
    auto haslo_uzytkownika = std::string{};

    do {
        std::cout << "Podaj hasło: ";
        std::getline(std::cin, haslo_uzytkownika);

    } while (haslo_uzytkownika != haslo);

    std::cout << "Hasło prawidłowe!\n";

    return 0;
}
