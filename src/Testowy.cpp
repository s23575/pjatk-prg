/*#include <cmath>
#include <functional>
#include <iostream>

auto dzialanie(int liczba1, int liczba2, std::function<int(int,int)> funkcja) ->
void
{
    std::cout << funkcja(liczba1, liczba2) << "\n";
}

auto main() -> int
{
    dzialanie(1,2, std::pow());
    return 0;
}*/

#include <cmath>
#include <functional>
#include <iostream>
#include <optional>

auto test(double a, double b) -> double
{
    return a + b;
}

auto test_funkcja(double a,
                  double b,
                  std::function<double(double, double)> funkcja) -> void
{
    std::cout << funkcja(a, b);
}

int main()
{
    test_funkcja(5, 6, test);

    return 0;
}
