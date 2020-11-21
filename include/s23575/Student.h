#ifndef S23575_STUDENT_H
#define S23575_STUDENT_H

#include <sstream>
#include <string>

namespace s23575 {

struct Student {
    std::string imie;
    std::string nazwisko;
    std::string indeks;
    constexpr static unsigned SEMESTR = 1;
    unsigned semestr{SEMESTR};
    constexpr static double SREDNIA = 0.00;
    double srednia{SREDNIA};

    Student(std::string,
            std::string,
            std::string,
            unsigned const = SEMESTR,
            double const   = SREDNIA);

    auto to_string() const -> std::string;
};

}

#endif
