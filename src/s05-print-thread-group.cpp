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
    auto threads_vector = std::vector<std::thread>{};

    auto j = int{};
    auto i = int{};

    for (j = 0; j < 42;) {
        std::cout << "- - - Grupa " << j / 6 + 1 << " - - -\n";

        for (i = 0; i < 6; i++, j++) {
            auto s = std::string{"Hello, "} + std::to_string(j) + "!";

            threads_vector.push_back(std::thread(print_stuff, std::move(s)));
        }

        for (i = 0; i < 6; i++) {
            threads_vector[i].join();
        }

        threads_vector.clear();
    }

    return 0;
}
