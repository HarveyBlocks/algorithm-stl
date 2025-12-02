/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/9/1
 *
 */
#ifndef ALGORITHM_CALCULATOR_H
#define ALGORITHM_CALCULATOR_H


#include "MathComparable.h"
#include "commons.h"
#include "../lang/StringBuilder.h"

template<class T>
class Calculator : public MathComparable<T> {
protected:
    virtual T &getThis() = 0;

    virtual T copyThis() const = 0;

public:
    static char number2Character(math::number value) {
        return (char) ((math::number) ((value < 10 ? '0' : ('A' - 10)) + value));
    }

    static math::number character2Number(char character) {
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

    static T phaseDecString(const String &src, int radix = 10) {
        if (radix > 36 || radix <= 1) {
            throw IllegalStateException("not supported radix: " + std::to_string(radix));
        }
        const String &str = src.trim();
        T result;
        T bigRadix = result.instance(radix);
        int strSize = str.getSize();
        int i = 0;
        if (str[0] == '-') {
            // 取相反数
            result.toOpposite();
            i++;
        }
        for (; i < strSize; ++i) {
            math::number number = Calculator::character2Number(str.at(i));
            if (number < 0) {
                throw IllegalArgumentException("Unknown Character in number string");
            }
            if (number >= radix) {
                throw IllegalArgumentException("Illegal Character in radix :" + std::to_string(radix));
            }
            result = result * bigRadix + T(number);
        }

        return result;
    }

    [[nodiscard]] virtual String toString(int radix, char separator) const = 0;

    [[nodiscard]] virtual bool isPositive() const = 0;

    [[nodiscard]] virtual bool isZero() const = 0;

    [[nodiscard]] virtual bool isMinus() const = 0;

    [[nodiscard]] virtual T abs() const = 0;


    virtual T operator-() const = 0;

    virtual T operator*(const T &other) const = 0;

    virtual T operator+(const T &other) const = 0;

    virtual T operator-(const T &other) const = 0;

    virtual T operator/(const T &other) const = 0;

    virtual T operator%(const T &other) const = 0;

    virtual T &operator*=(const T &other) = 0;

    virtual T &operator+=(const T &other) = 0;

    virtual T &operator-=(const T &other) = 0;

    virtual T &operator/=(const T &other) = 0;

    virtual T &operator%=(const T &other) = 0;

    virtual T operator*(const math::number &number) const = 0;

    virtual T operator+(const math::number &number) const = 0;

    virtual T operator-(const math::number &number) const = 0;

    virtual T operator/(const math::number &number) const = 0;

    virtual T operator%(const math::number &number) const = 0;

    virtual T &operator*=(const math::number &number) = 0;

    virtual T &operator+=(const math::number &number) = 0;

    virtual T &operator++() = 0;

    virtual T &operator-=(const math::number &number) = 0;

    virtual T &operator/=(const math::number &number) = 0;

    virtual T &operator%=(const math::number &number) = 0;

    virtual explicit operator math::number() const = 0;
};


#endif //ALGORITHM_CALCULATOR_H
