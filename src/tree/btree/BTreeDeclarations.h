//
// Created by Lenovo on 2025/12/5.
//

#ifndef ALGORITHM_B_TREE_DECLARATIONS_H
#define ALGORITHM_B_TREE_DECLARATIONS_H

#include "../../util/Comparator.h"
#include "../../util/Reference.h"
#include "../../container/sequence/Stack.h"

namespace harvey::algorithm::tree::btree {

    template<typename T, typename Cmp = Greater<T>>
    class BTree;

    template<typename T, typename Cmp = Greater<T>>
    class BTreeNode;

    template<typename T, typename Cmp = Greater<T>>
    class BTreeNodeReference;

    template<typename T>
    using BTreeData = Reference<T>;

    /**
     * 或指向某个node的child, 或指向某个node的data
     */
    template<typename T, typename Cmp = Greater<T>>
    struct BTreeElement;

    template<typename T, typename Cmp = Greater<T>>
    using BTreeTrace = Stack<BTreeElement<T, Cmp>>;

    template<typename T, typename Cmp= Greater<T>>
    struct InsertGroup;
}

#endif //ALGORITHM_B_TREE_DECLARATIONS_H
