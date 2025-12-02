#ifndef ALGORITHM_TIMES_H
#define ALGORITHM_TIMES_H

#include <chrono>
#include <iostream>
#include "../lang/exception/NullPointException.h"
#include "../lang/Runnable.h"

class Times {
public:
    static void timeAdvice(Runnable *runnable);

    static double timing(Runnable *runnable);

    static int millionTime(void (*fun)()) {
        clock_t start = std::clock();
        // fun();
        clock_t end = std::clock();
        return (int) (end - start);
    }
};


#endif //ALGORITHM_TIMES_H
