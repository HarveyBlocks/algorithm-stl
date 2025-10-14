/**
 * 避免Byte增加时出现进位和溢出
 * @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 * @date 2024/9/1
 */
#ifndef ALGORITHM_BYTE_CALCULATOR_H
#define ALGORITHM_BYTE_CALCULATOR_H


#include "ShortByteDivider.h"

class ByteCalculator {
private:
    ByteCalculator() {
        // 私有构造
    }

public:
    ShortByteDivider static multiply(const Byte &var1, const Byte &var2, math::NumberSign resultSign) {
        return ShortByteDivider((unsigned short) ((unsigned short) var1.get() * (unsigned short) var2.get()),
                                resultSign);
    }

    ShortByteDivider static divide(const Byte &var1, const Byte &var2) {
        return ShortByteDivider((short) ((short) var1.get() / (short) var2.get()));
    }

    ShortByteDivider static mod(const Byte &var1, const Byte &var2) {
        return ShortByteDivider((short) ((short) var1.get() % (short) var2.get()));
    }

    ShortByteDivider static add(const Byte &var1, const Byte &var2) {
        return ShortByteDivider((short) ((short) var1.get() + (short) var2.get()));
    }

    ShortByteDivider static sub(const Byte &var1, const Byte &var2) {
        return ShortByteDivider((short) ((short) var1.get() - (short) var2.get()));
    }

};


#endif //ALGORITHM_BYTE_CALCULATOR_H
