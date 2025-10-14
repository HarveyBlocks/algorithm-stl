#include "util/sort/InsertionSort.h"
#include "util/sort/CountSort.h"
#include "util/sort/EncodingSort.h"
#include "util/Times.h"
#include "util/RandomContainer.h"
#include "util/sort/RadixSort.h"

int compare(const double &a, const double &b) {
    return a == b ? 0 : (a > b ? 1 : -1);
}

int EncodingSortDemo() {
    Random::resetSeed();
    int length = 337;
    Array<int> test(length);
    Array<int> copy(length);
    int count = 0;
    Compare<double> cmp(compare);
    Producer<int> producer = []() { return Random::signedInt() % 256; };
    for (int i = 0; i < 200000; i++) {

        ArrayInitializer::init(test, producer);
        // 拷贝检验正确性
        test.clone(copy);
        /*cout << byteCopy << endl;
        cout << test << endl;*/
        Encode<int> encoder([](const int &obj) { return obj; });
        EncodingSort(test, encoder).sort();
        InsertionSort(copy).sort();
        if (Arrays::same(test, copy)) {
            if (++count == 2000) {
                std::cout << "SAME!" << std::endl;
                count = 0;
            }
        } else {
            std::cout << copy << std::endl;
            std::cout << test << std::endl;
        }
    }
    return 0;
}

int sortDemo() {
    Random::resetSeed();
    int length = 37;
    Array<unsigned int> test(length);
    Array<unsigned int> copy(length);
    int count = 0;
    Producer<unsigned int> producer = []() { return Random::unsignedInt() % 256; };
    for (int i = 0; i < 10; i++) {
        ArrayInitializer::init(test, producer);
        // 拷贝检验正确性
        test.clone(copy);
        /*cout << byteCopy << endl;
        cout << test << endl;*/
        RadixSort(test).sort();
        InsertionSort(copy, false).sort();
        if (Arrays::same(test, copy)) {
            if (++count == 1) {
                std::cout << "SAME!" << std::endl;
                count = 0;
            }
        } else {
            std::cout << copy << std::endl;
            std::cout << test << std::endl;
        }
    }
    return 0;
}

int sortDemoEach() {
    Random::resetSeed();
    int length = 26;
    Array<int> test(length);
    Array<int> copy(length);
    Producer<int> producer = []() { return Random::unsignedInt() % 256; };
    ArrayInitializer::init(test, producer);
    std::cout << test << std::endl;
    test.clone(copy);
    ShellSort(test).sort();
    InsertionSort(copy).sort();
    if (Arrays::same(test, copy)) {
        std::cout << "SAME!" << std::endl;
    } else {
        std::cout << copy << std::endl;
        std::cout << test << std::endl;
    }
    return 0;
}




//int sortCode = sortDemo();