/*
 * Ask the user for their credentials. Allow them to decline.
 */


#include <iostream>
#include <string>


auto main() -> int
{
    auto name = std::string{};

    do {
        std::cout << "password:";
        std::getline(std::cin, name);

    } while (name != "student");

    std::cout << "ok!\n";

    return 0;
}
