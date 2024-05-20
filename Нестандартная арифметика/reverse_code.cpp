#include <iostream>
#include <limits>
#include <type_traits>

template<typename BASE>
class ones_compl_int {
    static_assert(std::is_integral<BASE>::value, "BASE must be an integral type");

    BASE value;

    // Преобразование числа в обратный код
    BASE toOnesComplement(BASE val) const {
        return ~val;
    }

    // Преобразование числа из обратного кода в прямой
    BASE fromOnesComplement(BASE val) const {
        return ~val;
    }

public:
    // Конструкторы
    ones_compl_int() : value(0) {}
    ones_compl_int(BASE val) : value(toOnesComplement(val)) {}

    // Оператор присваивания
    ones_compl_int& operator=(BASE val) {
        value = toOnesComplement(val);
        return *this;
    }

    // Получение значения в прямом коде
    BASE get() const {
        return fromOnesComplement(value);
    }

    // Арифметические операторы
    ones_compl_int operator+(const ones_compl_int& other) const {
        return ones_compl_int(fromOnesComplement(value) + fromOnesComplement(other.value));
    }

    ones_compl_int operator-(const ones_compl_int& other) const {
        return ones_compl_int(fromOnesComplement(value) - fromOnesComplement(other.value));
    }

    ones_compl_int operator*(const ones_compl_int& other) const {
        return ones_compl_int(fromOnesComplement(value) * fromOnesComplement(other.value));
    }

    ones_compl_int operator/(const ones_compl_int& other) const {
        return ones_compl_int(fromOnesComplement(value) / fromOnesComplement(other.value));
    }

    // Операторы сравнения
    bool operator==(const ones_compl_int& other) const {
        return value == other.value;
    }

    bool operator!=(const ones_compl_int& other) const {
        return value != other.value;
    }

    bool operator<(const ones_compl_int& other) const {
        return fromOnesComplement(value) < fromOnesComplement(other.value);
    }

    bool operator<=(const ones_compl_int& other) const {
        return fromOnesComplement(value) <= fromOnesComplement(other.value);
    }

    bool operator>(const ones_compl_int& other) const {
        return fromOnesComplement(value) > fromOnesComplement(other.value);
    }

    bool operator>=(const ones_compl_int& other) const {
        return fromOnesComplement(value) >= fromOnesComplement(other.value);
    }

    // Ввод и вывод
    friend std::ostream& operator<<(std::ostream& os, const ones_compl_int& num) {
        os << num.get();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, ones_compl_int& num) {
        BASE val;
        is >> val;
        num = ones_compl_int(val);
        return is;
    }
};

// Пример использования
int main() {
    ones_compl_int<int32_t> a, b;

    std::cout << "Input For  a: ";
    std::cin >> a;

    std::cout << "Input For  b: ";
    std::cin >> b;

    std::cout << "a: " << a << "\n";
    std::cout << "b: " << b << "\n";

    ones_compl_int<int32_t> c = a + b;
    std::cout << "a + b: " << c << "\n";

    return 0;
}

