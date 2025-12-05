//
// Created by Lenovo on 2025/12/2.
//

#ifndef ALGORITHM_B_TREE_H
#define ALGORITHM_B_TREE_H

#include "InsertGroup.h"
#include "BTreeReference.h"
#include "BTreeNode.h"
#include "BTreeElement.h"
#include "BTreeDeclarations.h"

#ifdef DEBUG

#include <iostream>

#endif

namespace harvey::algorithm::tree::btree {
    template<typename T, typename Cmp>
    class BTree {
    private:
        BTreeNodeReference<T, Cmp> root;
        // n 级 B 树...
        int level;
        Cmp cmp;

        friend class BTreeNode<T, Cmp>;

    public:
        explicit BTree(int level, const Cmp &cmp = Cmp());

        ~BTree();

        void clear();


        [[nodiscard]] BTreeTrace<T, Cmp> search(const T &value) const;

        void insert(const T &data);

        // remove, 是删除一个, 还是删除多个? 依据trace去删除, 倒是可以
        void remove(BTreeTrace<T, Cmp> &trace);

        bool empty();

#ifdef DEBUG

        double calRate() const;

        void showBTree(std::ostream &os = std::cout) const;

#endif


    private:
        [[nodiscard]] BTreeNodeReference<T, Cmp> instanceNode() const;

        /**
         * @param trace 其index总是指向child_index
         */
        void insertLeaf(const T &data, BTreeTrace<T, Cmp> &trace);


        void removeLeaf(BTreeTrace<T, Cmp> &trace, BTreeNodeReference<T, Cmp> cur);
    };
}

#include "impl/BTree_impl.h"

#endif //ALGORITHM_B_TREE_H
