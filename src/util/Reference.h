//
// Created by Lenovo on 2025/12/5.
//

#ifndef ALGORITHM_REFERENCE_H
#define ALGORITHM_REFERENCE_H

template<typename T>
class Reference {
public:
    virtual void release() = 0;

    virtual T *operator->() const = 0;

    virtual T &operator*() const = 0;

    virtual bool operator==(const T *n) const = 0;

    virtual bool operator!=(const T *n) const = 0;

    virtual Reference<T> &operator=(const T *ref) = 0;
};

template<typename T>
class ReferenceImpl : public Reference<T> {
protected:
    T *reference;
public:

    explicit ReferenceImpl(const T *reference = nullptr) :
            reference(const_cast<T *>(reference)) {}


    void release() override { // 完全代理reference的操作
        delete reference;
        reference = nullptr;
    }

    T *operator->() const override {
        return reference;
    }

    T &operator*() const override {
        return *reference;
    }

    bool operator==(const T *n) const override {
        return this->reference == n;
    }

    bool operator!=(const T *n) const override {
        return this->reference != n;
    }

    ReferenceImpl<T> &operator=(const T *ref) override {
        this->reference = const_cast<T *>(ref);
        return *this;
    };

    ReferenceImpl<T> &operator=(const ReferenceImpl<T> &ref)  {
        if (this != &ref) {
            this->reference = ref.reference;
        }
        return *this;
    };
};

#endif //ALGORITHM_REFERENCE_H
