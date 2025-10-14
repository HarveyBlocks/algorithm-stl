#include "Random.h"


int Random::next() {
    return this->distrib(this->engine);//随机数
}

Random::Random() :
        distrib() {
    static std::random_device seed;//硬件生成随机数种子
    this->engine = std::ranlux48(seed());
}

int Random::myRand() {
    return std::rand();
}

char Random::resetSeed() {
    std::srand((int) time(nullptr));   //包含time.h
    return 12;
}


double Random::random() {
    return (myRand() * 1.0) / (RANDOM_MAX + 1);
}


bool Random::bit() {
    return (unsigned char) (myRand() & 0x0001);
}

unsigned char Random::unsignedByte() {
    return (unsigned char) (myRand() & 0x00ff);
}

signed char Random::signedByte() {
    return (signed char) Random::initValue(sizeof(signed short));
}


unsigned short Random::unsignedShort() {
    return (unsigned short) Random::initValue(sizeof(unsigned short));
}

signed short Random::signedShort() {
    return (signed short) Random::initValue(sizeof(signed short));
}

unsigned int Random::unsignedInt() {
    return (unsigned int) Random::initValue(sizeof(unsigned int));
}

signed int Random::signedInt() {
    return (signed int) Random::initValue(sizeof(signed int));
}

int Random::signedInt(int low, int high) {
    if (low >= high) {
        throw IllegalArgumentException();
    }
    return (Random::signedInt() & INT_MAX) % (high - low) + low;
}

unsigned long long Random::unsignedLongLong() {
    return (unsigned long long) Random::initValue(sizeof(unsigned long long));
}


signed long long Random::signedLongLong() {
    return (long long) Random::initValue(sizeof(long long));
}

unsigned long long Random::initValue(long long int targetByteSize) {
    unsigned long long result = 0;
    for (int i = 0; i < targetByteSize; ++i) {
        result <<= 8;
        result |= Random::unsignedByte();
    }
    return result;
}

