#include <iostream>
#include <limits>


auto main() -> int
{
    auto a = int{7};
    a < 10 ? std::cout << "0" << a : std::cout << a;

    return 0;
}
