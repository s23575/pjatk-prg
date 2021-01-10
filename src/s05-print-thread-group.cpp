#include <iostream>
#include <string>
#include <thread>
#include <vector>

auto print_stuff(std::string x) -> void
{
    std::cout << (x + "\n");
}

auto main() -> int
{
    for (auto i = int{0}; i < 42;) {
        auto threads_vector = std::vector<std::thread>{};

        std::cout << "- - - Grupa " << i / 6 + 1 << " - - -\n";

        for (auto j = int{0}; j < 6; i++, j++) {
            auto s = std::string{"Hello, "} + std::to_string(i) + "!";

            threads_vector.push_back(std::thread(print_stuff, std::move(s)));
        }

        for (auto k = int{0}; k < 6; k++) {
            threads_vector[k].join();
        }
    }

    return 0;
}
