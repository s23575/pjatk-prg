#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

auto print_stuff_from_queue(std::queue<std::string>& kolejka,
                            std::mutex& mtx,
                            int const id) -> void

{
    auto i = std::string{};

    while (not kolejka.empty()) {
        {
            std::unique_lock<std::mutex> lck{mtx};

            i = kolejka.front();

            kolejka.pop();

            std::cout << "from thread No. " << id << " : " << i << "\n";

            lck.unlock();
        }
        // Poniższą funkcję sleep_for wprowadzam tylko ilustracyjnie, żeby każdy
        // z wątków miał okazję pobrać i wydrukować element z kolejki - w
        // przeciwnym wypadku, nawet mimo użycia "unlock()", najcześciej jeden
        // wątek drukował wszystkie elementy (lub większość elementów).

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

auto main() -> int
{
    auto kolejka = std::queue<std::string>{};

    auto threads_vector = std::vector<std::thread>{};

    std::mutex mtx;

    const int liczba_elementow = 40;
    const int liczba_watkow    = 4;

    for (auto i = int{0}; i < liczba_elementow; i++) {
        auto s = std::string{"queue element No. "} + std::to_string(i);

        kolejka.push(s);
    }

    for (auto j = int{0}; j < liczba_watkow; j++) {
        threads_vector.push_back(std::thread(
            print_stuff_from_queue, std::ref(kolejka), std::ref(mtx), j));
    }

    for (auto& each : threads_vector) {
        each.join();
    }

    return 0;
}
