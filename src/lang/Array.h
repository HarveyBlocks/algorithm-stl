#ifndef ALGORITHM_ARRAY_H
#define ALGORITHM_ARRAY_H

#include "iostream"
#include "sstream"
#include "../container/sequence/SequentialAccessibleContainer.h"
#include "exception/IllegalArgumentException.h"
#include "exception/IndexOutOfBoundException.h"


/**
 * 只是对数组的封装
 */
template<class T>
class Array : public SequentialAccessibleContainer<T> {
private:
    T *arr;
    int len;

    Array();

public:

    [[nodiscard]] int getSize() const override;

    [[nodiscard]] bool empty() const override {
        return len == 0 || arr == nullptr;
    }

    Array(const Array &array);

    explicit Array(int allocate);

    Array(int allocate, const T &initValue);

    Array(const T *arr, int len);

    virtual ~Array();

    int clone(Array<T> &target) const;

    static int copy(const Array<T> &src, Array<T> &target);

    static int copy(const Array<T> *src, Array<T> *target);

    static int copy(const T *src, T *target, int len);

    void elementSwap(int index1, int index2);

    T &operator[](int index) const override;

    T *operator+(int offset) const override;

    void maxAndMin() const;

    Array<T> subArray(int start);

    Array<T> subArray(int start, int end, int step = 1);

    Array<T> concat(const Array<T> &array) const {
        return Array<T>::concat(*this, array);
    }

    static Array<T> &concat(const Array<T> &before, const Array<T> &after, Array<T> &target) {
        if (target.len < after.len + before.len) {
            throw IllegalArgumentException();
        }
        before.clone(target);
        for (int i = 0; i < after.len; ++i) {
            target[before.len + i] = after[i];
        }
        return target;
    }

    Array<T> reverse() const {
        Array<T> reverseArray(this->len);
        for (int i = 0; i < len; ++i) {
            reverseArray[len - i - 1] = this->operator[](i);
        }
        return reverseArray;
    }

    Array<T> &reverse() {
        return this->reverse(0, this->len - 1);
    }

    Array<T> &reverse(int startIndex, int endIndex) {
        for (int i = startIndex, j = endIndex; i < j; ++i, --j) {
            this->elementSwap(i, j);
        }
        return (*this);
    }

    explicit operator std::string() const;

    Array<T> &reset(T value) {
        for (int i = 0; i < len; ++i) {
            *(this->arr + i) = value;
        }
        return *this;
    }
};


template<class T>
std::ostream &operator<<(std::ostream &os, const Array<T> &obj);

#include "Array_impl.h"

#endif //ALGORITHM_ARRAY_H
