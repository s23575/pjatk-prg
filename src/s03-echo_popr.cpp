#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    auto liczba_argumentow = int{argc};

    if (liczba_argumentow == 1) {
        std::cerr << "Błąd! Nie podano żadnych argumentów.\n";
        return 1;
    }

    auto args = std::vector<std::string>{};
    std::copy(argv + 1, argv + argc, std::back_inserter(args));

    auto separator     = std::string{" "};
    auto terminator    = std::string{"\n"};
    auto reverse_order = false;

    auto operands_to_print = std::vector<std::string>{};
    for (auto operand_start = size_t{0}; operand_start < args.size();
         ++operand_start) {
        auto const& each = args.at(operand_start);
        if (each == "-r") {
            reverse_order = true;
        } else if (each == "-n") {
            terminator = "";
        } else if (each == "-l") {
            separator = "\n";
        } else {
            std::copy(args.begin() + operand_start,
                      args.end(),
                      std::back_inserter(operands_to_print));
            break;
        }
    }

    if (reverse_order) {
        std::reverse(operands_to_print.begin(), operands_to_print.end());
    }

    if (operands_to_print.empty()) {
        std::cout << terminator;
        return 0;
    }

    //    std::cout << operands_to_print.at(0);
    //    for (auto i = size_t{1}; i < operands_to_print.size(); ++i) {

    for (auto i = size_t{0}; i < operands_to_print.size(); ++i) {
        std::cout << operands_to_print.at(i);
        if (i + 1 == operands_to_print.size()) {
            std::cout << separator;
        }
    }

    std::cout << terminator;

    return 0;
}
