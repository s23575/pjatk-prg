#include <iostream>
#include <limits>


auto main() -> int
{
    enum Color { red, green, blue };

    Color r = green;

    switch (r) {
    case red:
        std::cout << "red\n";
        break;
    case green:
        std::cout << "green\n";
        break;
    case blue:
        std::cout << "blue\n";
        break;
    }

    return 0;
}
