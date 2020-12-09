#include <iostream>
#include <optional>
#include <random>
#include <string>

auto ask_user_for_integer(std::string prompt) -> std::optional<int>
{
    auto liczba = std::string{};

    for (int i = 0, j = 3; i < j; i++) {
        std::cout << prompt;

        try {
            std::getline(std::cin, liczba);
            return std::stoi(liczba);
        } catch (std::invalid_argument&) {
            if (i < j - 1) {  // Poniższy błąd nie powinien być zwracany w
                              // ostatnim cyklu pętli, stąd ten warunek.
                std::cerr << "Błąd! Nie podano liczby całkowitej - spróbuj "
                             "ponownie.\n";
            }
        }
    }

    return std::nullopt;
}

int main()
{
    std::random_device rd;
    std::uniform_int_distribution<int> losowa_liczba(1, 100);

    auto const wylosowana_liczba = losowa_liczba(rd);

    std::cout << "Zgadnij wylosowaną liczbę całkowitą od 1 do 100!\n";

    auto liczba_uzytkownika = std::optional<int>{};

    for (int i = 0, j = 100; i < j; i++) {
        std::cout << "Pozostało " << j - i << " prób.\n";

        liczba_uzytkownika = ask_user_for_integer("Podaj liczbę: ");

        if (not liczba_uzytkownika.has_value()) {
            std::cerr
                << "Błąd! Nie podano liczby całkowitej zbyt wiele razy.\n";
            return 1;
        } else {
            if (*liczba_uzytkownika > wylosowana_liczba) {
                std::cout << "Podana liczba jest za duża!\n";
            } else if (*liczba_uzytkownika < wylosowana_liczba) {
                std::cout << "Podana liczba jest za mała!\n";
            } else {
                std::cout << "Zgadłeś! Wylosowana liczba to: "
                          << wylosowana_liczba << ".\n";
                return 0;
            }
        }
    }

    std::cout << "Nie udało się - zbyt wiele nieudanych prób.\n";
    return 0;
}
