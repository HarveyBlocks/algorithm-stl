/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/9/1
 *
 */
#include "ShortByteDivider.h"

Byte ShortByteDivider::catchHigh(unsigned short origin) {
    return Byte((origin & HIGH_BYTE_CATCHER) >> Byte::BIT_COUNT);
}

Byte ShortByteDivider::catchLow(unsigned short origin) {
    return Byte(origin & LOW_BYTE_CATCHER);
}

ShortByteDivider::ShortByteDivider(signed short origin) :
        numberSign(math::MathCommons::signOf(origin)) {
    switch (numberSign) {
        case math::ZERO:
            low = BYTE_ZERO;
            high = BYTE_ZERO;
            break;
        case math::MINUS:
            origin = (signed short) -origin;
        case math::POSITIVE:
            low = catchLow(origin);
            high = catchHigh(origin);
            break;
        default:
            throw IllegalStateException("Unknown sign");
    }
}

ShortByteDivider::ShortByteDivider(unsigned short origin, math::NumberSign sign) :
        numberSign(origin == 0 ? math::NumberSign::ZERO : sign), low(catchLow(origin)), high(catchHigh(origin)) {}

Byte ShortByteDivider::getHigh() const {
    return high;
}

Byte ShortByteDivider::getLow() const {
    return low;
}

math::NumberSign ShortByteDivider::getSign() const {
    return numberSign;
}

ShortByteDivider::operator std::string() {
    return ((std::string) high) + "_" + ((std::string) low);
}


