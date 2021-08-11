#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

#define LIMIT 2147483647
#define THREAD_COUNT 8

atomic<uint64_t> total;
atomic<uint64_t> counter;

void collatz() {
    uint64_t n;

    while((n = counter++) <= LIMIT) {
        while(n != 1) {
            while(n & 1) {
                n = (3 * n + 1) / 2;
            }
            while(!(n & 1)) {
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
        cout << "Usage: ./collatz" << endl;
        exit(1);
    }

    thread t[THREAD_COUNT];

    auto t1 = chrono::high_resolution_clock::now();

    for (int i = 0; i < THREAD_COUNT; i++) {
        t[i] = thread(collatz);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        t[i].join();
    }

    auto t2 = chrono::high_resolution_clock::now();

    cout << "Program Statistics: " << endl;
    cout << "\tThread Count: " << THREAD_COUNT << endl;
    cout << "\tLimit Value: " << LIMIT << endl;
    cout << "\tCollatz Numbers: " << total << endl;

    cout << "Program took: " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " milliseconds" << endl;

    return 0;
}