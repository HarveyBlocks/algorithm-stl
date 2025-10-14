/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/9/2
 *
 */
#ifndef ALGORITHM_MATH_COMPARABLE_H
#define ALGORITHM_MATH_COMPARABLE_H


#include "../lang/Comparable.h"
#include "commons.h"

template<class T>
class MathComparable : public StrictComparable<const T&> {
public:
    virtual T instance(const math::number &value) const = 0;

    bool operator>(const T& calculator) const override {
        return StrictComparable<const T&>::operator>(calculator);
    }

    bool operator<(const T& calculator) const override {
        return StrictComparable<const T&>::operator<(calculator);
    }

    bool operator==(const T& calculator) const override {
        return StrictComparable<const T&>::operator==(calculator);
    }

    bool operator!=(const T& calculator) const override {
        return StrictComparable<const T&>::operator!=(calculator);
    }

    bool operator>=(const T& calculator) const override {
        return StrictComparable<const T&>::operator>=(calculator);
    }

    bool operator<=(const T& calculator) const override {
        return StrictComparable<const T&>::operator<=(calculator);
    }

    virtual bool operator>(const math::number &value) const {
        return StrictComparable<const T&>::operator>(instance(value));
    }

    virtual bool operator<(const math::number &value) const {
        return StrictComparable<const T&>::operator<(instance(value));
    }

    virtual bool operator==(const math::number &value) const {
        return StrictComparable<const T&>::operator==(instance(value));
    }

    virtual bool operator!=(const math::number &value) const {
        return StrictComparable<const T&>::operator!=(instance(value));
    }

    virtual bool operator>=(const math::number &value) const {
        return StrictComparable<const T&>::operator>=(instance(value));
    }

    virtual bool operator<=(const math::number &value) const {
        return StrictComparable<const T&>::operator<=(instance(value));
    }
};


#endif //ALGORITHM_MATH_COMPARABLE_H
