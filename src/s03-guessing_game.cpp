#include <iostream>
#include <random>
#include <string>

auto ask_user_for_integer(std::string prompt) -> int
{
    std::cout << prompt;
    auto liczba = std::string{};
    std::getline(std::cin, liczba);

    try {
        return std::stoi(liczba);
    } catch (std::invalid_argument&) {
        std::cerr << "Błąd! Nie podano liczby całkowitej - spróbuj ponownie.\n";
        return ask_user_for_integer("Podaj liczbę: ");
    }
}

int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> losowa_liczba(1, 100);

    auto wylosowana_liczba = int{losowa_liczba(rd)};

    std::cout << "Zgadnij wylosowaną liczbę całkowitą od 1 do 100!\n";

    auto liczba_uzytkownika = int{};

    do {
        liczba_uzytkownika = ask_user_for_integer("Podaj liczbę: ");

        if (liczba_uzytkownika > wylosowana_liczba) {
            std::cout << "Podana liczba jest za duża!\n";
        } else {
            if (liczba_uzytkownika < wylosowana_liczba) {
                std::cout << "Podana liczba jest za mała!\n";
            }
        }

    } while (liczba_uzytkownika != wylosowana_liczba);

    std::cout << "Zgadłeś! Wylosowana liczba to: " << wylosowana_liczba
              << ".\n";

    return 0;
}
