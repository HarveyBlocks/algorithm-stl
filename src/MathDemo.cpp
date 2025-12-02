#include "math/Data.h"
#include "math/BigInteger.h"
#include "math/ByteCalculator.h"
#include "util/Random.h"
#include "math/ByteBigInteger.h"

/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/8/30
 *
 */

void testRightMove(const Data &data, int off) {
    // std::cout << "--" << off << "--" << std::endl;
    Data data2 = data >> off;
    // std::cout << (std::string) byteArray << std::endl;
    std::cout << (std::string) data2 << std::endl;
}

void testLeftMove(const Data &data, int off) {
    // std::cout << "--" << off << "--" << std::endl;
    Data data2 = data << off;
    // std::cout << (std::string) byteArray << std::endl;
    std::cout << (std::string) data2 << std::endl;
}

int dataDemo() {
    std::cout << sizeof(int) << std::endl;
    std::cout << (std::string) DATA_ZERO << std::endl;
    Data data(10);
    std::cout << (std::string) data << std::endl;
    data.setByte(8, Byte(63));
    data.setByte(-1, Byte(0x64));
    std::cout << (std::string) data << std::endl;
    std::cout << data << std::endl;
    // data.shrink(packaging::ZERO);
    std::cout << (std::string) data << std::endl;
    std::cout << data << std::endl;
    Data newData = data | Data(1, Byte(1));
    std::cout << (std::string) data << std::endl;
    std::cout << (std::string) newData << std::endl;
    std::cout << data << std::endl;
    std::cout << newData << std::endl;
    data = data | Data(1, Byte(1));
    std::cout << (std::string) data << std::endl;
    std::cout << data << std::endl;
    std::cout << "----" << std::endl;
    std::cout << (std::string) data << std::endl;
    testLeftMove(data, 0);
    testLeftMove(data, 1);
    testLeftMove(data, 2);
    testLeftMove(data, 3);
    testLeftMove(data, 4);
    testLeftMove(data, 5);
    testLeftMove(data, 6);
    testLeftMove(data, 7);
    testLeftMove(data, 8);
    testLeftMove(data, 9);
    testLeftMove(data, 10);
    testLeftMove(data, 11);
    testLeftMove(data, 12);
    testLeftMove(data, 13);
    testLeftMove(data, 14);
    testLeftMove(data, 15);
    testLeftMove(data, 16);
    testLeftMove(data, 17);
    testRightMove(data, 0);
    testRightMove(data, 1);
    testRightMove(data, 2);
    testRightMove(data, 3);
    testRightMove(data, 4);
    testRightMove(data, 5);
    testRightMove(data, 6);
    testRightMove(data, 7);
    testRightMove(data, 8);
    testRightMove(data, 9);
    testRightMove(data, 10);
    testRightMove(data, 11);
    testRightMove(data, 12);
    testRightMove(data, 13);
    testRightMove(data, 14);
    testRightMove(data, 15);
    testRightMove(data, 16);
    testRightMove(data, 17);
    testRightMove(data, 35);
    testRightMove(data, 77);
    data <<= 2;
    std::cout << (std::string) data << std::endl;
    data >>= 10;
    std::cout << (std::string) data << std::endl;
    data >>= 10;
    std::cout << (std::string) data << std::endl;
    data |= Data(2, Byte(5));
    std::cout << (std::string) data << std::endl;
    data &= Data(2, Byte(0));
    std::cout << (std::string) data << std::endl;
    data ^= Data(2, Byte(12));
    std::cout << (std::string) data << std::endl;

    return 0;
}

ByteBigInteger bigIntegerRandomCreator(int len) {
    StringBuilder sb;
    for (int i = 0; i < len; ++i) {
        sb.append((char) ((char) (Random::unsignedByte() % 10) + '0'));
    }
    return ByteBigInteger::phaseDecString(sb.toString());
};

int rightMoveDemo() {
    for (int i = 1; i <= 1000000L; ++i) {
        BigInteger bigInteger(Random::signedLongLong());
        if (i % 100000L == 0) {
            std::cout << "checkpoint, a.dataSize=" << bigInteger.byteCount() << std::endl;
        }
        for (int j = 0; j < bigInteger.byteCount() * Byte::BIT_COUNT + 5; ++j) {
            std::cout << (std::string) (bigInteger >> j) << "\t" << (math::number) (bigInteger >> j) << std::endl;
        }
    }
    return 0;
}

int leftMoveDemo() {
    for (int i = 1; i <= 1000000L; ++i) {
        BigInteger bigInteger(Random::signedShort());
        if (i % 100000L == 0) {
            std::cout << "checkpoint, a.dataSize=" << bigInteger.byteCount() << std::endl;
        }
        for (int j = 0; j < 125; ++j) {
            std::cout << (std::string) (bigInteger << j) << "\t" << (math::number) (bigInteger << j) << std::endl;
        }
    }
    return 0;
}


int shortCalculateDemo() {
    std::cout << (std::string) ByteCalculator::multiply(Byte(255), Byte(255), math::NumberSign::POSITIVE) << std::endl;
    std::cout << (std::string) ByteCalculator::add(Byte(255), Byte(255)) << std::endl;
    std::cout << (std::string) ByteCalculator::sub(Byte(255), Byte(255)) << std::endl;
    std::cout << (std::string) ByteCalculator::divide(Byte(255), Byte(255)) << std::endl;
    std::cout << (std::string) ByteCalculator::mod(Byte(255), Byte(255)) << std::endl;
    return 0;
}


int constructorDemo() {
    std::cout << (math::number) ByteBigInteger(12) << std::endl;
    std::cout << (std::string) ByteBigInteger(12) << std::endl;
    std::cout << (math::number) ByteBigInteger(127) << std::endl;
    std::cout << (std::string) ByteBigInteger(127) << std::endl;
    std::cout << (math::number) ByteBigInteger(128) << std::endl;
    std::cout << (std::string) ByteBigInteger(128) << std::endl;
    std::cout << (math::number) ByteBigInteger(-21) << std::endl;
    std::cout << (std::string) ByteBigInteger(-21) << std::endl;
    std::cout << (math::number) ByteBigInteger(-127) << std::endl;
    std::cout << (std::string) ByteBigInteger(-127) << std::endl;
    std::cout << (math::number) ByteBigInteger(-128) << std::endl;
    std::cout << (std::string) ByteBigInteger(-128) << std::endl;
    std::cout << (math::number) ByteBigInteger(0xffffffffffffffffL) << std::endl;
    for (int i = 1; i <= 1000000L; ++i) {
        auto num = (math::number) Random::unsignedLongLong();
        ByteBigInteger a(num);
        if (i % 100000L == 0) {
            std::cout << "checkpoint, a.dataSize=" << a.byteCount() << std::endl;
        }
        if (((math::number) a) != num) {
            std::cout << num << std::endl;
            std::cout << (math::number) a << std::endl;
            std::cout << (std::string) a << std::endl;
            std::cout << math::MathCommons::binaryNumberString(num) << std::endl;
        }
    }
    return 0;
}

int compareDemo() {
    math::number num1 = 11;
    math::number num2 = 10;
    BigInteger integer1(num1);
    BigInteger integer2(num2);
    std::cout << BigInteger::compare(integer1, integer2) << std::endl;
    std::cout << BigInteger::compare(integer2, integer1) << std::endl;
    std::cout << BigInteger::compare(integer1, integer1) << std::endl;
    std::cout << BigInteger::compare(integer2, integer2) << std::endl;
    for (int i = 1; i <= 1000000L; ++i) {
        num1 = Random::signedInt();
        num2 = Random::signedInt();
        ByteBigInteger bigInteger1(num1);
        ByteBigInteger bigInteger2(num2);
        if (i % 100000L == 0) {
            std::cout << "checkpoint" << std::endl;
        }
        math::number standard = num1 - num2;
        standard = standard == 0 ? 0 : (standard > 0 ? 1 : -1);
        int result = ByteBigInteger::compare(bigInteger1, bigInteger2);
        result = result == 0 ? 0 : (result > 0 ? 1 : -1);
        if (result != standard) {
            std::cout << "num1 = " << math::MathCommons::binaryNumberString(std::abs(num1)) << std::endl;
            std::cout << "num2 = " << math::MathCommons::binaryNumberString(std::abs(num2)) << std::endl;
            std::cout << result << std::endl;
            std::cout << standard << std::endl;
        }
    }
    return 0;
}

int addSubDemo() {
    ByteBigInteger bigInteger01(128);
    ByteBigInteger bigInteger02(-128);
    ByteBigInteger sum0 = ByteBigInteger::add(bigInteger01, bigInteger02);
    std::cout << "sum=" << (math::number) sum0 << std::endl;
    ByteBigInteger sub0 = ByteBigInteger::sub(bigInteger01, bigInteger02);
    std::cout << "sub=" << (math::number) sub0 << std::endl;
    ByteBigInteger reserveSub0 = ByteBigInteger::sub(bigInteger02, bigInteger01);
    std::cout << "sub'=" << (math::number) reserveSub0 << std::endl;
    bigInteger01 = ByteBigInteger(256);
    bigInteger02 = ByteBigInteger(128);
    sum0 = ByteBigInteger::add(bigInteger01, bigInteger02);
    std::cout << "sum=" << (math::number) sum0 << std::endl;
    sub0 = ByteBigInteger::sub(bigInteger01, bigInteger02);
    std::cout << "sub=" << (math::number) sub0 << std::endl;
    reserveSub0 = ByteBigInteger::sub(bigInteger02, bigInteger01);
    std::cout << "sub'=" << (math::number) reserveSub0 << std::endl;
    for (int i = 1; i <= 1000000L; ++i) {
        auto num1 = Random::signedLongLong();
        auto num2 = Random::signedLongLong();
        ByteBigInteger bigInteger1(num1);
        ByteBigInteger bigInteger2(num2);
        const ByteBigInteger &sum = ByteBigInteger::add(bigInteger1, bigInteger2);
        const ByteBigInteger &sum_ = ByteBigInteger::add(bigInteger2, bigInteger1);
        const ByteBigInteger &sub = ByteBigInteger::sub(bigInteger1, bigInteger2);
        const ByteBigInteger &sub_ = ByteBigInteger::sub(bigInteger2, bigInteger1);


        if (i % 100000L == 0) {
            std::cout << "checkpoint, a.dataSize=" << sum.byteCount() << std::endl;
        }
        if ((math::number) sum != (num1 + num2)) {
            std::cout << "num1 = " << math::MathCommons::binaryNumberString(std::abs(num1)) << std::endl;
            std::cout << "num2 = " << math::MathCommons::binaryNumberString(std::abs(num2)) << std::endl;
            std::cout << "sum = " << (math::number) sum << std::endl;
            std::cout << "sum = " << (num1 + num2) << std::endl << std::endl;
            std::cout << "sum = " << (std::string) sum << std::endl;
            std::cout << "sum = " << math::MathCommons::binaryNumberString(std::abs(num1 + num2)) << std::endl;
        }
        if ((math::number) sum_ != (num2 + num1)) {
            std::cout << "num1 = " << math::MathCommons::binaryNumberString(std::abs(num1)) << std::endl;
            std::cout << "num2 = " << math::MathCommons::binaryNumberString(std::abs(num2)) << std::endl;
            std::cout << "sum' = " << (math::number) sum_ << std::endl;
            std::cout << "sum' = " << (num2 + num1) << std::endl << std::endl;
            std::cout << "sum' = " << (std::string) sum_ << std::endl;
            std::cout << "sum' = " << math::MathCommons::binaryNumberString(std::abs(num2 + num1)) << std::endl;
        }
        if ((math::number) sub != (num1 - num2)) {
            std::cout << "num1 = " << math::MathCommons::binaryNumberString(std::abs(num1)) << std::endl;
            std::cout << "num2 = " << math::MathCommons::binaryNumberString(std::abs(num2)) << std::endl;
            std::cout << "sub = " << (math::number) sub << std::endl;
            std::cout << "sub = " << (num1 - num2) << std::endl << std::endl;
            std::cout << "sub = " << (std::string) sub << std::endl;
            std::cout << "sub = " << math::MathCommons::binaryNumberString(std::abs(num1 - num2)) << std::endl;
        }
        if ((math::number) sub_ != (num2 - num1)) {
            std::cout << "num1 = " << math::MathCommons::binaryNumberString(std::abs(num1)) << std::endl;
            std::cout << "num2 = " << math::MathCommons::binaryNumberString(std::abs(num2)) << std::endl;
            std::cout << "sub' = " << (math::number) sub_ << std::endl;
            std::cout << "sub' = " << (num2 - num1) << std::endl << std::endl;
            std::cout << "sub' = " << (std::string) sub_ << std::endl;
            std::cout << "sub' = " << math::MathCommons::binaryNumberString(std::abs(num2 - num1)) << std::endl;
        }
    }
    return 0;
}

int increaseDemo() {
    ByteBigInteger bigInteger(-/*200212132413011231*/0023L);
    for (math::number i = -/*200212132413011231*/0022L; i < /*20021213241301123*/10023L; ++i) {
        auto result = (math::number) (++bigInteger);
        if (i % 100000L == 0) {
            std::cout << "checkpoint, a.dataSize=" << bigInteger.byteCount() << std::endl;
        }
        if (result != i) {
            std::cout << "false" << std::endl;
        }
    }
    return 0;
}

int compositeDemo() {
    std::cout << (std::string) ByteBigInteger(0) << " " << 0 << std::endl;
    std::cout << (std::string) -ByteBigInteger(0) << " " << 0 << std::endl;
    std::cout << (std::string) ByteBigInteger(12) << " " << 12 << std::endl;
    std::cout << (std::string) -ByteBigInteger(12) << " " << -12 << std::endl;
    std::cout << (std::string) ByteBigInteger(128) << " " << 128 << std::endl;
    std::cout << (std::string) -ByteBigInteger(128) << " " << -128 << std::endl;
    std::cout << (std::string) ByteBigInteger(-12) << " " << -12 << std::endl;
    std::cout << (std::string) -ByteBigInteger(-12) << " " << 12 << std::endl;
    std::cout << (std::string) ByteBigInteger(-128) << " " << -128 << std::endl;
    std::cout << (std::string) -ByteBigInteger(-128) << " " << 128 << std::endl;

    std::cout << (math::number) ByteBigInteger(0) << " " << 0 << std::endl;
    std::cout << (math::number) -ByteBigInteger(0) << " " << 0 << std::endl;
    std::cout << (math::number) ByteBigInteger(12) << " " << 12 << std::endl;
    std::cout << (math::number) -ByteBigInteger(12) << " " << -12 << std::endl;
    std::cout << (math::number) ByteBigInteger(128) << " " << 128 << std::endl;
    std::cout << (math::number) -ByteBigInteger(128) << " " << -128 << std::endl;
    std::cout << (math::number) ByteBigInteger(-12) << " " << -12 << std::endl;
    std::cout << (math::number) -ByteBigInteger(-12) << " " << 12 << std::endl;
    std::cout << (math::number) ByteBigInteger(-128) << " " << -128 << std::endl;
    std::cout << (math::number) -ByteBigInteger(-128) << " " << 128 << std::endl;
    for (int i = 1; i <= 1000000L; ++i) {
        auto num = (math::number) Random::unsignedLongLong();
        ByteBigInteger a(num);
        if (i % 100000L == 0) {
            std::cout << "checkpoint, a.dataSize=" << a.byteCount() << std::endl;
        }
        if (((math::number) -a) != -num) {
            std::cout << num << std::endl;
            std::cout << (math::number) a << std::endl;
            std::cout << (std::string) a << std::endl;
            std::cout << math::MathCommons::binaryNumberString(num) << std::endl;
        }
    }
    return 0;
}


void simpleMultiplyDemo(math::number num1, math::number num2) {
    ByteBigInteger integer1(num1);
    ByteBigInteger integer2(num2);
    const ByteBigInteger &res = integer1 * integer2;
    std::cout << (math::number) (num1) << "*"
              << (math::number) (num2) << "="
              << (math::number) (num1 * num2) << ", but: "
              << (math::number) res
              << std::endl;
    std::cout << (std::string) res << std::endl;
    std::cout << (std::string) ByteBigInteger(num1 * num2) << std::endl;
}

int multiplyDemo() {
    simpleMultiplyDemo(-1, -1);
    simpleMultiplyDemo(1, 2);
    simpleMultiplyDemo(351, 312);
    simpleMultiplyDemo(12412312, 123124124312);
    for (int i = 1; i <= 100000L; ++i) {
        math::number num1 = Random::signedInt();
        math::number num2 = Random::signedInt();
        ByteBigInteger bigInteger1(num1);
        ByteBigInteger bigInteger2(num2);

        const ByteBigInteger &integer = bigInteger1 * bigInteger2;
        if (i % 10000L == 0) {
            std::cout << "checkpoint, a.dataSize=" << bigInteger1.byteCount() <<
                      ", b.dataSize=" << bigInteger2.byteCount() <<
                      ", result.dataSize=" << integer.byteCount() << std::endl;
        }
        auto result = (math::number) integer;
        math::number cppResult = num1 * num2;
        if (cppResult != result) {
            std::cout << (math::number) (bigInteger1) << "/" << (math::number) (num1)
                      << "*"
                      << (math::number) (bigInteger2) << "/" << (math::number) (num2)
                      << "="
                      << (math::number) cppResult << ", but: "
                      << result
                      << std::endl;
            std::cout << (std::string) bigInteger1 << std::endl;
            std::cout << (std::string) bigInteger2 << std::endl;
            std::cout << (std::string) integer << std::endl;
            std::cout << (std::string) ByteBigInteger(cppResult) << std::endl;
        }
    }
    return 0;
}


int divideDemo() {
    // abs(i) % abs(j) == abs(i % j) 恒成立
    // / : 负负得正
    // % : 全看被除数
    // std::cout << -13 / 3 << std::endl;
    math::number num1 = 1100;
    math::number num2 = 10;
    ByteBigInteger integer1(num1);
    ByteBigInteger integer2(num2);
    ByteBigInteger remainder(1);
    std::cout << (math::number) ByteBigInteger::divide(integer1, integer2, remainder) << " 110" << std::endl;
    std::cout << (math::number) remainder << " 0" << std::endl;
    std::cout << (math::number) ByteBigInteger::divide(integer2, integer1, remainder) << " 0" << std::endl;
    std::cout << (math::number) remainder << " 10" << std::endl;
    std::cout << (math::number) ByteBigInteger::divide(integer1, integer1, remainder) << " 1" << std::endl;
    std::cout << (math::number) remainder << " 0" << std::endl;
    std::cout << (math::number) ByteBigInteger::divide(integer2, integer2, remainder) << " 1" << std::endl;
    std::cout << (math::number) remainder << " 0" << std::endl;
    std::cout << "------------------" << std::endl;
    for (int i = 1024; i < 1024; ++i) {
        for (int j = -1024; j < 1024; ++j) {
            if (j == 0) {
                continue;
            }
            ByteBigInteger dividend(i);
            ByteBigInteger divisor(j);
            const ByteBigInteger &quotient = ByteBigInteger::divide(dividend, divisor, remainder);
            bool b1 = quotient.operator!=(i / j);
            bool b2 = remainder != (i % j);
            if (b1 || b2) {
                std::cout << "quotient: " << i / j << std::endl;
                std::cout << "remainder: " << i % j << std::endl;
                quotient.printMessage("quotient");
                remainder.printMessage("remainder");
            }
        }
        if (i % 16 == 0) {
            std::cout << "[" << i / 16 << "]checkpoint: remainder.dataSize = " << remainder.byteCount() << std::endl;
        }
    }
    for (int index = 0; index < 100000; ++index) {
        // math::number i = Random::signedLongLong();
        // math::number j = Random::signedInt();
        /*math::MathCommons::printAbsMessage("i", i);
        math::MathCommons::printAbsMessage("j", j);*/
        /*if (j == 0) {
            continue;
        }*/
        ByteBigInteger dividend = bigIntegerRandomCreator(24);
        ByteBigInteger divisor = bigIntegerRandomCreator(10);
        const ByteBigInteger &quotient = ByteBigInteger::divide(dividend, divisor, remainder);
        /*bool b1 = quotient.operator!=(i / j);
        bool b2 = remainder != (i % j);
        if (b1 || b2) {
            math::MathCommons::printMessage("i", i);
            math::MathCommons::printMessage("j", j);
            math::MathCommons::printMessage("i / j", i / j);
            math::MathCommons::printMessage("i % j", i % j);
            quotient.printMessage("quotient");
            remainder.printMessage("remainder");
        }*/
        if (index % 1000 == 0) {
            std::cout << "[" << index / 1000 << "]checkpoint: remainder.dataSize = " << remainder.byteCount()
                      << std::endl;
        }
    }
    return 0;
}

int stringDemo() {
    std::cout << ByteBigInteger::phaseDecString(String("   \t\n\t12345098765432123476398612\t  \n"), 10).toString(10, 0)
              << std::endl;
    std::cout << ByteBigInteger::phaseDecString(String("12345098765432123476398612"), 10).toString(10, '_')
              << std::endl;
    std::cout << ByteBigInteger::phaseDecString(String("34567891254345612738178754123871247912"), 10).toString(10, ',')
              << std::endl;
    return 0;
}

int factorial() {
    int n = 250/*25000*/;
    ByteBigInteger bigInteger = Calculator<ByteBigInteger>::phaseDecString(String("1"));
    for (int i = 2; i <= n; i++) {
        bigInteger = ByteBigInteger::multiply(bigInteger, ByteBigInteger(i));
        if (i % 100 == 0) {
            std::cout << "[" << i << "]checkpoint: remainder.dataSize = " << bigInteger.byteCount() << std::endl;
        }
    }
    std::cout << bigInteger.toString(10, 0).getSize() << std::endl;
    return 0;
}

int find(double key) {
    int left = 0;
    int right = 255;
    int mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (std::abs(key - mid) < 0.01) {
            return mid;
        } else if (mid < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return mid;
}

// 示例用法
int mathDemo() {
    return divideDemo();
}

// int mathCode = mathDemo();

