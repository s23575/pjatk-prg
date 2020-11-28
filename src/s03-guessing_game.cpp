#include <iostream>
#include <random>
#include <string>

auto ask_user_for_integer(std::string prompt) -> int
{
    std::cout << prompt;
    auto liczba = std::string{};
    std::getline(std::cin, liczba);

    return std::stoi(liczba);
}

int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> losowa_liczba(1, 100);

    auto const wylosowana_liczba = losowa_liczba(rd);

    std::cout << "Zgadnij wylosowaną liczbę całkowitą od 1 do 100!\n";

    auto liczba_uzytkownika = int{}, liczba_blednych_prob = int{},
         liczba_prob = int{};

    do {
        try {
            liczba_uzytkownika = ask_user_for_integer("Podaj liczbę: ");
        } catch (std::invalid_argument&) {
            liczba_blednych_prob = liczba_blednych_prob + 1;
            if (liczba_blednych_prob < 3) {
                std::cerr << "Błąd! Nie podano liczby całkowitej - spróbuj "
                             "ponownie.\n";
                continue;
            } else {
                std::cerr
                    << "Błąd! Nie podano liczby całkowitej zbyt wiele razy.\n";
                return 0;
            }
        }
        liczba_blednych_prob = 0;

        if (liczba_uzytkownika > wylosowana_liczba) {
            std::cout << "Podana liczba jest za duża!\n";
        } else {
            if (liczba_uzytkownika < wylosowana_liczba) {
                std::cout << "Podana liczba jest za mała!\n";
            }
        }

        liczba_prob = liczba_prob + 1;
        if (liczba_prob == 100) {
            break;
        }

    } while (liczba_uzytkownika != wylosowana_liczba);

    if (liczba_prob == 100) {
        std::cout << "Nie udało się - zbyt wiele nieudanych prób.\n";
    } else {
        std::cout << "Zgadłeś! Wylosowana liczba to: " << wylosowana_liczba
                  << ".\n";
    }

    return 0;
}
