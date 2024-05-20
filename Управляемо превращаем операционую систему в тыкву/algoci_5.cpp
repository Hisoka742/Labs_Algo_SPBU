#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstring>
#include <cstdlib>
#include <sstream>

const size_t PAGE_SIZE = 4096;  // Размер страницы в байтах (4 KiB)
volatile char global_var;       // Глобальная переменная для чтения

void usage(const char* algoci_5) {
    std::cout << "Usage: " << algoci_5 << " <mode> <total_memory_mb> <delay_ms>\n";
    std::cout << "Modes: read, write\n";
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        usage(argv[0]);
        return 1;
    }

    std::string mode = argv[1];
    size_t total_memory_mb;
    int delay_ms;

    // Преобразование строки в число
    std::istringstream total_memory_mb_stream(argv[2]);
    total_memory_mb_stream >> total_memory_mb;
    std::istringstream delay_ms_stream(argv[3]);
    delay_ms_stream >> delay_ms;

    if (mode != "read" && mode != "write") {
        usage(argv[0]);
        return 1;
    }

    size_t total_memory = total_memory_mb * 1024 * 1024;
    size_t num_pages = total_memory / PAGE_SIZE;

    std::vector<char*> memory_blocks;

    try {
        // Выделяем память
        for (size_t i = 0; i < num_pages; ++i) {
            char* block = new char[PAGE_SIZE];
            if (!block) {
                throw std::bad_alloc();
            }
            memory_blocks.push_back(block);

            // Делаем задержку каждые 1000 страниц
            if (i % 1000 == 0 && i > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
            }
        }

        std::cout << "Allocated " << total_memory_mb << " MB of memory.\n";

        // Обращение к памяти
        for (size_t i = 0; i < num_pages; ++i) {
            if (mode == "write") {
                std::memset(memory_blocks[i], 1, PAGE_SIZE); // Записываем в память
            }
            else if (mode == "read") {
                for (size_t j = 0; j < PAGE_SIZE; ++j) {
                    global_var = memory_blocks[i][j]; // Читаем из памяти
                }
            }

            // Делаем задержку каждые 1000 страниц
            if (i % 1000 == 0 && i > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
            }
        }

        std::cout << "Memory access complete.\n";
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << '\n';
        for (auto block : memory_blocks) {
            delete[] block;
        }
        return 1;
    }

    // Очистка выделенной памяти
    for (auto block : memory_blocks) {
        delete[] block;
    }

    return 0;
}


