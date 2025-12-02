/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/8/29
 *
 */
#include "BigInteger.h"

BigInteger::BigInteger(const Data &data) : data(data) {}

BigInteger::BigInteger(math::number value) : data(sizeof(value)) {
    initData(value, sizeof(value));
    this->shrink();
}

BigInteger BigInteger::phaseDecString(const String &src, int radix) {
    if (radix > 36 || radix <= 1) {
        throw IllegalStateException("not supported radix: " + std::to_string(radix));
    }
    const String &str = src.trim();
    BigInteger result = BIG_INTEGER_ZERO;
    BigInteger bigRadix(radix);
    int strSize = str.getSize();
    int i = 0;
    if (str[0] == '-') {
        // 取反加一
        result.convert2Complement();
        i++;
    }
    for (; i < strSize; ++i) {
        math::number number = character2Number(str.at(i));
        if (number < 0) {
            throw IllegalArgumentException("Unknown Character in number string");
        }
        if (number >= radix) {
            throw IllegalArgumentException("Illegal Character in radix :" + std::to_string(radix));
        }
        result = result * bigRadix + BigInteger(number);
    }

    return result;
}

int BigInteger::byteCount() const {
    return this->data.byteCount();
}

int BigInteger::bitCount() const {
    return this->data.bitCount();
}

bool BigInteger::isZero() const {
    return this->data.isZero();
}

bool BigInteger::isMinus() const {
    return this->byteCount() != 0 &&
           this->data.getBit(0) == packaging::Bit::ONE;
}

int BigInteger::isPositive() const {
    return this->byteCount() != 0 &&
           this->data.getBit(0) == packaging::Bit::ZERO &&
           !this->isZero();
}

BigInteger &BigInteger::autoDataCast(const BigInteger &other) {
    return this->grow(other.byteCount());
}

BigInteger &BigInteger::grow(int targetByteCount) {
    int byteCount = this->byteCount();
    if (byteCount >= targetByteCount) {
        return *this;
    }
    this->data = dataAfterGrow(targetByteCount);
    return *this;
}

Data BigInteger::dataAfterGrow(int targetByteCount) const {
    int byteCount = this->byteCount();
    if (byteCount >= targetByteCount) {
        return this->data;
    }
    Data target(targetByteCount);
    int plusBytes = targetByteCount - byteCount;
    // 增加前缀的时候需要填充符号位, 符号位填充
    Byte filler(BYTE_NULL); // 此时默认是BYTE_NULL
    if (isMinus()) {
        filler = BYTE_FULL;
    }
    target.setByte(0, plusBytes, filler);
    for (int i = plusBytes, j = 0;
         i < targetByteCount && j < byteCount;
         ++i, ++j) {
        // 拷贝
        target.setByte(i, data.getByte(j));
    }
    // this->data.copyByte(0,byteCount,result.data,plusBytes,targetByteCount);
    return target;
}

BigInteger &BigInteger::convert2Complement() {
    return this->operator=(this->takeComplement());
}

BigInteger BigInteger::takeComplement() const {
    if (this->isZero()) {
        return *this;
    }
    bool isMinus = this->isMinus();
    // 取反, 加一
    BigInteger integer = BigInteger::add(
            this->operator~(), BIG_INTEGER_ONE);
    // 检查符号
    if (integer.isMinus() != isMinus) {
        // 符号正常
        return integer.shrink();
    }
    // 符号不正常
    if (isMinus) {
        // 想要变为正的
        // 但是现在是负数了,
        // 不可能
        // integer.set(this->byteArray.pushFront(0, BYTE_ZERO));
        throw IllegalStateException("it's impossible to be minus");
    } else {
        // 想要变成负的
        // 变成正的了? 原来是进位了, 最前面变0了
        // 不可能, 除非原来是0
        throw IllegalStateException("it's impossible to be positive");
    }
}

BigInteger &BigInteger::shrink() {
    return this->shrink(this->isMinus());
}

BigInteger BigInteger::newShrink() const {
    return this->newShrink(this->isMinus());
}

BigInteger &BigInteger::set(const Data &newData) {
    this->data = newData;
    return *this;
}

char BigInteger::number2Character(math::number value) {
    return (char) ((math::number) ((value < 10 ? '0' : ('A' - 10)) + value));
}

math::number BigInteger::character2Number(char character) {
    if ('0' <= character && character <= '9') {
        return character - '0';
    }
    if ('a' <= character && character <= 'z') {
        return character - 'a' + 10;
    }
    if ('A' <= character && character <= 'Z') {
        return character - 'A' + 10;
    }
    return -1;
}

void BigInteger::initData(math::number value, int size) {
    for (int i = 0; i < size; ++i) {
        this->data.setByte(-i - 1, Byte((value >> (i * Byte::BIT_COUNT)) & 0xff));
    }
    // this->data.setByte(0,dataSize, funcIndex())
}

BigInteger &BigInteger::shrink(bool isMinus) {
    return this->shrink(isMinus ? packaging::ONE : packaging::ZERO);
}

BigInteger &BigInteger::shrink(const packaging::Bit &shrinkTarget) {
    // new 出一个结果
    Data newData = this->newShrinkData(shrinkTarget);
    if (newData.byteCount() == 0) {
        // 当前没有可以省去的前导0
        // 没有new出一个结果
        packaging::Bit firstBit = this->data.getBit(0);
        if (shrinkTarget != firstBit) {
            // 符号位不正确
            throw IllegalStateException("incorrect sign bit");
        }
        return *this;
    }
    this->data = newData;
    return *this;
}

BigInteger BigInteger::newShrink(bool isMinus) const {
    return this->newShrink(isMinus ? packaging::ONE : packaging::ZERO);
}

BigInteger BigInteger::newShrink(const packaging::Bit &shrinkTarget) const {
    return BigInteger(this->newShrinkData(shrinkTarget));
}

Data BigInteger::newShrinkData(const packaging::Bit &shrinkTarget) const {
    int oldCount = byteCount();
    // 非0从何处起? start表示第一个非0的字节
    int start = this->data.firstTargetNotByte(shrinkTarget); // 此时标注字节

    if (start < 0) {
        // 全是shrinkTarget
        return Data(1, shrinkTarget == packaging::Bit::ZERO ? BYTE_ZERO : BYTE_FULL);
    }
    packaging::Bit firstBit = this->data.getBit(start * Byte::BIT_COUNT);
    if (firstBit != shrinkTarget) {
        start--;
    }
    if (start < 0) {
        // 没有搞
        return Data(0);
    }
    if (start == oldCount - 1) {
        // 保留最后一个, 不会变为空心
        start = oldCount - 1;
    }
    Data newData(oldCount - start);
    for (int i = 0, j = start; j < oldCount; ++i, ++j) {
        newData.setByte(i, this->data.getByte(j));
    }
    // this->data.copyByte(0,oldCount-start,newData,start,oldCount);
    return newData;
}

BigInteger BigInteger::add0(const BigInteger &casted1, const BigInteger &casted2) {
    Data var1 = casted1.data;
    Data var2 = casted2.data;
    while (!var1.isZero()) {
        Data temp = var1 & var2;
        var2 ^= var1;
        var1 = temp << 1;
    }
    return BigInteger(var2);
}

BigInteger BigInteger::divide0(BigInteger &absDividend, BigInteger &absDivisor, BigInteger &absRemainder) {
    // 位数对齐
    int offset = (absDivisor.data.firstBit(packaging::Bit::ONE) - absDivisor.bitCount())
                 - (absDividend.data.firstBit(packaging::Bit::ONE) - absDividend.bitCount());
    // 讨论
    if (offset == 0) {
        const BigInteger &difference = absDividend - absDivisor;
        if (!difference.isMinus()) {
            absRemainder.set(difference.data).shrink();
            return BIG_INTEGER_ONE;
        }
    }
    if (offset <= 0) {
        absRemainder.set(absDividend.data).shrink();
        return BIG_INTEGER_ZERO;
    }
    // 数位对齐
    absDivisor <<= offset;
    // 轮换相减
    BigInteger quotient = BIG_INTEGER_ZERO; // 商
    while (offset-- >= 0) {
        quotient <<= 1;
        const BigInteger &difference = absDividend - absDivisor;
        if (!difference.isMinus()) {
            absDividend = difference;
            quotient.data.setBit1(-1);
        }
        absDivisor >>= 1;
    }
    absRemainder.set(absDividend.data);
    return quotient.shrink();
}

BigInteger BigInteger::sub(const BigInteger &signedInteger1, const BigInteger &signedInteger2) {
    return BigInteger::add(signedInteger1, -signedInteger2);
}

BigInteger BigInteger::add(const BigInteger &signedInteger1, const BigInteger &signedInteger2) {
    // 获取拷贝
    BigInteger casted1(signedInteger1.data);
    BigInteger casted2(signedInteger2.data);
    casted1.shrink();
    casted2.shrink();
    int byteCount1 = casted1.byteCount();
    int byteCount2 = casted2.byteCount();
    // 多获取一个字节作为加法进位空间
    int castCount = std::max(byteCount1, byteCount2) + 1;
    casted1.grow(castCount);
    casted2.grow(castCount);
    // casted1和casted2是同样长度的了
    Data result(castCount);
    int resultByteCount = result.byteCount();
    result.setByte(0, BYTE_ZERO);
    // 同位数的数相加
    const BigInteger &integer = BigInteger::add0(casted1, casted2);

    for (int i = -1; i >= -resultByteCount; --i) {
        // 倒序, 防止
        // 获取到符号位
        result.setByte(i, integer.data.getByte(i));
    }

    // integer.data.copyByte(-resultByteCount,0,result.data,-resultByteCount,0);
    return BigInteger(result).shrink();
}

BigInteger BigInteger::multiply(const BigInteger &signedInteger1, const BigInteger &signedInteger2) {
    if (signedInteger1.isZero() || signedInteger2.isZero()) {
        return BIG_INTEGER_ZERO;
    }
    bool isMinus2 = signedInteger2.isMinus();
    BigInteger result(Data(0));
    int bitCount = signedInteger2.data.bitCount();
    for (int i = -1; i >= -bitCount; --i) {
        if (signedInteger2.data.getBit(i) == packaging::ZERO) {
            continue;
        }
        int offset = -1 - i;
        const BigInteger &tempInteger = signedInteger1 << offset;
        if (isMinus2 && i == -bitCount) {
            // 最后一个, 且第二个数是minus负数
            result -= tempInteger;
        } else {
            result += tempInteger;
        }
    }
    return result.shrink();
}

BigInteger BigInteger::abs(const BigInteger &integer) {
    return integer.isMinus() ? -integer : integer;
}

BigInteger BigInteger::divide(const BigInteger &dividend, const BigInteger &divisor, BigInteger &remainder) {
    if (divisor.isZero()) {
        throw DivideZeroException("zero");
    }
    // 获取拷贝
    bool dividendIsMinus = dividend.isMinus();
    bool divisorIsMinus = divisor.isMinus();
    BigInteger absDividend(abs(dividend).data);
    BigInteger absDivisor(abs(divisor).data);
    absDividend.shrink();
    absDivisor.shrink();
    // 可以除
    // 正数除法
    const BigInteger &absQuotient = BigInteger::divide0(absDividend, absDivisor, remainder);
    // 设置余数
    if (dividendIsMinus) {
        remainder.set((-remainder).data);//负值
    }
    if (dividendIsMinus == divisorIsMinus) {
        return absQuotient.newShrink();// 正
    } else {
        return (-absQuotient).newShrink();//负
    }
}

BigInteger BigInteger::operator&(const BigInteger &other) const {
    return BigInteger(this->data.operator&(other.data));
}

BigInteger BigInteger::operator|(const BigInteger &other) const {
    return BigInteger(this->data.operator|(other.data));
}

BigInteger BigInteger::operator^(const BigInteger &other) const {
    return BigInteger(this->data.operator^(other.data));
}


BigInteger &BigInteger::operator&=(const BigInteger &other) {
    return this->operator=(this->operator&(other));
}

BigInteger &BigInteger::operator|=(const BigInteger &other) {
    return this->operator=(this->operator|(other));
}

BigInteger &BigInteger::operator^=(const BigInteger &other) {
    return this->operator=(this->operator^(other));
}

BigInteger BigInteger::operator~() const {
    return BigInteger(this->data.operator~());
}

int BigInteger::compare(const BigInteger &self, const BigInteger &other) {
    const BigInteger &integer = BigInteger::sub(self, other);
    if (integer.isMinus()) {
        return -1;
    } else if (integer.isZero()) {
        return 0;
    } else {
        return 1;
    }
}

int BigInteger::compareTo(const BigInteger &o) const {
    return BigInteger::compare(*this, o);
}

bool BigInteger::operator==(const BigInteger &o) const {
    return this->compareTo(o) == 0;
}

bool BigInteger::operator!=(const BigInteger &o) const {
    return this->compareTo(o) != 0;
}

bool BigInteger::operator>=(const BigInteger &o) const {
    return this->compareTo(o) >= 0;
}

bool BigInteger::operator<=(const BigInteger &o) const {
    return this->compareTo(o) <= 0;
}

bool BigInteger::operator>(const BigInteger &o) const {
    return this->compareTo(o) < 0;
}

bool BigInteger::operator<(const BigInteger &o) const {
    return this->compareTo(o) < 0;
}

BigInteger BigInteger::operator<<(int offset) const { // NOLINT(*-no-recursion)
    if (offset == 0) {
        return *this;
    } else if (offset < 0) {
        return this->operator>>(-offset);
    }
    int resultBitNeed = this->data.bitCount() + offset;
    int resultByteCount = resultBitNeed / Byte::BIT_COUNT;
    if (resultByteCount * Byte::BIT_COUNT < resultBitNeed) {
        resultByteCount++;
    }
    Data resultData(resultByteCount, BYTE_NULL);
    int srcStart = 0;
    int srcEnd = this->bitCount();
    int resultStart = resultData.bitCount() - resultBitNeed;
    int resultEnd = resultData.bitCount() - offset;
    this->data.bitCopy(srcStart, srcEnd, resultData,
                       resultStart, resultEnd);
    if (this->isMinus()) {
        resultData.setBit(0, resultStart, packaging::Bit::ONE);
    }
    return BigInteger(resultData).shrink();
}

BigInteger BigInteger::operator>>(int offset) const { // NOLINT(*-no-recursion)
    if (offset == 0) {
        return *this;
    } else if (offset < 0) {
        return this->operator<<(-offset);
    }
    if (this->isZero()) {
        // 0直接返回
        return BIG_INTEGER_ZERO;
    }
    if (offset >= this->bitCount()) {
        return isMinus() ? BIG_INTEGER_FULL : BIG_INTEGER_ZERO;
    }
    int resultBitNeed = this->data.bitCount() - offset;
    int resultByteCount = resultBitNeed / Byte::BIT_COUNT + 1;
    // 负数需要在前填充1
    Data resultData(resultByteCount, isMinus() ? BYTE_FULL : BYTE_NULL);
    int srcStart = 0;
    int srcEnd = resultBitNeed;
    int resultStart = resultData.bitCount() - resultBitNeed;
    int resultEnd = resultData.bitCount();
    this->data.bitCopy(srcStart, srcEnd, resultData,
                       resultStart, resultEnd);
    return BigInteger(resultData).shrink();

}


BigInteger &BigInteger::operator<<=(int offset) {
    return this->operator=(this->operator<<(offset));
}

BigInteger &BigInteger::operator>>=(int offset) {
    return this->operator=(this->operator>>(offset));
}

// ----
BigInteger &BigInteger::operator=(const BigInteger &other) {
    if (this != &other) {
        this->data.operator=(other.data);
    }
    return *this;
}

BigInteger &BigInteger::operator+=(const BigInteger &other) {
    return this->operator=(this->operator+(other));
}

BigInteger &BigInteger::operator-=(const BigInteger &other) {
    return this->operator=(this->operator-(other));
}

BigInteger &BigInteger::operator++() {// ++a;
    return this->operator=(this->operator+(BIG_INTEGER_ONE));
}

BigInteger &BigInteger::operator--() {// --a;
    return this->operator=(this->operator-(BIG_INTEGER_ONE));
}

BigInteger &BigInteger::operator*=(const BigInteger &other) {
    return this->operator=(this->operator*(other));
}

BigInteger &BigInteger::operator/=(const BigInteger &other) {
    return this->operator=(this->operator/(other));
}

BigInteger &BigInteger::operator%=(const BigInteger &other) {
    return this->operator=(this->operator%(other));
}

BigInteger BigInteger::operator-() const {
    return this->takeComplement();
}

BigInteger BigInteger::operator+(const BigInteger &other) const {
    return BigInteger::add(*this, other);
}

BigInteger BigInteger::operator-(const BigInteger &other) const {
    return BigInteger::sub(*this, other);
}

BigInteger BigInteger::operator*(const BigInteger &other) const {
    return BigInteger::multiply(*this, other);
}

BigInteger BigInteger::operator/(const BigInteger &other) const {
    BigInteger remainder = BIG_INTEGER_ZERO;
    return BigInteger::divide(*this, other, remainder);
}

BigInteger BigInteger::operator%(const BigInteger &other) const {
    BigInteger remainder = BIG_INTEGER_ZERO;
    BigInteger::divide(*this, other, remainder);
    return remainder;
}

BigInteger &BigInteger::operator=(const math::number &other) {
    return this->operator=(BigInteger(other)); // NOLINT(*-unconventional-assign-operator)
}

BigInteger &BigInteger::operator+=(const math::number &other) {
    return this->operator+=(BigInteger(other));
}

BigInteger &BigInteger::operator-=(const math::number &other) {
    return this->operator-=(BigInteger(other));
}

BigInteger &BigInteger::operator*=(const math::number &other) {
    return this->operator*=(BigInteger(other));
}

BigInteger &BigInteger::operator/=(const math::number &other) {
    return this->operator/=(BigInteger(other));
}

BigInteger &BigInteger::operator%=(const math::number &other) {
    return this->operator%=(BigInteger(other));
}

BigInteger BigInteger::operator+(const math::number &other) const {
    return this->operator+(BigInteger(other));
}

BigInteger BigInteger::operator-(const math::number &other) const {
    return this->operator-(BigInteger(other));
}

BigInteger BigInteger::operator*(const math::number &other) const {
    return this->operator*(BigInteger(other));
}

BigInteger BigInteger::operator/(const math::number &other) const {
    return this->operator/(BigInteger(other));
}

BigInteger BigInteger::operator%(const math::number &other) const {
    return this->operator%(BigInteger(other));
}

BigInteger BigInteger::operator&(const math::number &other) const {
    return this->operator&(BigInteger(other));
}

BigInteger BigInteger::operator|(const math::number &other) const {
    return this->operator|(BigInteger(other));
}

BigInteger BigInteger::operator^(const math::number &other) const {
    return this->operator^(BigInteger(other));
}

BigInteger &BigInteger::operator&=(const math::number &other) {
    return this->operator&=(BigInteger(other));
}

BigInteger &BigInteger::operator|=(const math::number &other) {
    return this->operator|=(BigInteger(other));
}

BigInteger &BigInteger::operator^=(const math::number &other) {
    return this->operator^=(BigInteger(other));
}

bool BigInteger::operator==(const math::number &other) const {
    return this->operator==(BigInteger(other));
}

bool BigInteger::operator!=(const math::number &other) const {
    return this->operator!=(BigInteger(other));
}

bool BigInteger::operator>=(const math::number &other) const {
    return this->operator>=(BigInteger(other));
}

bool BigInteger::operator<=(const math::number &other) const {
    return this->operator<=(BigInteger(other));
}

bool BigInteger::operator>(const math::number &other) const {
    return this->operator>(BigInteger(other));
}

bool BigInteger::operator<(const math::number &other) const {
    return this->operator<(BigInteger(other));
}

BigInteger::operator math::number() const {
    return this->data.operator math::number();
}

BigInteger::operator std::string() const {
    return (std::string) this->data;
}

String BigInteger::toString(int radix, char separator) const {
    if (radix > 36 || radix <= 1) {
        throw IllegalStateException("not supported radix: " + std::to_string(radix));
    }

    BigInteger bigRadix(radix);
    BigInteger num(this->data);
    BigInteger remainder = BIG_INTEGER_ZERO;
    StringBuilder builder;
    bool isMinus = num.isMinus();
    if (isMinus) {
        num = -num;
    }
    int count = 0;
    while (!num.isZero()) {
        const BigInteger &quotient = BigInteger::divide(num, bigRadix, remainder);
        auto remainderValue = (math::number) remainder;
        char radixRemainder = number2Character(remainderValue);
        if (separator != 0 && count == 4) {
            builder.pushFront(separator);
            count = 0;
        }
        builder.pushFront(radixRemainder);
        num = quotient;
        count++;
    }
    if (isMinus) {
        builder.pushFront('-');
    }
    return builder.toString();
}

void BigInteger::printMessage(const std::string &varName) const {
    std::cout << varName << " value: " << this->toString(10) << std::endl;
    std::cout << varName << " binary: " << this->operator std::string() << std::endl;
}
