#include <itp/channel.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

auto printer(itp::channel<std::string>& ch, int const id) -> void
{
    auto message = std::string{ch.wait()};

    while (not message.empty()) {
        std::cout << "from thread No. " << id << " : " << message << "\n";
        message = ch.wait();
    }

    std::cout << "thread No. " << id << " exiting\n";
}

auto main() -> int
{
    auto ch = itp::channel<std::string>{};

    auto threads_vector = std::vector<std::thread>();

    const int liczba_watkow = 4;

    for (auto i = int{0}; i < liczba_watkow; i++) {
        threads_vector.push_back(std::thread{printer, std::ref(ch), i});
    }

    auto message = std::string{};

    auto j = int{0};

    while (j < liczba_watkow) {
        std::getline(std::cin, message);

        ch.push(message);

        if (message.empty()) {
            j++;
        }
    }

    for (auto& each : threads_vector) {
        each.join();
    }

    return 0;
}
