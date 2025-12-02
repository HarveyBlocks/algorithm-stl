/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/24
 *
 */
#ifndef ALGORITHM_INTEGER_H
#define ALGORITHM_INTEGER_H


#include "../exception/OverflowException.h"
#include "../exception/DownflowException.h"
#include <climits>
#include <iostream>

class Integer {
private:
    int value;
public:
    static const int MAX = INT_MAX;
    static const int MIN = INT_MIN;
    static const unsigned int SIGN_BIT = MIN;

    explicit Integer(int value) : value(value) {}

    Integer() : value(0) {}

    bool operator&&(const int &number) const {
        return this->value && number;
    }

    bool operator||(const int &number) const {
        return this->value || number;
    }

    bool operator&&(const Integer &number) const {
        return this->operator&&(number.value);
    }

    bool operator||(const Integer &number) const {
        return this->operator||(number.value);
    }

    bool operator!() const {
        return !this->value;
    }

    bool operator==(const int &number) const {
        return this->value == number;
    }

    bool operator==(const Integer &number) const {
        return this->operator==(number.value);
    }

    bool operator!=(const int &number) const {
        return !this->operator==(number);
    }

    bool operator!=(const Integer &number) const {
        return this->operator!=(number.value);
    }

    explicit operator bool() const {
        return this->value != 0;
    }

    Integer operator+() const {
        return Integer(this->value);
    }

    Integer operator+(const int &num) const {
        if ((num & SIGN_BIT) && (this->value & SIGN_BIT)) {
            if (MIN - num > this->value) {
                throw DownflowException();
            }
        } else if (!(num & SIGN_BIT) && !(this->value & SIGN_BIT)) {
            if (MAX - num < this->value) {
                throw OverflowException();
            }
        }
        return Integer(this->value + num);
    }

    Integer operator+(const Integer &num) const {
        return this->operator+(num.value);
    }

    friend Integer operator+(const int &num1, const Integer &num2) {
        return num2.operator+(num1);
    }

    Integer operator-() const {
        if (MIN == this->value) {
            throw OverflowException();
        }
        return Integer(-this->value);
    }

    friend std::ostream &operator<<(std::ostream &os, const Integer &num) {
        return os << num.value;
    }


};


#endif //ALGORITHM_INTEGER_H
