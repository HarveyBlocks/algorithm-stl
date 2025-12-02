#include "util/Arrays.h"
#include "util/sort/InsertionSort.h"
#include "util/Comparator.h"

int selectDemo() {
    Random::resetSeed();
    int length = 37;
    Array<int> test(length);
    Producer<int> producer = []() { return Random::signedInt() % 256; };
    ArrayInitializer::init(test, producer);
    std::cout << test << std::endl;
    int tail = Arrays::tail(test, 3);
    std::cout << tail << std::endl;
    std::cout << test << std::endl;
    InsertionSort(test).sort();
    std::cout << test << std::endl;
    std::cout << (test[3] == tail) << std::endl;
    return 0;
}

void checkFindCurrent(const Array<int> &test, int value, int index);

int findDemo() {
    Random::resetSeed();
    int length = 217;
    Array<int> test(length);

    const Compare<int> cmp = [](const int &a, const int &b) {
        return a - b;
    };

    Producer<int> producer = []() { return Random::signedInt() % 256; };
    int i = 10000;
    while (i--) {
        ArrayInitializer::init(test, producer);
        InsertionSort(test).sort();
        test[length - 1] = INT_MAX;

        int value = Random::signedInt() % 270;
        int index = Arrays::binarySearch(test, value, Comparators::GREATER<int>());

        if (index >= 0) {
            if (test[index] != value) {
                std::cout << "Not Find!" << std::endl;
                std::cout << test << std::endl;
                std::cout << "index: " << index << std::endl;
                std::cout << "value: " << value << std::endl;
            } else {
                // cout << "FIND SUCCESS" << endl;
                continue;
            }
        }
        Array<int> copy(length);
        test.clone(copy);

        index = -index - 1;
        // pushFront(index , value)
        for (int j = length - 1; j > index; --j) {
            test[j] = test[j - 1];
        }
        test[index] = value;

        if (!Arrays::checkSorted(test, cmp)) {
            std::cout << "Not Sorted!" << std::endl;
            std::cout << copy << std::endl;
            std::cout << test << std::endl;
            std::cout << "index: " << index << std::endl;
            std::cout << "value: " << value << std::endl;
        } else {
            // cout << "INSERT SUCCESS" << endl;
        }
    }
    return 0;
}

void checkFindCurrent(const Array<int> &test, int value, int index) {
    if (index >= 0) {
        if (test[index] == value) {}
        else {
            std::cout << test << std::endl;
            std::cout << "find: " << value << " at [" << index << "] = " << test[index] << std::endl;
        }
    } else {
        if (-index == test.getSize()) {
            if (test[-index - 1] <= value) {}
            else {
                std::cout << test << std::endl;
                std::cout << "not find: " << value
                          << ", it should pushFront after: [" << -index - 1 << "] = " << test[-index - 1]
                          << std::endl;
            }
        } else if (-index > test.getSize()) {
            std::cout << "ERROR: ????" << std::endl;
        } else {
            if (test[-index - 1] <= value && value <= test[-index]) {}
            else {
                std::cout << test << std::endl;
                std::cout << "not find: " << value
                          << ", it should pushFront between: [" << -index - 1 << "] = " << test[-index - 1]
                          << " and [" << -index - 2 << "] = " << test[-index]
                          << std::endl;
            }
        }
    }
}

//int selectCode = findDemo();