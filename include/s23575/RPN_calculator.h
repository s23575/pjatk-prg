#ifndef S23575_RPN_CALCULATOR_H
#define S23575_RPN_CALCULATOR_H

#include <memory>
#include <queue>
#include <stack>


namespace s23575 { namespace rpn_calculator {
using stack_type = std::stack<double>;

struct Element {
    virtual auto evaluate(stack_type&) const -> void = 0;
    virtual ~Element();
};

struct Literal : public Element {
    double const value{0.0};

    auto evaluate(stack_type&) const -> void override;

    Literal(double const);
};

struct Print : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Addition : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Subtraction : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Multiplication : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Division : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Division_Integers : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Reminder : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Exponentiation : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Square_Root : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Seconds_To_Hours : public Element {
    auto evaluate(stack_type&) const -> void override;
};

struct Calculator {
    stack_type stack;
    std::queue<std::unique_ptr<Element>> ops;

    /*
     * Schedule operation for evaluation.
     */
    auto push(std::unique_ptr<Element>) -> void;

    /*
     * Convert string to element and push it on the queue of operations to
     * perform.
     */
    auto push(std::string) -> void;

    /*
     * Evaluate scheduled operations.
     */
    auto evaluate() -> void;

    Calculator() = default;
    Calculator(stack_type);
};
}}  // namespace s23575::rpn_calculator

#endif
