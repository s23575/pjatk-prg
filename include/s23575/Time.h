#ifndef S23575_TIME_H
#define S23575_TIME_H

#include <cstdint>
#include <sstream>
#include <string>

namespace s23575 {

struct Czas {
    constexpr static int GODZINA = 0;
    int godzina{GODZINA};
    constexpr static int MINUTA = 0;
    int minuta{MINUTA};
    constexpr static int SEKUNDA = 0;
    int sekunda{SEKUNDA};

    enum class Time_of_day { rano, dzien, wieczor, noc };

    Czas(int const = GODZINA, int const = MINUTA, int const = SEKUNDA);

    auto to_string() const -> std::string;

    auto next_hour() -> void;
    auto next_minute() -> void;
    auto next_second() -> void;

    auto validate_time() -> void;

    auto time_of_day() const -> Time_of_day;
    static auto to_string(Time_of_day const) -> std::string;

    auto operator+(Czas const&) const -> Czas;
    auto operator-(Czas const&) const -> Czas;
    auto operator<(Czas const&) const -> bool;
    auto operator>(Czas const&) const -> bool;
    auto operator==(Czas const&) const -> bool;
    auto operator!=(Czas const&) const -> bool;

    auto count_seconds() const -> uint64_t;
    auto count_minutes() const -> uint64_t;
    auto time_to_midnight() const -> Czas;
};

}  // namespace s23575

#endif
