/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/24
 *
 */
#ifndef ALGORITHM_ARRAY_LIST_IMPL_H
#define ALGORITHM_ARRAY_LIST_IMPL_H

#include "../ArrayList.h"

template<class T>
bool ArrayList<T>::grow0(int newCapacity) {
    if (this->array->getSize() > newCapacity) {
        return false;
    }
    auto *newArray = new Array<T>(newCapacity);
    array->clone(*newArray);
    delete array;
    array = newArray;
    capacity = newCapacity;
    return true;
}

template<class T>
bool ArrayList<T>::grow(int addNum) {
    if (addNum < 0) {
        throw IllegalArgumentException();
    }
    if (((unsigned) size + addNum) > ((unsigned) CAPACITY_MAX)) {
        return false;
    }
    if (capacity >= CAPACITY_MAX) {
        // 到上限了, 不能再涨了
        return false;
    }
    if ((size + addNum) < (capacity >> 1) + (capacity >> 2)) {
        // size每到达capacity的3/4的时候还不可以增长
        // capacity还够, 别涨了
        return true;
    }
    int newCapacity = capacity + (capacity >> 1);
    // 涨1.5倍
    while (newCapacity < size + addNum) {
        newCapacity = newCapacity + (newCapacity >> 1);
    } // 防止触发下一次的增长
    return grow0(newCapacity >= CAPACITY_MAX ? CAPACITY_MAX : newCapacity);
}

template<class T>
void ArrayList<T>::shrink0(int newCapacity) {
    auto *newArray = new Array<T>(newCapacity);
    array->clone(*newArray);
    delete array;
    array = newArray;
    capacity = newCapacity;
}

template<class T>
void ArrayList<T>::shrink() {
    if (capacity <= DEFAULT_INIT_CAPACITY) {
        // 到下限了, 不能再收缩了
        return;
    }
    if (size > (capacity >> 2)) {
        // size没小于capacity的1/4的时候还不可以收缩
        // capacity还不够, 别缩了
        return;
    }
    int newCapacity = capacity >> 1;
    while (size > (capacity >> 2)) {
        newCapacity = newCapacity >> 1; // 缩为原来的1/2
    }
    // 如果会触发
    shrink0(newCapacity <= DEFAULT_INIT_CAPACITY ? DEFAULT_INIT_CAPACITY : newCapacity);
}

template<class T>
ArrayList<T>::ArrayList(int allocate) {
    if (allocate > CAPACITY_MAX) {
        throw OverflowException("capacity = " + std::to_string(capacity));
    }
    array = new Array<T>(allocate);
    capacity = allocate;
    size = 0;
}

template<class T>
Array<T> ArrayList<T>::getArray() const {
    Array<T> result(size);
    this->array->clone(result);
    return result;
}

template<class T>
int ArrayList<T>::getSize() const {
    return size;
}

template<class T>
int ArrayList<T>::getCapacity() const {
    return capacity;
}

template<class T>
bool ArrayList<T>::empty() const {
    return size == 0 || array == nullptr;
}

template<class T>
T *ArrayList<T>::operator+(const int offset) const {
    return *array + offset;
}

template<class T>
T &ArrayList<T>::operator[](const int index) const {
    if (index > size) {
        throw IndexOutOfBoundException();
    }
    return (*array)[index];
}

template<class T>
ArrayList<T> &ArrayList<T>::update(const int index, const T &element) {
    this->operator[](index) = element;
    return *(this);
}

template<class T>
ArrayList<T> &ArrayList<T>::insert(const int index, const T &element) {
    if (index < 0 || index > size) {
        throw IndexOutOfBoundException();
    }
    if (!grow(1)) {
        // 增长失败了?
        throw OverflowException("capacity = " + std::to_string(capacity));
    }
    size++;
    for (int i = size - 1; i > index; --i) {
        this->operator[](i) = this->operator[](i - 1);
    }
    this->operator[](index) = element;
    return *(this);
}

template<class T>
ArrayList<T> &ArrayList<T>::add(const T &element) {
    if (!grow(1)) {
        // 增长失败了?
        throw OverflowException("capacity = " + std::to_string(capacity));
    }
    (*array)[size] = element;
    size++;
    return *(this);
}

template<class T>
ArrayList<T> &ArrayList<T>::concat(const ArrayList<T> &list) {
    return concat(list.getArray());
}

template<class T>
ArrayList<T> &ArrayList<T>::concat(const Array<T> &_array) {
    if (!grow(_array.getSize())) {
        // 增长失败了?
        throw OverflowException("capacity = " + std::to_string(capacity));
    }
    for (int i = 0; i < _array.getSize(); ++i) {
        (*array)[size++] = _array[i];
    }
    return *(this);
}

template<class T>
ArrayList<T> &ArrayList<T>::removeLast() {
    --size;
    shrink();
    return *(this);
}

template<class T>
ArrayList<T> &ArrayList<T>::remove(const int index) {
    if (index < 0 || index >= size) {
        throw IndexOutOfBoundException();
    }
    size--;
    for (int i = index; i + 1 < size; ++i) {
        this->operator[](i) = this->operator[](i + 1);
    }
    shrink();
    return *(this);
}

template<class T>
ArrayList<T> &ArrayList<T>::removeElement(const T &element) {
    int j = 0;
    for (int i = 0; i < size; ++i) {
        if (this->operator[](i) != element) {
            this->operator[](j) = this->operator[](i);
            j++;
        }
    }
    size = j;
    shrink();
    return *(this);
}

template<class T>
void ArrayList<T>::clear() {
    delete array;
    size = 0;
    capacity = DEFAULT_INIT_CAPACITY;
    this->array = new Array<T>(capacity);
}

template<class T>
void ArrayList<T>::shrinkArray() {
    shrink();
}

template<class T>
ArrayList<T>::~ArrayList() {
    delete array;
}

#endif //ALGORITHM_ARRAYLIST_IMPL_H
