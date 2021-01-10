#ifndef S23575_RPN_CALCULATOR_H
#define S23575_RPN_CALCULATOR_H
#define RPN_OP_STRUCT(Op)                                  \
    struct Op : public Element {                           \
        auto evaluate(stack_type&) const -> void override; \
    }

#include <functional>
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

RPN_OP_STRUCT(Print);
RPN_OP_STRUCT(Addition);
RPN_OP_STRUCT(Subtraction);
RPN_OP_STRUCT(Multiplication);
RPN_OP_STRUCT(Division);
RPN_OP_STRUCT(Division_Integers);
RPN_OP_STRUCT(Reminder);
RPN_OP_STRUCT(Exponentiation);
RPN_OP_STRUCT(Square_Root);
RPN_OP_STRUCT(Seconds_To_Hours);

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
