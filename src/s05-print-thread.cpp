#include <iostream>
#include <string>
#include <thread>

auto print_stuff(std::string x) -> void
{
    std::cout << (x + "\n");
}

auto main() -> int
{
    for (auto i = 0; i < 42; i++) {
        auto s = std::string{"Hello, "} + std::to_string(i) + "!";

        auto t = std::thread{print_stuff, std::move(s)};

        t.detach();
    }

    return 0;
}
