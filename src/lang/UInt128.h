//
// Created by Lenovo on 2025/10/5.
//

#ifndef ALGORITHM_UINT128_H
#define ALGORITHM_UINT128_H


#include <climits>
#include <ostream>

class UInt128 {
    unsigned long long h;
    unsigned long long l;
public:
#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"

    UInt128(unsigned long long int l = 0, unsigned long long int h = 0);

#pragma clang diagnostic pop


    UInt128 &operator=(const UInt128 &b);

    UInt128 operator&(const UInt128 &b) const;

    UInt128 &operator&=(const UInt128 &b);

    UInt128 operator|(const UInt128 &b) const;

    UInt128 &operator|=(const UInt128 &b);

    UInt128 operator^(const UInt128 &b) const;

    UInt128 &operator^=(const UInt128 &b);

    UInt128 operator>>(int b) const;

    UInt128 operator<<(int b) const;

    [[nodiscard]] int compare(const UInt128 &b) const;

    [[nodiscard]] int compare(unsigned long long b) const;

    bool operator==(unsigned long long int b) const;

    bool operator==(const UInt128 &b) const;

    friend std::ostream &operator<<(std::ostream &os, const UInt128 &a);

    static UInt128 MAX_VALUE;
};

std::ostream &operator<<(std::ostream &os, const UInt128 &a) {
    return os << std::hex << a.h << "_" << a.l << std::dec;
}


#endif //ALGORITHM_UINT128_H
