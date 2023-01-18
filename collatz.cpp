#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

const uint64_t LIMIT = 2147483647;
const uint64_t THREAD_COUNT = std::thread::hardware_concurrency();

std::atomic<uint64_t> total;
std::atomic<uint64_t> counter;

void collatz() {
    uint64_t n;

    while ((n = counter++) <= LIMIT) {
        while (n != 1) {
            while (n & 1) {
                n = (3 * n + 1) / 2;
            }
            while (!(n & 1)) {
                n /= 2;
            }
        }
        total++;
    }
}

int main(int argc, char *argv[]) {
    total = 0;
    counter = 1;

    if (argc != 1) {
        std::cout << "Usage: ./collatz" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Running, this may take some time..." << std::endl;

    std::thread *t = new std::thread[THREAD_COUNT];

    auto t1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < THREAD_COUNT; i++) {
        t[i] = std::thread(collatz);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        t[i].join();
    }

    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << "Program Statistics: " << std::endl;
    std::cout << "\tThread Count: " << THREAD_COUNT << std::endl;
    std::cout << "\tLimit Value: " << LIMIT << std::endl;
    std::cout << "\tCollatz Numbers: " << total << std::endl;

    std::cout << "\tRun-time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms" << std::endl;

    delete []t;
    return 0;
}