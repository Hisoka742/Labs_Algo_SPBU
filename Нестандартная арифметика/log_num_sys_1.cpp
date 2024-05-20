#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <functional>

// Шаблонный класс для логарифмической системы счисления
template<typename B = double>
class log_num_sys {
public:
    B value; // Храним значение в логарифмическом виде

    // Конструктор по умолчанию
    log_num_sys() : value(0) {}

    // Конструктор от числа
    log_num_sys(B v) : value(std::log(v)) {}

    // Конструктор от логарифма
    static log_num_sys<B> from_log(B log_value) {
        log_num_sys<B> res;
        res.value = log_value;
        return res;
    }

    // Перегрузка оператора +
    log_num_sys<B> operator+(const log_num_sys<B>& other) const {
        B max_val = std::max(value, other.value);
        B result = max_val + std::log1p(std::exp(std::min(value, other.value) - max_val));
        return from_log(result);
    }

    // Перегрузка оператора -
    log_num_sys<B> operator-(const log_num_sys<B>& other) const {
        if (value < other.value) {
            throw std::invalid_argument("Result of subtraction is negative in log_num_sys.");
        }
        B result = value + std::log1p(-std::exp(other.value - value));
        return from_log(result);
    }

    // Перегрузка оператора *
    log_num_sys<B> operator*(const log_num_sys<B>& other) const {
        return from_log(value + other.value);
    }

    // Перегрузка оператора /
    log_num_sys<B> operator/(const log_num_sys<B>& other) const {
        return from_log(value - other.value);
    }

    // Преобразование обратно в обычное число
    B to_value() const {
        return std::exp(value);
    }
};

// Функция для тестирования арифметических операций
void test_arithmetic() {
    log_num_sys<> a(2.0);
    log_num_sys<> b(8.0);

    auto sum = a + b;
    auto diff = b - a;
    auto prod = a * b;
    auto quot = b / a;

    std::cout << "a = " << a.to_value() << "\n";
    std::cout << "b = " << b.to_value() << "\n";
    std::cout << "a + b = " << sum.to_value() << "\n";
    std::cout << "b - a = " << diff.to_value() << "\n";
    std::cout << "a * b = " << prod.to_value() << "\n";
    std::cout << "b / a = " << quot.to_value() << "\n";
}

// Основная функция
int main() {
    test_arithmetic();
    return 0;
}


