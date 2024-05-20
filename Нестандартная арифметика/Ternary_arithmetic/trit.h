#ifndef TRIT_H
#define TRIT_H

#include <iostream>
#include <cmath>
#include <stdexcept>


class trit {
public:
    enum Value { NEG = -1, ZERO = 0, POS = 1 };

    trit() : value(ZERO) {}
    trit(Value v) : value(v) {}

    Value get_value() const { return value; }

    friend std::ostream& operator<<(std::ostream& os, const trit& t) {
        if (t.value == NEG) os << "NEG";
        else if (t.value == ZERO) os << "ZERO";
        else os << "POS";
        return os;
    }

private:
    Value value;
};

class trit_num_sys {
public:
    trit_num_sys() : value(0.0) {}

    trit_num_sys(trit t) {
        switch (t.get_value()) {
        case trit::NEG:
            value = std::log(-1.0);
            break;
        case trit::ZERO:
            value = std::log(0.0);
            break;
        case trit::POS:
            value = std::log(1.0);
            break;
        }
    }

    trit_num_sys operator+(const trit_num_sys& other) const {
        double max_val = std::max(value, other.value);
        double result = max_val + std::log1p(std::exp(std::min(value, other.value) - max_val));
        return from_log(result);
    }

    trit_num_sys operator-(const trit_num_sys& other) const {
        double result = value + std::log1p(-std::exp(other.value - value));
        return from_log(result);
    }

    trit_num_sys operator*(const trit_num_sys& other) const {
        return from_log(value + other.value);
    }

    trit_num_sys operator/(const trit_num_sys& other) const {
        return from_log(value - other.value);
    }

    double to_value() const {
        return std::exp(value);
    }

    static trit_num_sys from_log(double log_value) {
        trit_num_sys res;
        res.value = log_value;
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const trit_num_sys& tns) {
        os << tns.to_value();
        return os;
    }

private:
    double value;
};

#endif // TRIT_H

