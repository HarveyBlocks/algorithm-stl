//
// Created by Lenovo on 2025/12/5.
//

#ifndef ALGORITHM_REFERENCE_H
#define ALGORITHM_REFERENCE_H

template<typename T>
class Reference {
protected:
    T *reference;
public:

    explicit Reference(const T *reference = nullptr) :
            reference(const_cast<T *>(reference)) {}


    void release() { // 完全代理reference的操作
        delete reference;
        reference = nullptr;
    }

    T *operator->() const {
        return reference;
    }

    T &operator*() const {
        return *reference;
    }

    bool operator==(const T *n) const {
        return this->reference == n;
    }

    bool operator!=(const T *n) const {
        return this->reference != n;
    }

    virtual Reference<T> &operator=(const T *ref) {
        this->reference = const_cast<T *>(ref);
        return *this;
    };

    Reference<T> &operator=(const Reference<T> &ref) {
        if (this != &ref) {
            this->reference = ref.reference;
        }
        return *this;
    };
};

#endif //ALGORITHM_REFERENCE_H
