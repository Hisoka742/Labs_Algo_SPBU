#include <iostream>
#include <chrono>
#include <vector>

const int SIZE = 1024; // Размер матрицы 1024x1024

// Функция для заполнения матрицы
void fill_matrix(std::vector<std::vector<int>>& matrix) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            matrix[i][j] = i + j;
        }
    }
}

// Функция для подсчета суммы элементов матрицы при обходе по строкам
long long sum_by_rows(const std::vector<std::vector<int>>& matrix) {
    long long sum = 0;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

// Функция для подсчета суммы элементов матрицы при обходе по столбцам
long long sum_by_columns(const std::vector<std::vector<int>>& matrix) {
    long long sum = 0;
    for (int j = 0; j < SIZE; ++j) {
        for (int i = 0; i < SIZE; ++i) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

int main() {
    std::vector<std::vector<int>> matrix(SIZE, std::vector<int>(SIZE));
    fill_matrix(matrix);

    // Обход по строкам
    auto start = std::chrono::high_resolution_clock::now();
    long long sum_rows = sum_by_rows(matrix);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_rows = end - start;
    std::cout << "Sum by rows: " << sum_rows << " in " << duration_rows.count() << " seconds.\n";

    // Обход по столбцам
    start = std::chrono::high_resolution_clock::now();
    long long sum_columns = sum_by_columns(matrix);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_columns = end - start;
    std::cout << "Sum by columns: " << sum_columns << " in " << duration_columns.count() << " seconds.\n";

    return 0;
}

