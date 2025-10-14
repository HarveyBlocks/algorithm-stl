#ifndef ALGORITHM_ARRAY_IMPL_H
#define ALGORITHM_ARRAY_IMPL_H

#include "Array.h"


template<class T>
Array<T>::Array(const T *arr, int len) :
        arr(new T[len]), len(len) {
    // 深拷贝
    Array<T>::copy(arr, this->arr, len);
}

template<class T>
Array<T>::Array() : arr(nullptr), len(0) {
}

template<class T>
Array<T>::Array(const Array &array) : Array(array.arr, array.len) {
}

template<class T>
Array<T>::~Array() {
    delete[] this->arr;
}

template<class T>
int Array<T>::clone(Array<T> &target) const {
    return Array<T>::copy(*this, target);
}

template<class T>
int Array<T>::copy(const Array<T> &src, Array<T> &target) {
    int len = src.len;
    if (len > target.len) {
        len = target.len;
    }
    return Array<T>::copy(src.arr, target.arr, len);
}

template<class T>
int Array<T>::copy(const Array<T> *src, Array<T> *target) {
    int len = src->len;
    if (len > target->len) {
        len = target->len;
    }
    return Array<T>::copy(src->arr, target->arr, len);
}

template<class T>
int Array<T>::copy(const T *src, T *target, int len) {
    for (int i = 0; i < len; ++i) {
        target[i] = src[i];
    }
    return len;
}

template<class T>
void Array<T>::elementSwap(int index1, int index2) {
    if (index1 == index2 || (*this)[index1] == (*this)[index2]) {
        return;
    }
    T temp = this->operator[](index1);
    this->operator[](index1) = this->operator[](index2);
    this->operator[](index2) = temp;
}

template<class T>
int Array<T>::getSize() const {
    return len;
}

template<class T>
T &Array<T>::operator[](int index) const {
    if (index >= len || index < 0) {
        throw IndexOutOfBoundException(std::to_string(index));
    }
    return arr[index];
}

template<class T>
T *Array<T>::operator+(int offset) const {
    return arr + offset;
}

template<class T>
void Array<T>::maxAndMin() const {
    if (len <= 0) {
        return;
    }
    int end = len;
    T max;
    T min;
    if (len % 2) {
        max = this->operator[](len - 1);
        min = this->operator[](len - 1);
        end--;
    } else {
        T ele1 = this->operator[](len - 1);
        T ele2 = this->operator[](len - 2);
        if (ele1 > ele2) {
            max = ele1;
            min = ele2;
        } else {
            max = ele2;
            min = ele1;
        }
        end -= 2;
    }
    end = end / 2 - 1;
    for (int i = 0; i < end; ++i) {
        int ele1 = this->operator[](i * 2);
        int ele2 = this->operator[](i * 2 + 1);
        if (ele1 > ele2) {
            if (ele1 > max) {
                max = ele1;
            }
            if (ele2 < min) {
                min = ele2;
            }
        } else {
            if (ele2 > max) {
                max = ele2;
            }
            if (ele1 < min) {
                min = ele1;
            }
        }
    }
}


template<class T>
std::ostream &operator<<(std::ostream &os, const Array<T> &obj) {
    /*os << "[";
    for (int i = 0; i < obj.getSize() - 1; ++i) {
        os << obj[i] << ", ";
    }
    if (obj.getSize() > 0) {
        os << obj[obj.getSize() - 1];
    }
    return os << "]";*/
    int size = obj.getSize();
    os << size << sizeof(T);
    for (int i = 0; i < size; ++i) {
        os << obj[i];
    }
    return os;
}

template<class T>
Array<T>::operator std::string() const {
    std::stringstream ss;
    ss << "[";
    for (int i = 0; i < this->getSize() - 1; ++i) {
        // os << this->operator[](i) << ", ";
        ss << (std::string) this->operator[](i) << ", ";
    }
    if (this->getSize() > 0) {
        /*os << */
        ss << (std::string) this->operator[](this->getSize() - 1);
    }
    ss << "]";
    return ss.str();
}

template<class T>
Array<T> Array<T>::subArray(int start) {
    return subArray(start, this->len);
}

template<class T>
Array<T> Array<T>::subArray(int start, int end, int step) {
    if (step == 0 || start < 0 || (start < end && step < 0) || (start > end && step > 0)) {
        throw IllegalArgumentException();
    }

    Array<T> result(abs(end - start));
    if (step > 0) {
        for (int i = start, j = 0; i < end; i += step,j++) {
            result[j] = this->operator[](i);
        }
    } else {
        for (int i = start; i > end; i += step) {
            result[i] = this->operator[](i);
        }
    }
    return result;
}

template<class T>
Array<T>::Array(const int allocate, const T &initValue):Array(allocate) {
    for (int i = 0; i < len; ++i) {
        arr[i] = initValue;
    }
}

template<class T>
Array<T>::Array(const int allocate) :len(allocate), arr(new T[allocate]) {
}


#endif //ALGORITHM_ARRAY_IMPL_H
