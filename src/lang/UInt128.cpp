//
// Created by Lenovo on 2025/10/5.
//

#include "UInt128.h"

UInt128 UInt128::MAX_VALUE = {ULLONG_MAX, ULLONG_MAX};

UInt128::UInt128(unsigned long long int l, unsigned long long int h) :
        h(h),
        l(l) {}

UInt128 &UInt128::operator=(const UInt128 &b) {
    if (this == &b) {
        return *this;
    }
    this->l = b.l;
    this->h = b.h;
    return *this;
}

UInt128 UInt128::operator&(const UInt128 &b) const {
    return {this->l & b.l, this->h & b.h};
}

UInt128 &UInt128::operator&=(const UInt128 &b) {
    return this->operator=(this->operator&(b));
}

UInt128 UInt128::operator|(const UInt128 &b) const {
    return {this->l | b.l, this->h | b.h};
}

UInt128 &UInt128::operator|=(const UInt128 &b) {
    return this->operator=(this->operator|(b));
}

UInt128 UInt128::operator^(const UInt128 &b) const {
    return {this->l ^ b.l, this->h ^ b.h};
}

UInt128 &UInt128::operator^=(const UInt128 &b) {
    return this->operator=(this->operator^(b));
}

UInt128 UInt128::operator>>(int b) const {
    if (b == 0) return *this;
    if (b < 0) return this->operator<<(-b);
    if (b >= 128) return {0};
    if (b >= 64) {
        return {this->l >> (b - 64), 0};
    }
    return {this->l >> b | this->h & ULONG_LONG_MAX << (64 - b), this->h >> b};
}

UInt128 UInt128::operator<<(int b) const {
    if (b == 0) return *this;
    if (b < 0) return this->operator>>(-b);
    if (b >= 128) return {0};
    if (b >= 64) {
        return {0, (this->l & ULONG_LONG_MAX << (b - 64))};
    }
    return {this->l << b, this->h << b | this->l >> (64 - b)};
}

int UInt128::compare(const UInt128 &b) const {
    if (this->h != b.h) {
        return this->h > b.h ? 1 : -1;
    }
    if (this->l == b.l) {
        return 0;
    }
    return this->l > b.l ? 1 : -1;
}

int UInt128::compare(const unsigned long long int b) const {
    return compare(UInt128(b));
}

bool UInt128::operator==(unsigned long long int b) const {
    return compare(b) == 0;
}

bool UInt128::operator==(const UInt128 &b) const {
    return compare(b) == 0;
}
