//
// Created by Lenovo on 2025/12/6.
//

#ifndef ALGORITHM_B_TREE_DATA_H
#define ALGORITHM_B_TREE_DATA_H

#include "BTreeDeclarations.h"

namespace harvey::algorithm::tree::btree {
    template<typename T>
    class BTreeData {
        ReferenceImpl<T> reference;
    public:
        explicit BTreeData(const T *reference = nullptr) : reference(reference) {}

        explicit BTreeData(const T &data) : reference(new T(data)) {}

        void release() { reference.release(); }

        T *operator->() const { return reference.operator->(); }

        T &operator*() const { return reference.operator*(); }

        bool operator==(const T *n) const { return reference.operator==(n); }

        bool operator!=(const T *n) const { return reference.operator!=(n); }

        BTreeData<T> &operator=(const T *ref) {
            reference.operator=(ref);
            return *this;
        }

        BTreeData<T> &operator=(const BTreeData<T> &src) {
            if (this != &src) {
                this->reference = src.reference;
            }
            return *this;
        }
    };
}

#endif //ALGORITHM_B_TREE_DATA_H
