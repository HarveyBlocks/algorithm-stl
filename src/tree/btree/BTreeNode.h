//
// Created by Lenovo on 2025/12/5.
//

#ifndef ALGORITHM_B_TREE_NODE_H
#define ALGORITHM_B_TREE_NODE_H

#include "BTreeDeclarations.h"

#ifdef DEBUG

#include <iostream>

#endif

namespace harvey::algorithm::tree::btree {

    template<typename T, typename Cmp>
    class BTreeNode {
    private:
        int size;
        /**
         * 数组, 本节点上的, 长度及level有关
         */
        BTreeData<T> *datas;
        BTreeNodeReference<T, Cmp> *children;

        friend class BTreeElement<T, Cmp>;


        /**
         * @return 对data进行new拷贝构造
         */
        bool insert(int index, int level, const InsertGroup<T, Cmp> &insertGroup);

        /**
         * @return 增加后转移到返回值, 自己清空
         */
        BTreeNode<T, Cmp> plus(int index, const InsertGroup<T, Cmp> &insertGroup) const;


        void removeFirst();

        void insertFirst(const BTreeData<T> &data, const BTreeNodeReference<T, Cmp> &firstChild);

    public:

        [[nodiscard]] bool leaf() const;

        explicit BTreeNode(int level);

        ~BTreeNode();


        [[nodiscard]] bool full(int level) const;

        [[nodiscard]] bool empty() const;

        /**
         * @param value target
         * @param level BTree::level
         * @return positive for find, negative for not found;<br>
         *      -1 for value is before index 0
         *      -2 for value is between index (0,1)
         *      -3 for value is between index (1,2)
         *      ...
         *      -n for value is between index (n-2,n-1)
         *      -n-1 for value is between index (n-1,n)
         */
        int search(const T &value, const BTree<T, Cmp> *belong) const;

        [[nodiscard]] BTreeData<T> dataAt(int index) const;

        [[nodiscard]] BTreeNodeReference<T, Cmp> childAt(int index) const;

        BTreeData<T> setData(int index, const BTreeData<T> &data);

        BTreeNodeReference<T, Cmp> setChild(int index, const BTreeNodeReference<T, Cmp> &child);

        /**
         * @return 被填充的节点数量
         */
        inline int filledCount();

        void reset();

        void resize(int newSize);

        void resetChild(int index);

        /**
         * 本节点是full后的temp
         * @return 返回防裂后的right
         */
        void split(InsertGroup<T, Cmp> &insertGroup) const;

#ifdef DEBUG

        void showBTree(int level, std::ostream &os = std::cout) const;

#endif
    };



}

#include "impl/BTreeNode_impl.h"


#endif //ALGORITHM_B_TREE_NODE_H
