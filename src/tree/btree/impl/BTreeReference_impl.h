//
// Created by Lenovo on 2025/12/5.
//

#ifndef ALGORITHM_B_TREE_REFERENCE_IMPL_H
#define ALGORITHM_B_TREE_REFERENCE_IMPL_H

#include "../BTreeReference.h"

namespace harvey::algorithm::tree::btree {

    template<typename T, typename Cmp>
    BTreeNodeReference<T, Cmp> &BTreeNodeReference<T, Cmp>::operator=(const BTreeNodeReference<T, Cmp> &src) {
        if (this != &src) {
            this->reference = src.reference;
        }
        return *this;
    }

    template<typename T, typename Cmp>
    BTreeNodeReference<T, Cmp> &BTreeNodeReference<T, Cmp>::operator=(const BTreeNode<T, Cmp> *ref) {
        this->ReferenceImpl<BTreeNode<T, Cmp>>::operator=(ref);
        return *this;
    }

}
#endif //ALGORITHM_B_TREE_REFERENCE_IMPL_H
