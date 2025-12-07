/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/9/1
 *
 */
#ifndef ALGORITHM_BYTE_BIG_INTEGER_H
#define ALGORITHM_BYTE_BIG_INTEGER_H


#include "DataBasedCalculator.h"
#include "ByteCalculator.h"
#include "../lang/exception/DivideZeroException.h"

#define BYTE_BIG_INTEGER_ZERO ByteBigInteger(0)
#define BYTE_BIG_INTEGER_ONE ByteBigInteger(1)

class ByteBigInteger : public DataBasedCalculator<ByteBigInteger> {
private:
    math::NumberSign numberSign;
    static const int BYTE_RADIX = 256; // 256进制的基数, 可用于进位和在减法的时候借数
protected:
    [[nodiscard]] ByteBigInteger &getThis() override {
        return *this;
    }

    [[nodiscard]] ByteBigInteger copyThis() const override {
        return *this;
    }

public:

    /**
     * @param absoluteData 表示绝对值
     */
    explicit ByteBigInteger(const Data &absoluteData, const math::NumberSign &numberSign = math::NumberSign::POSITIVE) :
            DataBasedCalculator<ByteBigInteger>(absoluteData),
            numberSign(numberSign) {
        if (absoluteData.isZero()) {
            this->numberSign = math::ZERO;
        }
    }

    explicit ByteBigInteger(const math::number &number = 0) :
            DataBasedCalculator<ByteBigInteger>(number),
            numberSign(math::MathCommons::signOf(number)) { initData(number); }

    ByteBigInteger(const ByteBigInteger &obj) :
            DataBasedCalculator<ByteBigInteger>(obj.data),
            numberSign(obj.numberSign) {}

    [[nodiscard]] ByteBigInteger instance(const math::number &value) const override {
        return ByteBigInteger(value);
    }

    [[nodiscard]]  bool isPositive() const override {
        return this->numberSign == math::NumberSign::POSITIVE;
    }

    [[nodiscard]] bool isZero() const override {
        return this->numberSign == math::NumberSign::ZERO;
    }

    [[nodiscard]] bool isMinus() const override {
        return this->numberSign == math::NumberSign::MINUS;
    }

    void initData(const math::number &value) override {
        if (value == 0) {
            return;
        }
        math::number absoluteNumber = std::abs(value);
        for (int i = 0; i < sizeof(math::number); ++i) {
            this->data.setByte(-i - 1, Byte((absoluteNumber >> (i * Byte::BIT_COUNT)) & 0xff));
        }
        this->shrink();
    }

    ByteBigInteger &operator=(const ByteBigInteger &other) {
        if (this != &other) {
            this->data = newShrinkData(other.data);
            this->numberSign = other.numberSign;
        }
        return *this;
    }


    [[nodiscard]] ByteBigInteger getOpposite() const override {
        return ByteBigInteger(this->data, math::MathCommons::oppositeOf(this->numberSign));
    }

    ByteBigInteger &toOpposite() override {
        this->numberSign = math::MathCommons::oppositeOf(this->numberSign);
        return *this;
    }

    explicit operator math::number() const override {
        math::number num = 0;
        int high = this->byteCount();
        if (sizeof(math::number) < high) {
            high = sizeof(math::number);
        }
        for (int i = -high; i <= -1; ++i) {
            num <<= 8;
            num += this->data.getByte(i).get();
        }
        return isMinus() ? -num : num;
    }

    [[nodiscard]] ByteBigInteger add(const ByteBigInteger &other) const override {
        return ByteBigInteger::add(*this, other);
    }

    [[nodiscard]] ByteBigInteger multiply(const ByteBigInteger &other) const override {
        return ByteBigInteger::multiply(*this, other);
    }

    ByteBigInteger divide(const ByteBigInteger &divisor, ByteBigInteger &remainder) const override {
        return ByteBigInteger::divide(*this, divisor, remainder);
    }

    ByteBigInteger &cloneFrom(const ByteBigInteger &src) override {
        return this->operator=(src);
    }

    [[nodiscard]] int compareTo(const ByteBigInteger &other) const override {
        return ByteBigInteger::compare(*this, other);
    }

    [[nodiscard]] ByteBigInteger sub(const ByteBigInteger &other) const override {
        return ByteBigInteger::sub(*this, other);
    }

    static int compare(const ByteBigInteger &num1, const ByteBigInteger &num2) {
        if (num1.numberSign != num2.numberSign) {
            // 符号不同比符号
            if (num1.numberSign > num2.numberSign) {
                return 1;
            } else if (num1.numberSign < num2.numberSign) {
                return -1;
            }
        }
        // 符号相同
        if (num1.isZero()) {
            return 0;
        }
        // 符号相同且不为0
        int wight = 1;
        if (num1.isMinus() && num2.isMinus()) {
            wight = -1;
        }
        // 比较绝对值
        // 长度
        ByteBigInteger num1Copy = num1;
        ByteBigInteger num2Copy = num2;
        int afterCastCount = ByteBigInteger::autoCast(num1Copy, num2Copy);
        return wight * ByteBigInteger::compare(num1Copy.data, num2Copy.data, afterCastCount);
    }


    static ByteBigInteger add(const ByteBigInteger &num1, const ByteBigInteger &num2) {
        if (num2.isZero()) {
            return num1;
        }
        if (num1.isZero()) {
            return num2;
        }
        if (num1.isPositive() && num2.isMinus()) {
            // num1 - abs(num2)
            return ByteBigInteger::sub0(num1, -num2);
        }
        if (num1.isMinus() && num2.isPositive()) {
            //  num2-abs(num1)
            return ByteBigInteger::sub0(num2, -num1);
        }
        if (num1.isMinus() && num2.isMinus()) {
            // -(abs(num1)+abs(num2))
            return -ByteBigInteger::add0(-num1, -num2);
        }
        // num1+num2
        return ByteBigInteger::add0(num1, num2);
    }

    static ByteBigInteger sub(const ByteBigInteger &num1, const ByteBigInteger &num2) {
        if (num2.isZero()) {
            return num1;
        }
        if (num1.isZero()) {
            return -num2;
        }
        if (num1.isPositive() && num2.isMinus()) {
            // num1 + abs(num2)
            return ByteBigInteger::add0(num1, -num2);
        }
        if (num1.isMinus() && num2.isPositive()) {
            //  -(abs(num1)+num2)
            return -ByteBigInteger::add0(-num1, num2);
        }
        if (num1.isMinus() && num2.isMinus()) {
            // abs(num2)-abs(num1)
            return ByteBigInteger::sub0(-num2, -num1);
        }
        // num1-num2
        return ByteBigInteger::sub0(num1, num2);
    }

    static ByteBigInteger multiply(const ByteBigInteger &num1, const ByteBigInteger &num2) {
        if (num2.isZero() || num2.isZero()) {
            return BYTE_BIG_INTEGER_ZERO;
        }
        return ByteBigInteger(
                ByteBigInteger::multiply(newShrinkData(num1.data), newShrinkData(num2.data)),
                num1.numberSign == num2.numberSign ?
                math::NumberSign::POSITIVE : math::NumberSign::MINUS);

    }

    static ByteBigInteger divide(const ByteBigInteger &dividend, const ByteBigInteger &divisor,
                                 ByteBigInteger &remainder) {
        if (divisor.isZero()) {
            throw DivideZeroException("zero");
        }
        if (dividend.isZero()) {
            remainder = BYTE_BIG_INTEGER_ZERO;
            return BYTE_BIG_INTEGER_ZERO;
        }
        // 获取拷贝
        bool dividendIsMinus = dividend.isMinus();
        bool divisorIsMinus = divisor.isMinus();
        ByteBigInteger absDividend(dividend.data);
        ByteBigInteger absDivisor(divisor.data);
        remainder.numberSign = math::NumberSign::POSITIVE;
        absDividend.shrink();
        absDivisor.shrink();
        // 可以除
        // 正数除法
        const ByteBigInteger absQuotient(
                ByteBigInteger::divide(absDividend.data, absDivisor.data, remainder.data),
                math::NumberSign::POSITIVE);
        // 设置余数
        remainder.shrink();
        remainder.updateZeroSign();
        if (dividendIsMinus && remainder.isPositive()) {
            remainder.numberSign = math::NumberSign::MINUS; // 负值
        }
        return dividendIsMinus == divisorIsMinus ?
               absQuotient :    // 正
               -absQuotient;    // 负
    }

protected:
    [[nodiscard]] Data newShrinkData() const override {
        return ByteBigInteger::newShrinkData(this->data);
    }


    [[nodiscard]] Data newGrowData(int targetCount) const override {
        return ByteBigInteger::newGrowData(this->data, targetCount);
    }

private:
    ByteBigInteger &updateZeroSign() {
        bool dataIsZero = this->data.isZero();
        bool numberIsZero = isZero();
        if (!numberIsZero && dataIsZero) {
            // 是zero但没有标注成zero的情况
            this->numberSign = math::NumberSign::ZERO;
        } else if (numberIsZero && !dataIsZero) {
            throw IllegalStateException("The sign of the number cannot be determined");
        }
        return *this;
    }

    [[nodiscard]] static Data newShrinkData(const Data &src) {
        int count = src.byteCount();
        int start = src.firstTargetNotByte(packaging::ZERO);
        if (start < 0) {
            return DATA_NULL;
        }
        int newCount = count - start;
        Data result(newCount);
        src.byteCopy(start, count, result, 0, newCount);
        return result;
    }

    [[nodiscard]] static Data newShrinkData(const Data &src, int target) {
        int count = src.byteCount();
        if (target >= count) {
            // TODO 意义不明
            Data result(src.byteCount());
            src.clone(result);
            return result;
        }
        int start = src.firstTargetNotByte(packaging::ZERO);
        if (start < 0) {
            return Data(target, BYTE_ZERO);
        }
        int newCount = count - start;
        int resultEnd = newCount;
        if (target > resultEnd) {
            resultEnd = target;
        }
        Data result(resultEnd);
        int resultStart = resultEnd - newCount;
        src.byteCopy(start, count, result, resultStart, resultEnd);
        return result;
    }

    [[nodiscard]] static Data newGrowData(const Data &src, int targetCount) {
        int count = src.byteCount();
        if (targetCount <= count) {
            return src;
        }
        Data result(targetCount, BYTE_ZERO);
        src.byteCopy(0, count, result, targetCount - count, targetCount);
        return result;
    }

    static int compare(const Data &data1, const Data &data2, int count) {
        if (count < 0) {
            throw IllegalArgumentException("count be positive: " + std::to_string(count));
        }
        if (data1.byteCount() != count || data2.byteCount() != count) {
            throw IllegalArgumentException("two data byte count should be same: " + std::to_string(count));
        }
        for (int i = 0; i < count; ++i) {
            int difference = data1.getByte(i) - data2.getByte(i);
            if (difference != 0) {
                return difference;
            }
        }
        return 0;
    }

    /**
     * 绝对值相加
     *
     * @param num1 确保是正数
     * @param num2 确保是正数
     */
    static ByteBigInteger add0(const ByteBigInteger &num1, const ByteBigInteger &num2) {
        // 绝对值相加
        ByteBigInteger num1Copy = num1;
        ByteBigInteger num2Copy = num2;
        num1Copy.shrink();
        num2Copy.shrink();
        return ByteBigInteger(ByteBigInteger::newShrinkData(
                ByteBigInteger::add(num1Copy.data, num2Copy.data)
        ), math::NumberSign::POSITIVE);
    }

    /**
     * 绝对值相加, 不需要位数相同
     *
     * @param num1 确保是正数, 如果已经shrink, 会提高效率
     * @param num2 确保是正数, 如果已经shrink, 会提高效率
     */
    static Data add(const Data &data1, const Data &data2) {
        int byteCount1 = data1.byteCount();
        int byteCount2 = data2.byteCount();
        // 绝对值相加
        return byteCount1 > byteCount2 ?
               ByteBigInteger::add(data1, data2, byteCount1, byteCount2) :
               ByteBigInteger::add(data2, data1, byteCount2, byteCount1);
    }

    static Data add(const Data &longer, const Data &shorter, int longerCount, int shorterCount) {
        Data result = ByteBigInteger::newGrowData(longer, longerCount + 1);
        int resultCount = result.byteCount();
        // 相加
        for (int i = -1; i >= -shorterCount; --i) {
            // 每一位相加
            ByteBigInteger::add(result, shorter.getByte(i), resultCount, i);
        }
        return ByteBigInteger::newShrinkData(result, longerCount);
    }

    static Data &add(Data &result, const Byte &oneByte, int resultCount, int minusIndex) {
        if (oneByte == 0) {
            return result;
        }
        ShortByteDivider divider = ByteCalculator::add(result.getByte(minusIndex), oneByte);
        result.setByte(minusIndex, divider.getLow());
        // 进位
        for (int j = minusIndex - 1; divider.getHigh() != 0 && j >= -resultCount; --j) {
            divider = ByteCalculator::add(result.getByte(j), BYTE_ONE);
            result.setByte(j, divider.getLow());
        }
        return result;
    }

    /**
     * 绝对值相减, 不需要位数相同
     *
     * @param num1 确保是正数
     * @param num2 确保是正数
     */
    static ByteBigInteger sub0(const ByteBigInteger &minuend, const ByteBigInteger &subtrahend) {
        ByteBigInteger minuendCopy = minuend;
        ByteBigInteger subtrahendCopy = subtrahend;
        int afterCastCount = ByteBigInteger::autoCast(minuendCopy, subtrahendCopy);
        int difference = ByteBigInteger::compare(minuendCopy.data, subtrahendCopy.data, afterCastCount);

        if (difference == 0) {
            return BYTE_BIG_INTEGER_ZERO;
        }
        // 恢复shrink
        if (minuend.byteCount() < afterCastCount) {
            minuendCopy.shrink();
        }
        if (subtrahend.byteCount() < afterCastCount) {
            subtrahendCopy.shrink();
        }
        if (difference > 0) {
            return ByteBigInteger(ByteBigInteger::sub(minuendCopy.data, subtrahendCopy.data),
                                  math::NumberSign::POSITIVE);
        } else {
            return ByteBigInteger(ByteBigInteger::sub(subtrahendCopy.data, minuendCopy.data),
                                  math::NumberSign::MINUS);
        }
    }

    /**
     * 确保data1大于data2, 不需要位数相同
     *
     * @param data1 如果已经shrink, 会提高效率
     * @param data2 如果已经shrink, 会提高效率
     */
    static Data sub(const Data &minuend, const Data &subtrahend) {
        Data difference = minuend; // 进位不够用来标记
        int subtrahendCount = subtrahend.byteCount();
        int minuendCount = minuend.byteCount();
        for (int i = -1; i >= -subtrahendCount; --i) {
            ByteBigInteger::sub(difference, subtrahend.getByte(i), minuendCount, i);
        }
        // 绝对值相减
        return ByteBigInteger::newShrinkData(difference);
    }


    static Data &sub(Data &minuend, const Byte &subtrahend, int minuendCount, int minusIndex) {
        // minuend一定是比subtrahend大的, 故不用考虑进位
        ShortByteDivider divider = ByteCalculator::sub(minuend.getByte(minusIndex), subtrahend);
        // divider是负数, divider.getLow()会获取结果的绝对值的字节数
        bool isMinus = divider.getSign() == math::NumberSign::MINUS;
        Byte lowByte = divider.getLow();
        minuend.setByte(minusIndex, isMinus ? Byte(BYTE_RADIX - lowByte.get()) : lowByte);
        // 从高位取数
        for (int j = minusIndex - 1; j >= -minuendCount && isMinus; --j) {
            divider = ByteCalculator::sub(minuend.getByte(j), BYTE_ONE);
            isMinus = divider.getSign() == math::NumberSign::MINUS;
            lowByte = divider.getLow();
            minuend.setByte(j, isMinus ? Byte(BYTE_RADIX - lowByte.get()) : lowByte);
        }
        return minuend;
    }

    /**
     * 绝对值相乘, shrink 会增加效率
     */
    static Data multiply(const Data &data1, const Data &data2) {
        int byteCount1 = data1.byteCount();
        int byteCount2 = data2.byteCount();
        Data result(byteCount1 + byteCount2);
        int data1Count = data1.byteCount();
        // 绝对值相乘
        for (int i = 0; i < byteCount2; ++i) {
            result.leftMoveByte(1);
            result = ByteBigInteger::add(result, ByteBigInteger::multiply(
                    data1, data2.getByte(i), data1Count));
        }
        return ByteBigInteger::newShrinkData(result);
    }

    /**
     *
     * @param data     由于在前面的检查, 必不为0
     * @param oneByte 可能为0
     */
    static Data multiply(const Data &data, const Byte &oneByte, int dataCount) {
        if (oneByte == 0) {
            return DATA_ZERO;
        }
        Data result = Data(dataCount + 1);
        Byte highTemp = BYTE_ZERO; // 乘法运算时留下的高位的数, 进位用
        for (int i = -1; i >= -dataCount; --i) {
            /*std::cout << "-------" << i << "-------" << std::endl;
            math::MathCommons::printMessage("now byte", data.getByte(i).get());*/
            const ShortByteDivider &multiplyDriver = ByteCalculator::multiply(
                    data.getByte(i), oneByte, math::NumberSign::POSITIVE);
            const ShortByteDivider &addDriver = ByteCalculator::add(multiplyDriver.getLow(), highTemp);
            result.setByte(i, addDriver.getLow());
            const ShortByteDivider &highTempDivider = ByteCalculator::add(
                    addDriver.getHigh(), multiplyDriver.getHigh());
            highTemp = highTempDivider.getLow();
            if (highTempDivider.getHigh() != 0) {
                throw IllegalStateException("high can't larger than 256");
            }
        }
        // 进位用位
        result.setByte(0, highTemp);
        return newShrinkData(result, dataCount);
    }

    /**
     *
     * @param absDividend   取绝对值, 经过shrink
     * @param absDivisor    取绝对值, 经过shrink
     * @param absRemainder  取绝对值
     * @return
     */
    static Data divide(Data &absDividend, Data &absDivisor,
                       Data &absRemainder) {
        // 位数对齐

        /* std::cout << "=====param=====" << std::endl;
         absDividend.printMessage("absDividend");
         absDivisor.printMessage("absDivisor");
         absRemainder.printMessage("absRemainder");*/

        int absDividendCount = absDividend.byteCount();
        int absDivisorCount = absDivisor.byteCount();
        int offset = absDividendCount - absDivisorCount;
        // 讨论
        if (offset == 0) {
            int diff = ByteBigInteger::compare(absDividend, absDivisor, absDividendCount);
            if (diff == 0) {
                absRemainder = DATA_ZERO;
                return Data(1, Byte(1));
            } else if (diff > 0) {
                // 已经对齐, absDividend>absDivisor
                return Data(1, divideGracefulButSlowerALittle(absDividend, absDivisor, absRemainder));
            }
        }
        if (offset <= 0) {
            absRemainder = ByteBigInteger::newShrinkData(absDividend);
            return Data(0);
        }
        // 数位对齐
        absDivisor = absDivisor.leftMoveByteGrow(offset);
        // 轮换相减
        Data quotient(0); // 商
        absRemainder = absDividend;
        while (offset-- >= 0) { // offset=1
            quotient = quotient.leftMoveByteGrow(1);
            // 依据absRemainder调整absDividend*/
            quotient.setByte(-1, divideGracefulButSlowerALittle(absDividend, absDivisor, absRemainder));
            absDividend = absRemainder;
            absDivisor = absDivisor.rightMoveByteShrink(1);
        }
        if (offset >= 0) {
            quotient = quotient.leftMoveByteGrow(1 + offset);
        }
        return newShrinkData(quotient);
    }

    /**
     * @param absDividend 比absDivisor大, (不含前导0)
     * @param absDivisor  比absDividend小, (不含前导0)
     * @return quotient 商
     * @deprecated
     */
    static Byte divideUglyButFasterALittle(const Data &dividend, const Data &divisor, Data &remainder) {
        int dividendCount = dividend.byteCount();
        int divisorCount = divisor.byteCount();
        int offset = dividendCount - divisorCount;
        if (offset < 0) {
            remainder = dividend;
            return BYTE_ZERO;
        }
        size_t numberSize = sizeof(math::number);
        int dividendEnd = std::min((size_t) dividendCount, numberSize);
        unsigned long long dividendSum = 0;
        for (int i = 0; i < dividendEnd; ++i) {
            dividendSum <<= 8;
            dividendSum += dividend.getByte(i).get();
        }
        int divisorEnd = std::min((size_t) divisorCount, numberSize - offset);
        unsigned long long divisorSum = 0;
        for (int i = 0; i < divisorEnd; ++i) {
            divisorSum <<= 8;
            divisorSum += divisor.getByte(i).get();
        }
        unsigned long long int guessValue = dividendSum / divisorSum;
        if (guessValue >= BYTE_RADIX) {
            math::NumberSign sign = ByteBigInteger::tryGuess256(dividend, divisor, remainder);
            guessValue = BYTE_RADIX - 1;
        }
        Byte guess(guessValue);
        math::NumberSign sign = ByteBigInteger::tryGuess(guess, dividend, divisor, remainder);
        switch (sign) {
            case math::ZERO: {
                remainder = DATA_ZERO;
                return guess;
            }
            case math::POSITIVE: {
                // guessValue 过小了
                int count = 0;
                while (guessValue < BYTE_RADIX - 1) {
                    if (++count > ByteBigInteger::maxPOSITIVE) {
                        ByteBigInteger::maxPOSITIVE = count;
                    }
                    Byte guessPositive(guessValue + 1);
                    if (tryGuess(guessPositive, dividend, divisor, remainder) != math::NumberSign::MINUS) {
                        // 过大就抛出异常
                        guessValue++;
                    }
                    return Byte(guessValue);
                }
                if (tryGuess256(dividend, divisor, remainder) != math::NumberSign::MINUS) {
                    // 过大就抛出异常
                    throw IllegalStateException("Unknown State: It's impossible!");
                }
                return BYTE_FULL;
            }
            case math::MINUS: {
                // guessValue 过大了
                int count = 0;
                while (guessValue > 1) {
                    if (++count > ByteBigInteger::maxMINUS) {
                        maxMINUS = count;
                    }
                    Byte guessMinus(guessValue - 1);
                    if (tryGuess(guessMinus, dividend, divisor, remainder) != math::NumberSign::MINUS) {
                        // 偏小就返回
                        return guessMinus;
                    }
                    guessValue--;
                }
                // 偏小就返回
                return BYTE_ZERO;
            }
            default:
                throw IllegalStateException("Unknown number sign");
        }
    }

    static int maxMINUS;
    static int maxPOSITIVE;

    /**
     * 如果成功需要给absRemainder注入值, 不成功就不要动absRemainder
     * @return guess*absDivisor<absDividend
     */
    static math::NumberSign tryGuess(
            const Byte &guess,
            const Data &absDividend,
            const Data &absDivisor, Data &absRemainder) {
        ByteBigInteger difference =
                multiplyTryGuess(guess, absDividend, absDivisor);
        if (!difference.isMinus()) {
            // 不能进入该分支说明guess过大了
            // 能进入说明guess过小或刚好
            absRemainder = difference.data;
        }
        return difference.numberSign;
    }

    static math::NumberSign tryGuess(
            const int &guess,
            const Data &absDividend,
            const Data &absDivisor, Data &absRemainder) {
        ByteBigInteger difference = multiplyTryGuess(guess, absDividend, absDivisor);
        if (!difference.isMinus()) {
            // 不能进入该分支说明guess过大了
            // 能进入说明guess过小或刚好
            absRemainder = difference.data;
        }
        return difference.numberSign;
    }

    static ByteBigInteger multiplyTryGuess(const Byte &guess, const Data &absDividend,
                                           const Data &absDivisor) {
        return ByteBigInteger(absDividend) - (ByteBigInteger(guess.get()) * ByteBigInteger(absDivisor));
    }

    static ByteBigInteger multiplyTryGuess(const int &guess, const Data &absDividend,
                                           const Data &absDivisor) {
        return ByteBigInteger(absDividend) - (ByteBigInteger(guess) * ByteBigInteger(absDivisor));
    }

    static math::NumberSign tryGuess256(
            const Data &absDividend,
            const Data &absDivisor, Data &absRemainder) {
        ByteBigInteger difference =
                ByteBigInteger(absDividend) - (ByteBigInteger(BYTE_RADIX) * ByteBigInteger(absDivisor));
        if (!difference.isMinus()) {
            throw IllegalStateException("Unknown State: It's impossible!");
        }
        return difference.numberSign;
    }


    /**
     * @param dividend 比absDivisor大, (不含前导0)
     * @param divisor  比absDividend小, (不含前导0)
     * @return quotient 商
     */
    static Byte divideGracefulButSlowerALittle(const Data &dividend, const Data &divisor, Data &remainder) {
        int left = 0;
        int right = BYTE_RADIX - 1;
        int guess = (left + right) / 2;
        math::NumberSign sign;
        while (left <= right) {
            sign = tryGuess(guess, dividend, divisor, remainder);
            switch (sign) {
                case math::ZERO:
                    remainder = DATA_ZERO;
                    return Byte(guess);
                case math::POSITIVE:
                    // guessValue 过小了
                    left = guess + 1;
                    guess = (left + right) / 2;
                    break;
                case math::MINUS:
                    // guessValue 过大了
                    right = guess - 1;
                    guess = (left + right) / 2;
                    break;
                default:
                    throw IllegalStateException("Unknown number sign");
            }
        }
        sign = tryGuess(guess, dividend, divisor, remainder);
        switch (sign) {
            case math::ZERO:
                remainder = DATA_ZERO;
                break;
            case math::POSITIVE:
                // guessValue 过小了
                sign = tryGuess(guess + 1, dividend, divisor, remainder);
                if (sign == math::POSITIVE) {
                    // 依然过小
                    throw IllegalStateException("Unknown State: It's impossible!");
                }
                break;
            case math::MINUS:
                // guessValue 过大了
                if (guess == 0) {
                    throw IllegalStateException("Unknown State: It's impossible!");
                }
                guess = guess - 1;
                sign = tryGuess(guess, dividend, divisor, remainder);
                if (sign == math::MINUS) {
                    // guessValue 过大了
                    throw IllegalStateException("Unknown State: It's impossible!");
                }
                break;
        }
        return Byte(guess);
    }

};


#endif //ALGORITHM_BYTE_BIG_INTEGER_H
