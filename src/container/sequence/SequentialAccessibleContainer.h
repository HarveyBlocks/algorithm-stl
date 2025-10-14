/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/22
 *
 */
#ifndef ALGORITHM_SEQUENTIAL_ACCESSIBLE_CONTAINER_H
#define ALGORITHM_SEQUENTIAL_ACCESSIBLE_CONTAINER_H


#include "../Container.h"

template<class T>
class SequentialAccessibleContainer : public Container<T> {
public:
    T& at(int index) const{
        return this->operator[](index);
    }

    void set(int index, T value) {
        this->operator[](index) = value;
    }

    virtual T &operator[](int index) const = 0;

    virtual T *operator+(int offset) const = 0;

};


#endif //ALGORITHM_SEQUENTIAL_ACCESSIBLE_CONTAINER_H
