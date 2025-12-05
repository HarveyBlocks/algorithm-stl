//
// Created by Lenovo on 2025/12/5.
//

#ifndef ALGORITHM_B_TREE_ELEMENT_H
#define ALGORITHM_B_TREE_ELEMENT_H

#include "BTreeDeclarations.h"

namespace harvey::algorithm::tree::btree {

    template<typename T, typename Cmp>
    struct BTreeElement {
        BTreeNodeReference<T, Cmp> node;
        /**
         * minus for node->children[-index-1]
         * else for node->data[index]
         */
        int index;

        BTreeElement(BTreeNodeReference<T, Cmp> node, int index);

        /**
         * 当前元素的前驱push到stack里去, 当前元素不包含 <br>
         * @param stack 栈顶指向当前节点 <br>
         */
        void pushPrevious(BTreeTrace<T, Cmp> &stack) const;

        BTreeElement<T, Cmp> &operator=(const BTreeElement<T, Cmp> &src);

        BTreeData<T> &data();

        BTreeNodeReference<T, Cmp> &child() const;;

        /**
         * 整理, 一般是没用的, 因为由于之间的操作, index=node->size, 除非删除的就是叶子 <br>
         */
        void tidyLeaf();

        /**
         * @param parent 为了防止对外界的改变, 因此采用复制, 此时parent.child()==cur <br>
         * @param lowerBound =(level-1)>>1 <br>
         */
        bool tryMoveFromBrother(BTreeNodeReference<T, Cmp> cur, int lowerBound) const;


        /**
         * this 作为 parent <br>
         * right 的最左放入 parent[parentIndex] <br>
         * parent[parentIndex] 放入 cur 的最右 <br>
         */
        void moveFromRightBrother(BTreeNodeReference<T, Cmp> cur, BTreeNodeReference<T, Cmp> right);

        /**
         * this 作为 parent <br>
         * left 的最右放入 parent[parentIndex] <br>
         * parent[parentIndex] 放入 cur 的最左 <br>
         */
        void moveFromLeftBrother(BTreeNodeReference<T, Cmp> cur, BTreeNodeReference<T, Cmp> left);


        void combine(int level);

        void insert(int level, const InsertGroup<T, Cmp> &insertGroup);

        BTreeNode<T, Cmp> plus(const InsertGroup<T, Cmp> &insertGroup);

        /**
         * @param cur 为了防止对外界的改变, 因此采用复制, 此时this->child()==cur, cur->insert<br>
         * @param bound (level-1)>>1 for lower and level-1 for !lower <br>
         */
        bool tryMoveToBrother(
                const BTreeElement<T, Cmp> &cur, int upperBound,
                const InsertGroup<T, Cmp> &insertGroup) const;

        /**
         * this 作为 parent, 且指向data <br>
         * data 放入 cur, 同时右溢出 <br>
         * cur 的右溢出放入 parent[parentIndex] <br>
         * parent[parentIndex] 放入 right 的最左 <br>
         * @param cur拷贝一份
         */
        void moveToRightBrother(
                BTreeElement<T, Cmp> cur,
                BTreeNodeReference<T, Cmp> right,
                const InsertGroup<T, Cmp> &insertGroup);

        /**
         * this 作为 parent, 且指向data <br>
         * data 放入 cur, 同时左溢出 <br>
         * cur 的左溢出放入 parent[parentIndex] <br>
         * parent[parentIndex] 放入 left 的最右 <br>
         * @param cur拷贝一份
         */
        void moveToLeftBrother(
                BTreeElement<T, Cmp> cur,
                BTreeNodeReference<T, Cmp> left,
                const InsertGroup<T, Cmp> &insertGroup);

        void leftMoveInsert(const InsertGroup<T, Cmp> &insertGroup);

        void rightMoveInsert(const InsertGroup<T, Cmp> &insertGroup);
    };

}

#include "impl/BTreeElement_impl.h"

#endif //ALGORITHM_B_TREE_ELEMENT_H
