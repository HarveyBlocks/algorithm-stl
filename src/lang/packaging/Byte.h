/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/8/29
 *
 */
#ifndef ALGORITHM_BYTE_H
#define ALGORITHM_BYTE_H


#include "../exception/IllegalArgumentException.h"
#include "iostream"
#include "../../math/commons.h"
#include "sstream"

#define BYTE_ZERO Byte(0)
#define BYTE_ONE Byte(1)
#define BYTE_NULL BYTE_ZERO
#define BYTE_FULL Byte(0xff)

namespace packaging {
    enum Bit {
        ZERO, ONE
    };

    static int getValue(Bit bit) {
        return bit == ZERO ? 0 : 1;
    }

    static Bit valueOf(bool has) {
        return has ? ONE : ZERO;
    }

    static Bit operator!(const Bit &bit) {
        return bit == ZERO ? ONE : ZERO;
    }
}

class Byte {
private:
    math::byte value;


    static int fixIndex(int index) {
        return index >= 0 ? index : BIT_COUNT + index;
    }

public:
    static constexpr int BIT_COUNT = 8;

    explicit Byte(math::byte value = 0);

    Byte(const Byte &other);

    Byte &operator=(math::byte value);

    Byte &operator=(const Byte &obj);

    Byte operator<<(int offset) const;

    Byte operator>>(int offset) const;

    Byte operator&(math::byte other) const;

    Byte operator|(math::byte other) const;

    Byte operator^(math::byte other) const;

    Byte operator&(const Byte &other) const;

    Byte operator|(const Byte &other) const;

    Byte operator^(const Byte &other) const;

    Byte operator~() const;

    bool operator>(math::byte other) const;

    bool operator<(math::byte other) const;

    bool operator>=(math::byte other) const;

    bool operator<=(math::byte other) const;

    bool operator==(math::byte other) const;

    bool operator!=(math::byte other) const;

    bool operator>(const Byte &other) const;

    bool operator<(const Byte &other) const;

    bool operator>=(const Byte &other) const;

    bool operator<=(const Byte &other) const;

    bool operator==(const Byte &other) const;

    bool operator!=(const Byte &other) const;

    signed int operator+(math::byte other) const;

    signed int operator-(math::byte other) const;

    signed int operator*(math::byte other) const;

    signed int operator/(math::byte other) const;

    signed int operator%(math::byte other) const;

    signed int operator+(const Byte &other) const;

    signed int operator-(const Byte &other) const;

    signed int operator*(const Byte &other) const;

    signed int operator/(const Byte &other) const;

    signed int operator%(const Byte &other) const;

    Byte &operator&=(math::byte other);

    Byte &operator|=(math::byte other);

    Byte &operator^=(math::byte other);

    Byte &operator&=(const Byte &other);

    Byte &operator|=(const Byte &other);

    Byte &operator^=(const Byte &other);

    Byte &operator<<=(int offset);

    Byte &operator>>=(int offset);

    Byte &operator+=(math::byte other);

    Byte &operator-=(math::byte other);

    Byte &operator*=(math::byte other);

    Byte &operator/=(math::byte other);

    Byte &operator%=(math::byte other);

    Byte &operator+=(const Byte &other);

    Byte &operator-=(const Byte &other);

    Byte &operator*=(const Byte &other);

    Byte &operator/=(const Byte &other);

    Byte &operator%=(const Byte &other);

    Byte operator++(int ignored);

    Byte &operator++();

    explicit operator math::byte() const;

    /**
     * 享元
     * @param offset 从高位向低位的偏移, 7表示取最低位, 0表示取最高位
     */
    static Byte getBitFetcher(int index);

    static Byte getReversalBitFetcher(int index);

    /**
     * @param index 索引0表示最高位, 索引7表示最低位, -1表示最低位, -8表示最高位
     */
    [[nodiscard]] packaging::Bit getBit(int index) const;

    [[nodiscard]] math::byte get() const;

    Byte &set(math::byte value);

    /**
     * @param index 索引0表示最高位, 索引7表示最低位, -1表示最低位, -8表示最高位
     */
    [[nodiscard]] Byte set1(int index) const;

    /**
     * @param index 索引0表示最高位, 索引7表示最低位, -1表示最低位, -8表示最高位
     */
    [[nodiscard]] Byte set0(int index) const;

    /**
     * @param index 索引0表示最高位, 索引7表示最低位, -1表示最低位, -8表示最高位
     */
    Byte &selfSet1(int index);

    Byte &selfSet(int index, packaging::Bit value);

    /**
     * @param index 索引0表示最高位, 索引7表示最低位, -1表示最低位, -8表示最高位
     */
    Byte &selfSet0(int index);

    /**
     * @return bit index, 0表最高位
     */
    [[nodiscard]] int first(const packaging::Bit &target) const;

    friend std::ostream &operator<<(std::ostream &os, const Byte &obj) {
        return os << obj.value;
    }


    explicit operator std::string() const {
        return toBinaryString();
    }

    [[nodiscard]] std::string toBinaryString() const {
        std::stringstream ss;
        for (int i = 0; i < BIT_COUNT; ++i) {
            ss << (getBit(i) == packaging::ONE ? '1' : '0');
        }
        return ss.str();
    }


};

#endif //ALGORITHM_BYTE_H
