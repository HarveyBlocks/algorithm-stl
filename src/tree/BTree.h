//
// Created by Lenovo on 2025/12/2.
//

#ifndef ALGORITHM_B_TREE_DECLARE_H
#define ALGORITHM_B_TREE_DECLARE_H

#include "../util/Comparator.h"
#include "../container/sequence/Stack.h"

#ifdef DEBUG

#include <iostream>

#endif

template<typename T, typename Cmp = Greater<T>>
class BTree;

template<typename T, typename Cmp = Greater<T>>
class BTreeNode;

/**
 * 或指向某个node的child, 或指向某个node的data
 */
template<typename T, typename Cmp = Greater<T>>
struct BTreeElement;


template<typename T, typename Cmp = Greater<T>>
using BTreeTrace = Stack<BTreeElement<T, Cmp>>;

template<typename T, typename Cmp>
struct BTreeElement {
    BTreeNode<T, Cmp> *node;
    /**
     * minus for node->children[-index-1]
     * else for node->data[index]
     */
    int index;

    BTreeElement(BTreeNode<T, Cmp> *node, int index);

    /**
     * 当前元素的前驱push到stack里去, 当前元素不包含
     * @param stack 栈顶指向当前节点
     */
    void pushPrevious(BTreeTrace<T, Cmp> &stack) const;

    BTreeElement<T, Cmp> &operator=(const BTreeElement<T, Cmp> &src);

    T *&data();

    BTreeNode<T, Cmp> *&child() const;;

    /**
     * 整理, 一般是没用的, 因为由于之间的操作, index=node->size, 除非删除的就是叶子
     */
    void tidyLeaf();

    /**
     * this 作为 parent
     * right 的最左放入 parent[parentIndex]
     * parent[parentIndex] 放入 cur 的最右
     */
    void moveFromRightBrother(BTreeNode<T, Cmp> *cur, BTreeNode<T, Cmp> *right);

    /**
     * this 作为 parent
     * left 的最右放入 parent[parentIndex]
     * parent[parentIndex] 放入 cur 的最左
     */
    void moveFromLeftBrother(BTreeNode<T, Cmp> *cur, BTreeNode<T, Cmp> *left);


    void combine(int level);
};

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

    // remove, 是删除一个, 还是删除多个? 依据trace去删除, 倒是可以
    void remove(BTreeTrace<T, Cmp> &trace);

    bool empty() {
        return root->empty();
    }

#ifdef DEBUG

    /**
     * @deprecated
     */
    double calRate() const;

    void showBTree(std::ostream &os) const;

#endif


private:
    [[nodiscard]] BTreeNode<T, Cmp> *instanceNode() const;

    /**
     * @param trace 其index总是指向child_index
     */
    void insert(const T &data, BTreeTrace<T, Cmp> &trace);


    /**
     * @param parent 为了防止对外界的改变, 因此采用复制
     */
    bool tryMoveFromBrother(BTreeNode<T, Cmp> *cur, BTreeElement<T, Cmp> parent, int lowerBound);

    void removeLeaf(BTreeTrace<T, Cmp> &trace, BTreeNode<T, Cmp> *pNode);
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

    friend class BTreeElement<T, Cmp>;

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

    [[nodiscard]] bool leaf() const;

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

    void removeFirst();

    void insertFirst(T *data, BTreeNode<T, Cmp> *firstChild);

public:
    [[nodiscard]] T *dataAt(int index) const;

#ifdef DEBUG

    void showBTree(int level, std::ostream &os) const;

#endif
};


#include "impl/BTreeElement_impl.h"
#include "impl/BTree_impl.h"
#include "impl/BTreeNode_impl.h"

#endif //ALGORITHM_B_TREE_DECLARE_H
