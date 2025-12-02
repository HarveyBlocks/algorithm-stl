//
// Created by Lenovo on 2025/12/2.
//

#ifndef ALGORITHM_B_TREE_DECLARE_H
#define ALGORITHM_B_TREE_DECLARE_H

#include "../util/Comparator.h"
#include "../container/sequence/Stack.h"
#include "../container/associative/Entry.h"

template<typename T, typename Cmp = Greater<int>>
class BTree;

template<typename T, typename Cmp = Greater<int>>
class BTreeNode;

template<typename T, typename Cmp>
using BTreeTraceElement = Entry<BTreeNode<T, Cmp> *, int>;

template<typename T, typename Cmp>
using BTreeTrace = Stack<BTreeTraceElement<T, Cmp>>;

template<typename T, typename Cmp>
class BTree {
private:
    BTreeNode<T, Cmp> *root;
    // n 级 B 树...
    int level;
    Cmp cmp;

    friend class BTreeNode<T, Cmp>;

public:
    explicit BTree(int level, Cmp cmp = Cmp());

    ~BTree();

    void clear();

    void clear(BTreeNode<T, Cmp> *node);

    [[nodiscard]] BTreeTrace<T, Cmp> search(const T &value) const;

    void insert(const T &data);

#ifdef DEBUG

    void showBTree() const;

#endif
private:
    [[nodiscard]] BTreeNode<T, Cmp> *instanceNode() const;

    void insert(const T &data, BTreeTrace<T, Cmp> &trace);
};

template<typename T, typename Cmp>
class BTreeNode {
private:
    int size;
    /**
     * 数组, 本节点上的, 长度及level有关
     */
    T **datas;
    BTreeNode<T, Cmp> **children;

    friend class BTree<T, Cmp>;

    explicit BTreeNode(int level);

    ~BTreeNode();

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

    [[nodiscard]] BTreeNode<T, Cmp> *childAt(int index) const;

    [[nodiscard]] bool full(int level) const;

    [[nodiscard]] bool empty() const;

    /**
     * @return 对data进行new拷贝构造
     */
    bool insert(int index, T *data, int level,
                BTreeNode<T, Cmp> *left,
                BTreeNode<T, Cmp> *right);

    /**
     * @return 增加后转移到返回值, 自己清空
     */
    BTreeNode<T, Cmp> plus(int index, T *data,
                           BTreeNode<T, Cmp> *left,
                           BTreeNode<T, Cmp> *right) const;

    void reset();

    /**
     * 本节点是full后的temp
     * @return 返回防裂后的right
     */
    void split(T *&mid, BTreeNode<T, Cmp> *left, BTreeNode<T, Cmp> *right) const;


    T *resetData(int index, const T &value);

public :
    [[nodiscard]] T *dataAt(int index) const;

#ifdef DEBUG

    void showBTree(int level) const;

#endif
};

#include "impl/BTree_impl.h"
#include "impl/BTreeNode_impl.h"


#endif //ALGORITHM_B_TREE_DECLARE_H
