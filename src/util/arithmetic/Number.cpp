/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/7/30
 *
 */
#include "Number.h"

Number::Number(int value) : value(value) {}

int Number::get() const {
    return value;
}

void Number::set(int _value) {
    Number::value = _value;
}

std::string Number::toString() const {
    return std::to_string(value);
}

