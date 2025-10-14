/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/8/29
 *
 */
#include "Byte.h"

Byte::Byte(math::byte value) : value(value) {}

Byte::Byte(const Byte &other) = default;

Byte &Byte::operator=(math::byte value_) {
    this->value = value_;
    return *this;
}

Byte &Byte::operator=(const Byte &obj) {
    if (this != &obj) {
        this->value = obj.value;
    }
    return *this;
}

Byte Byte::operator<<(int offset) const {
    return Byte(value << offset);
}

Byte Byte::operator>>(int offset) const {
    return Byte(value >> offset);
}

Byte Byte::operator&(math::byte other) const {
    return Byte(other & this->value);
}

Byte Byte::operator|(math::byte other) const {
    return Byte(other | this->value);
}

Byte Byte::operator^(math::byte other) const {
    return Byte(other ^ this->value);
}

Byte Byte::operator&(const Byte &other) const {
    return Byte(other.value & this->value);
}

Byte Byte::operator|(const Byte &other) const {
    return Byte(other.value | this->value);
}

Byte Byte::operator^(const Byte &other) const {
    return Byte(other.value ^ this->value);
}

Byte Byte::operator~() const {
    return Byte(~this->value);
}

bool Byte::operator>(math::byte other) const {
    return this->value > other;
}

bool Byte::operator<(math::byte other) const {
    return this->value < other;
}

bool Byte::operator>=(math::byte other) const {
    return this->value >= other;
}

bool Byte::operator<=(math::byte other) const {
    return this->value <= other;
}

bool Byte::operator==(math::byte other) const {
    return this->value == other;
}

bool Byte::operator!=(math::byte other) const {
    return this->value != other;
}

bool Byte::operator>(const Byte &other) const {
    return this->value > other.value;
}

bool Byte::operator<(const Byte &other) const {
    return this->value < other.value;
}

bool Byte::operator>=(const Byte &other) const {
    return this->value >= other.value;
}

bool Byte::operator<=(const Byte &other) const {
    return this->value <= other.value;
}

bool Byte::operator==(const Byte &other) const {
    return this->value == other.value;
}

bool Byte::operator!=(const Byte &other) const {
    return this->value != other.value;
}

int Byte::operator+(math::byte other) const {
    return this->value + other;
}

int Byte::operator-(math::byte other) const {
    return this->value - other;
}

int Byte::operator*(math::byte other) const {
    return this->value * other;
}

int Byte::operator/(math::byte other) const {
    return this->value / other;
}

int Byte::operator%(math::byte other) const {
    return this->value % other;
}

int Byte::operator+(const Byte &other) const {
    return this->value + other.value;
}

int Byte::operator-(const Byte &other) const {
    return this->value - other.value;
}

int Byte::operator*(const Byte &other) const {
    return this->value * other.value;
}

int Byte::operator/(const Byte &other) const {
    return this->value / other.value;
}

int Byte::operator%(const Byte &other) const {
    return this->value % other.value;
}

Byte &Byte::operator&=(math::byte other) {
    this->operator=(this->operator&(other));
    return *this;
};

Byte &Byte::operator|=(math::byte other) {
    this->operator=(this->operator|(other));
    return *this;
};

Byte &Byte::operator^=(math::byte other) {
    this->operator=(this->operator^(other));
    return *this;
};

Byte &Byte::operator&=(const Byte &other) {
    this->operator=(this->operator&(other));
    return *this;
};

Byte &Byte::operator|=(const Byte &other) {
    this->operator=(this->operator|(other));
    return *this;
};

Byte &Byte::operator^=(const Byte &other) {
    this->operator=(this->operator^(other));
    return *this;
};

Byte &Byte::operator<<=(int offset) {
    this->operator=(this->operator<<(offset));
    return *this;
};

Byte &Byte::operator>>=(int offset) {
    this->operator=(this->operator+(offset));
    return *this;
};

Byte &Byte::operator+=(math::byte other) {
    this->operator=(this->operator+(other));
    return *this;
};

Byte &Byte::operator-=(math::byte other) {
    this->operator=(this->operator-(other));
    return *this;
};

Byte &Byte::operator*=(math::byte other) {
    this->operator=(this->operator*(other));
    return *this;
};

Byte &Byte::operator/=(math::byte other) {
    this->operator=(this->operator/(other));
    return *this;
};

Byte &Byte::operator%=(math::byte other) {
    this->operator=(this->operator%(other));
    return *this;
};

Byte &Byte::operator+=(const Byte &other) {
    this->operator=(this->operator+(other));
    return *this;
};

Byte &Byte::operator-=(const Byte &other) {
    this->operator=(this->operator-(other));
    return *this;
};

Byte &Byte::operator*=(const Byte &other) {
    this->operator=(this->operator*(other));
    return *this;
};

Byte &Byte::operator/=(const Byte &other) {
    this->operator=(this->operator/(other));
    return *this;
};

Byte &Byte::operator%=(const Byte &other) {
    this->operator=(this->operator%(other));
    return *this;
};

Byte Byte::operator++(int ignored) {
    math::byte old = this->value;
    this->value++;
    return Byte(old);
}

Byte &Byte::operator++() {
    this->value++;
    return *this;
}

Byte::operator math::byte() const {
    return this->get();
}

Byte Byte::getBitFetcher(int index) {
    index = fixIndex(index);
    static Byte bitFetcher[8] = {
            Byte(128), Byte(64), Byte(32), Byte(16),
            Byte(8), Byte(4), Byte(2), Byte(1)
    };
    return bitFetcher[index];
}

Byte Byte::getReversalBitFetcher(int index) {
    return ~getBitFetcher(index);
}

packaging::Bit Byte::getBit(int index) const {
    if (index >= BIT_COUNT) {
        throw IllegalArgumentException("index 0 means lowest bit; index 7 means highest bit;index -1 means lowest bit");
    }
    index = fixIndex(index);
    const Byte &byte = this->operator>>(7 - index).operator&(0x01);
    return (packaging::Bit) (byte.value != 0);
}

math::byte Byte::get() const {
    return this->value;
}

Byte &Byte::set(math::byte value_) {
    this->value = value_;
    return *this;
}

Byte Byte::set1(int index) const {
    return Byte(this->value | getBitFetcher(index).value);
}

Byte Byte::set0(int index) const {
    return Byte(this->value & getReversalBitFetcher(index).value);
}

Byte &Byte::selfSet0(int index) {
    this->value &= getReversalBitFetcher(index).value;
    return *this;
}

Byte &Byte::selfSet1(int index) {
    this->value |= getBitFetcher(index).value;
    return *this;
}

Byte &Byte::selfSet(int index, packaging::Bit value_) {
    return value_ == packaging::Bit::ONE ? this->selfSet1(index) : this->selfSet0(index);
}

int Byte::first(const packaging::Bit &target) const {
    if (this->value == 0) {
        return -1;
    }
    for (int i = 0; i < Byte::BIT_COUNT; ++i) {
        if (this->getBit(i) == target) {
            return i;
        }
    }
    return -1;
}





