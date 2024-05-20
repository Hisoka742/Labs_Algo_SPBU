#include <iostream>
#include <type_traits>
#include <cstdint>
#include <cmath>

template<typename B = int32_t, unsigned FRAC = 16>
class fixed_point {
    static_assert(std::is_integral<B>::value, "B must be an integral type");
    static_assert(FRAC < sizeof(B) * 8, "FRAC must be less than the number of bits in B");

    B value;

    // Константы для преобразовании
    static constexpr B FRACTIONAL_MASK = (1 << FRAC) - 1;
    static constexpr B FRACTIONAL_FACTOR = 1 << FRAC;

public:
    // Конструкторы
    fixed_point() : value(0) {}

    fixed_point(double d) {
        value = static_cast<B>(std::round(d * FRACTIONAL_FACTOR));
    }

    // Оператор присваивания
    fixed_point& operator=(double d) {
        value = static_cast<B>(std::round(d * FRACTIONAL_FACTOR));
        return *this;
    }

    // Получение значения в вид double
    double to_double() const {
        return static_cast<double>(value) / FRACTIONAL_FACTOR;
    }

  
    fixed_point operator+(const fixed_point& other) const {
        return fixed_point::from_raw(value + other.value);
    }

    fixed_point operator-(const fixed_point& other) const {
        return fixed_point::from_raw(value - other.value);
    }

    fixed_point operator*(const fixed_point& other) const {
        return fixed_point::from_raw((static_cast<int64_t>(value) * other.value) >> FRAC);
    }

    fixed_point operator/(const fixed_point& other) const {
        return fixed_point::from_raw((static_cast<int64_t>(value) << FRAC) / other.value);
    }

  
    bool operator==(const fixed_point& other) const {
        return value == other.value;
    }

    bool operator!=(const fixed_point& other) const {
        return value != other.value;
    }

    bool operator<(const fixed_point& other) const {
        return value < other.value;
    }

    bool operator<=(const fixed_point& other) const {
        return value <= other.value;
    }

    bool operator>(const fixed_point& other) const {
        return value > other.value;
    }

    bool operator>=(const fixed_point& other) const {
        return value >= other.value;
    }

 
    friend std::ostream& operator<<(std::ostream& os, const fixed_point& num) {
        os << num.to_double();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, fixed_point& num) {
        double d;
        is >> d;
        num = fixed_point(d);
        return is;
    }

private:
   
    static fixed_point from_raw(B raw_value) {
        fixed_point fp;
        fp.value = raw_value;
        return fp;
    }
};


int main() {
    fixed_point<int32_t, 16> a, b;

    std::cout << "Введите значение для a: ";
    std::cin >> a;

    std::cout << "Введите значение для b: ";
    std::cin >> b;

    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";

    fixed_point<int32_t, 16> c = a + b;
    std::cout << "a + b: " << c << "\n";

    fixed_point<int32_t, 16> d = a - b;
    std::cout << "a - b: " << d << "\n";

    fixed_point<int32_t, 16> e = a * b;
    std::cout << "a * b: " << e << "\n";

    fixed_point<int32_t, 16> f = a / b;
    std::cout << "a / b: " << f << "\n";

    return 0;
}
