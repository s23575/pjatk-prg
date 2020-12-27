#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <string>
#include <thread>

auto print_stuff_from_queue(std::queue<std::string>& kolejka,
                            std::mutex& mtx,
                            int const id) -> void

{
    std::random_device rd;
    std::uniform_int_distribution<int> losowa_liczba(10, 100);

    auto s = std::string{};

    while (true) {
        std::unique_lock<std::mutex> lck{mtx};

        if (kolejka.empty()) {
            lck.unlock();
            std::this_thread::sleep_for(
                std::chrono::milliseconds(losowa_liczba(rd)));
            continue;
        }

        s = kolejka.front();

        kolejka.pop();

        if (s.empty()) {
            std::cout << "thread No. " << id << " exiting\n";
            break;

        } else {
            std::cout << "from thread No. " << id << " : " << s << "\n";
        }
    }
}


auto main() -> int
{
    auto kolejka = std::queue<std::string>{};

    auto threads_vector = std::vector<std::thread>{};

    std::mutex mtx;

    auto i = int{};

    const int liczba_watkow = 4;

    for (i = 0; i < liczba_watkow; i++) {
        threads_vector.push_back(std::thread(
            print_stuff_from_queue, std::ref(kolejka), std::ref(mtx), i));
    }

    auto j = int{0};

    auto s = std::string{};

    while (j < liczba_watkow) {
        std::getline(std::cin, s);

        if (s.empty()) {
            j++;
        }

        {
            std::unique_lock<std::mutex> lck{mtx};
            kolejka.push(std::move(s));
        }
    }

    for (i = 0; i < liczba_watkow; i++) {
        threads_vector[i].join();
    }

    return 0;
}
