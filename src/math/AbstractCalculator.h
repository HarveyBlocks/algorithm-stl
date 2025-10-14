/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/9/1
 *
 */
#ifndef ALGORITHM_ABSTRACT_CALCULATOR_H
#define ALGORITHM_ABSTRACT_CALCULATOR_H

#include "Calculator.h"

template<class T>
class AbstractCalculator : public Calculator<T> {
public:
    explicit AbstractCalculator(const math::number &number = 0) {}

    T abs() const override {
        const T &t = this->copyThis();
        return this->isMinus() ? t.operator-() : t;
    }

    T operator-() const override {
        return this->getOpposite();
    }

    T operator*(const T &other) const override {
        return this->multiply(other);
    }

    T operator+(const T &other) const override {
        return this->add(other);
    }


    T operator-(const T &other) const override {
        return this->sub(other);
    }

    T operator/(const T &other) const override {
        T remainder;
        return this->divide(other, remainder);
    }

    T operator%(const T &other) const override {
        T remainder;
        this->divide(other, remainder);
        return remainder;
    }

    T &operator*=(const T &other) override {
        return this->cloneFrom(this->operator*(other));
    }

    T &operator+=(const T &other) override {
        return this->cloneFrom(this->operator+(other));
    }

    T &operator-=(const T &other) override {
        return this->cloneFrom(this->operator-(other));
    }

    T &operator/=(const T &other) override {
        return this->cloneFrom(this->operator/(other));
    }

    T &operator%=(const T &other) override {
        return this->cloneFrom(this->operator%(other));
    }

    T operator*(const math::number &number) const override {
        return this->operator*(T(number));
    }

    T operator+(const math::number &number) const override {
        return this->operator+(T(number));
    }

    T operator-(const math::number &number) const override {
        return this->operator-(T(number));
    }

    T operator/(const math::number &number) const override {
        return this->operator/(T(number));
    }

    T operator%(const math::number &number) const override {
        return this->operator%(T(number));
    }

    T &operator*=(const math::number &number) override {
        return this->operator*=(T(number));
    }

    T &operator+=(const math::number &number) override {
        return this->operator+=(T(number));
    }

    T &operator++() override {
        return this->operator+=(T(1));
    }

    T &operator-=(const math::number &number) override {
        return this->operator-=(T(number));
    }

    T &operator/=(const math::number &number) override {
        return this->operator/=(T(number));
    }

    T &operator%=(const math::number &number) override {
        return this->operator%=(T(number));
    }

    [[nodiscard]] String toString(int radix, char separator) const override {
        if (radix > 36 || radix <= 1) {
            throw IllegalStateException("not supported radix: " + std::to_string(radix));
        }
        T bigRadix(radix);
        T num = this->copyThis();
        T remainder;
        StringBuilder builder;
        bool isMinus = num.isMinus();
        if (isMinus) {
            num = -num;
        }
        int count = 0;
        while (!num.isZero()) {
            const T &quotient = num.divide(bigRadix, remainder);
            auto remainderValue = (math::number) remainder;
            char radixRemainder = Calculator<T>::number2Character(remainderValue);
            if (separator != 0 && count == 4) {
                builder.pushFront(separator);
                count = 0;
            }
            builder.pushFront( radixRemainder);
            num = quotient;
            count++;
        }
        if (isMinus) {
            builder.pushFront( '-');
        }
        return builder.toString();
    }

    /**
     * 将自身变成自身的相反数
     * @return *this
     */
    virtual T &toOpposite() = 0;

    virtual T getOpposite() const = 0;

    virtual T add(const T &other) const = 0;

    virtual T sub(const T &other) const = 0;

    virtual T multiply(const T &other) const = 0;

    virtual T divide(const T &divisor, T &remainder) const = 0;

    virtual T &cloneFrom(const T &src) = 0;
};


#endif //ALGORITHM_ABSTRACT_CALCULATOR_H
