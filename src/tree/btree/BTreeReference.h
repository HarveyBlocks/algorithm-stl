//
// Created by Lenovo on 2025/12/5.
//

#ifndef ALGORITHM_B_TREE_REFERENCE_H
#define ALGORITHM_B_TREE_REFERENCE_H

#include "BTreeDeclarations.h"

namespace harvey::algorithm::tree::btree {
    template<typename T, typename Cmp>
    class BTreeNodeReference : public Reference<BTreeNode<T, Cmp>> {
    public:
        explicit BTreeNodeReference(const BTreeNode<T, Cmp> *reference = nullptr) :
                Reference<BTreeNode<T, Cmp>>(reference) {}

        BTreeNodeReference<T, Cmp> &operator=(const BTreeNode<T, Cmp> *ref) override;;

        BTreeNodeReference<T, Cmp> &operator=(const BTreeNodeReference<T, Cmp> &src);;
    };
}

#include "impl/BTreeReference_impl.h"

#endif //ALGORITHM_B_TREE_REFERENCE_H
