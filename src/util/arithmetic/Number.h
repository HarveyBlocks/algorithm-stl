/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/7/30
 *
 */
#ifndef ALGORITHM_NUMBER_H
#define ALGORITHM_NUMBER_H

#include "string"

enum NumberType {
    DEFAULT, BYTE, INTEGER, LONG, FLOUT, DOUBLE
};

class Number {
    int value;
    NumberType Type;
public:
    static const Number DEFAULT_NUMBER;

    explicit Number(int value);

    [[nodiscard]] int get() const;

    void set(int value);

    [[nodiscard]] std::string toString() const;

    friend std::ostream &operator<<(std::ostream &os, const Number &obj) {
        return os << obj.toString();
    }
};

const Number DEFAULT_NUMBER = Number(0);


#endif //ALGORITHM_NUMBER_H
