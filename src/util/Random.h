#ifndef ALGORITHM_RANDOM_UTIL_H
#define ALGORITHM_RANDOM_UTIL_H

#include <random>
#include <ctime>
#include <vector>
#include "../lang/exception/IllegalArgumentException.h"

class Random {
private:
    std::uniform_int_distribution<> distrib;
    std::ranlux48 engine;

    static int myRand();

    static const int RANDOM_MAX = RAND_MAX;
public:
    explicit Random();

    static double random();

    static char resetSeed();

    int next();


    static bool bit();

    static unsigned char unsignedByte();

    static signed char signedByte();

    static signed short signedShort();

    static unsigned short unsignedShort();

    static unsigned int unsignedInt();

    static int signedInt();

    static int signedInt(int low, int high);

    static long long int signedLongLong();

    static unsigned long long unsignedLongLong();
    static void shuffle(std::vector<int> &arr);


private:
    static unsigned long long initValue(long long targetByteSize);

};


#endif //ALGORITHM_RANDOM_UTIL_H
