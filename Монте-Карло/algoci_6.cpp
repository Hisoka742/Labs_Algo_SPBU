#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>
#include <atomic>
#include <sstream>

void usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " <number_of_threads> <number_of_points>\n";
}

void monte_carlo_pi(int points_per_thread, std::atomic<int>& inside_circle) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    int local_inside_circle = 0;
    for (int i = 0; i < points_per_thread; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        if (x * x + y * y <= 1.0) {
            ++local_inside_circle;
        }
    }
    inside_circle += local_inside_circle;
}

int string_to_int(const std::string& str) {
    std::stringstream ss(str);
    int result;
    ss >> result;
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        usage(argv[0]);
        return 1;
    }

    int num_threads = string_to_int(argv[1]);
    int num_points = string_to_int(argv[2]);

    if (num_threads <= 0 || num_points <= 0) {
        usage(argv[0]);
        return 1;
    }

    std::atomic<int> inside_circle(0);
    int points_per_thread = num_points / num_threads;

    std::vector<std::thread> threads;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(monte_carlo_pi, points_per_thread, std::ref(inside_circle));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    double pi = 4.0 * inside_circle / num_points;
    std::cout << "Estimated Pi = " << pi << "\n";
    std::cout << "Time taken = " << duration.count() << " seconds\n";

    return 0;
}
