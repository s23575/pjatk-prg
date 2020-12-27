#include <condition_variable>
#include <iostream>
#include <mutex>
#include <optional>
#include <random>
#include <string>
#include <thread>
#include <vector>

// Poniższą funkcję i obsługę błędu w funkcji "main" wykorzystałem (dostosowując
// odpowiednio) z zadania "s03-guessing-game.bin"

auto ask_user_for_integer(std::string prompt) -> std::optional<int>
{
    auto liczba_wprowadzona = std::string{};

    for (int i = 0, j = 3; i < j; i++) {
        std::cout << prompt;

        try {
            std::getline(std::cin, liczba_wprowadzona);
            return std::stoi(liczba_wprowadzona);
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

auto ping_pong(int& liczba,
               std::mutex& mtx,
               std::condition_variable& cv,
               std::string id,
               int& koniec) -> void
{
    std::random_device rd;
    std::uniform_int_distribution<int> losowa_liczba(1, 42);

    auto biezaca_liczba = std::optional<int>{};

    while (true) {
        // Poniższa funkcja "if" służy zabezpieczeniu, aby ten sam wątek nie
        // "wyprzedzał" drugiego i nie zwracał liczby kilka razy pod rząd - stąd
        // jeżeli liczba jest równa ostatniej, wydrukowanej przez ten wątek
        // liczbie
        // ("biezaca_liczba), to pętla jest jednorazowo przerywana ("continue").

        if (liczba == biezaca_liczba) {
            continue;
        }

        std::unique_lock<std::mutex> lck{mtx};

        cv.wait(lck);

        liczba = liczba + losowa_liczba(rd);

        if (liczba > 1024) {
            break;
        }

        std::cout << id << " : " << liczba << "\n";

        biezaca_liczba = liczba;

        lck.unlock();

        cv.notify_one();
    }

    koniec++;
    std::cout << "Koniec " << id << "\n";
}

auto main() -> int
{
    auto liczba = int();

    auto liczba_uzytkownika = std::optional<int>{};

    auto koniec = int{};

    auto threads_vector = std::vector<std::thread>{};

    const std::vector<std::string> nazwy = {"Ping", "Pong"};

    std::mutex mtx;

    std::condition_variable cv;

    auto i = int{};

    const int liczba_watkow = 2;

    for (i = 0; i < liczba_watkow; i++) {
        threads_vector.push_back(std::thread(ping_pong,
                                             std::ref(liczba),
                                             std::ref(mtx),
                                             std::ref(cv),
                                             nazwy[i],
                                             std::ref(koniec)));
    }

    {
        std::unique_lock<std::mutex> lck{mtx};

        liczba_uzytkownika = ask_user_for_integer("Podaj liczbę: ");

        if (not liczba_uzytkownika.has_value()) {
            std::cerr
                << "Błąd! Nie podano liczby całkowitej zbyt wiele razy.\n";
            for (i = 0; i < liczba_watkow; i++) {
                threads_vector[i].detach();
            }
            return 1;
        } else {
            liczba = *liczba_uzytkownika;
        }
    }

    while (koniec < liczba_watkow) {
        cv.notify_one();
    }

    for (i = 0; i < liczba_watkow; i++) {
        threads_vector[i].join();
    }

    return 0;
}
