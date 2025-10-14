/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/9/1
 *
 */
#ifndef ALGORITHM_COMMONS_H
#define ALGORITHM_COMMONS_H

#include "../lang/exception/IllegalStateException.h"
#include "sstream"
#include "iostream"

namespace math {
    using number = signed long long int;
    using byte = unsigned char;
    enum NumberSign {
        MINUS, ZERO, POSITIVE
    };

    class MathCommons {
    private:
        MathCommons() {};
    public:
        static NumberSign signOf(number n) {
            if (n > 0) {
                return POSITIVE;
            } else if (n < 0) {
                return MINUS;
            } else {
                return ZERO;
            }
        }

        static NumberSign oppositeOf(NumberSign numberSign) {
            switch (numberSign) {
                case math::MINUS:
                    return math::POSITIVE;
                case math::POSITIVE:
                    return math::MINUS;
                case math::ZERO:
                    return math::ZERO;
                default:
                    throw IllegalStateException("Unknown sign");
            }
        }

        static int getValue(NumberSign numberSign) {
            switch (numberSign) {
                case math::MINUS:
                    return -1;
                case math::POSITIVE:
                    return 1;
                case math::ZERO:
                    return 0;
                default:
                    throw IllegalStateException("Unknown sign");
            }
        }

        static std::string binaryNumberString(const number &value) {
            number var = value;
            std::stringstream ss;
            ss << "[";
            for (int j = 1; j < 64; ++j) {
                ss << ((var >> 63) & 0x01);
                if (j % 8 == 0) {
                    ss << ", ";
                }
                var <<= 1;
            }
            ss << (var & 0x01) << "]";
            return ss.str();
        }

        static void printMessage(const std::string &varName, const math::number &var) {
            std::cout << varName << " [value] : " << var << std::endl;
            std::cout << varName << " [binary]: " << MathCommons::binaryNumberString(var) << std::endl;
        }

        static void printAbsMessage(const std::string &varName, const math::number &var) {
            std::cout << varName << " [value] : " << var << std::endl;
            std::cout << varName << " [abs binary]: " << MathCommons::binaryNumberString(std::abs(var)) << std::endl;
        }
    };
}
#endif //ALGORITHM_COMMONS_H
