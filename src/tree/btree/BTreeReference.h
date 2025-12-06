//
// Created by Lenovo on 2025/12/5.
//

#ifndef ALGORITHM_B_TREE_REFERENCE_H
#define ALGORITHM_B_TREE_REFERENCE_H

#include "BTreeDeclarations.h"

namespace harvey::algorithm::tree::btree {
    template<typename T, typename Cmp>
    class BTreeNodeReference : public ReferenceImpl<BTreeNode<T, Cmp>> {
    public:
        explicit BTreeNodeReference(const BTreeNode<T, Cmp> *reference = nullptr) :
                ReferenceImpl<BTreeNode<T, Cmp>>(reference) {}

        bool operator==(const BTreeNode<T, Cmp> *n) const override {
            return ReferenceImpl<BTreeNode<T, Cmp>>::operator==(n);
        }

        bool operator!=(const BTreeNode<T, Cmp> *n) const override {
            return ReferenceImpl<BTreeNode<T, Cmp>>::operator!=(n);
        }

        bool operator==(const BTreeNodeReference<T> n) const {
            return this->reference == n.reference;
        }

        bool operator!=(const BTreeNodeReference<T> n) const {
            return this->reference != n.reference;
        }

        BTreeNodeReference<T, Cmp> &operator=(const BTreeNode<T, Cmp> *ref) override;

        BTreeNodeReference<T, Cmp> &operator=(const BTreeNodeReference<T, Cmp> &src);
    };

}

#include "impl/BTreeReference_impl.h"

#endif //ALGORITHM_B_TREE_REFERENCE_H
