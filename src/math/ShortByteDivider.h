/**
 * 将Short的绝对值分成俩字节
 *
 * @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 * @date 2024/9/1
 */
#ifndef ALGORITHM_SHORT_BYTE_DIVIDER_H
#define ALGORITHM_SHORT_BYTE_DIVIDER_H

#include "../lang/packaging/Byte.h"

#define HIGH_BYTE_CATCHER 0xff00
#define LOW_BYTE_CATCHER 0x00ff


class ShortByteDivider {
private:
    Byte low;
    Byte high;
    math::NumberSign numberSign;

    static Byte catchHigh(unsigned short origin);

    static Byte catchLow(unsigned short origin);

public:
    explicit ShortByteDivider(signed short origin);

    explicit ShortByteDivider(unsigned short origin, math::NumberSign sign);

    [[nodiscard]] Byte getHigh() const;

    [[nodiscard]] Byte getLow() const;

    [[nodiscard]] math::NumberSign getSign() const;

    friend std::ostream &operator<<(std::ostream &os, const ShortByteDivider &obj) {
        return os << obj.high << obj.low;
    }

    explicit operator std::string();
};


#endif //ALGORITHM_SHORT_BYTE_DIVIDER_H
