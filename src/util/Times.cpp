#include "Times.h"


void Times::timeAdvice(Runnable *runnable) {
    std::cout << timing(runnable) / 1000 << " ms" << std::endl;
}

double Times::timing(Runnable *runnable) {
    if (runnable == nullptr) {
        throw NullPointException();
    }
    auto start = std::chrono::system_clock::now();
    runnable->run();
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return double(duration.count());
}

int Times::millionTime(void (*fun)()) {
    clock_t start = std::clock();
    // fun();
    clock_t end = std::clock();
    return (int) (end - start);
}


