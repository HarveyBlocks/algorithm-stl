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

template<typename T, typename Cmp= Greater<T>>
struct InsertGroup {
    T *data;
    BTreeNode<T, Cmp> *left;
    BTreeNode<T, Cmp> *right;

    explicit InsertGroup(T *data) : data(data), left(nullptr), right(nullptr) {}
};

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
     * 当前元素的前驱push到stack里去, 当前元素不包含 <br>
     * @param stack 栈顶指向当前节点 <br>
     */
    void pushPrevious(BTreeTrace<T, Cmp> &stack) const;

    BTreeElement<T, Cmp> &operator=(const BTreeElement<T, Cmp> &src);

    T *&data();

    BTreeNode<T, Cmp> *&child() const;;

    /**
     * 整理, 一般是没用的, 因为由于之间的操作, index=node->size, 除非删除的就是叶子 <br>
     */
    void tidyLeaf();

    /**
     * @param parent 为了防止对外界的改变, 因此采用复制, 此时parent.child()==cur <br>
     * @param lowerBound =(level-1)>>1 <br>
     */
    bool tryMoveFromBrother(BTreeNode<T, Cmp> *cur, int lowerBound) const;


    /**
     * this 作为 parent <br>
     * right 的最左放入 parent[parentIndex] <br>
     * parent[parentIndex] 放入 cur 的最右 <br>
     */
    void moveFromRightBrother(BTreeNode<T, Cmp> *cur, BTreeNode<T, Cmp> *right);

    /**
     * this 作为 parent <br>
     * left 的最右放入 parent[parentIndex] <br>
     * parent[parentIndex] 放入 cur 的最左 <br>
     */
    void moveFromLeftBrother(BTreeNode<T, Cmp> *cur, BTreeNode<T, Cmp> *left);


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
            BTreeNode<T, Cmp> *right,
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
            BTreeNode<T, Cmp> *left,
            const InsertGroup<T, Cmp> &insertGroup);

    void leftMoveInsert(const InsertGroup<T, Cmp> &insertGroup);

    void rightMoveInsert(const InsertGroup<T, Cmp> &insertGroup);
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


    [[nodiscard]] BTreeTrace<T, Cmp> search(const T &value) const;

    void insert(const T &data);

    // remove, 是删除一个, 还是删除多个? 依据trace去删除, 倒是可以
    void remove(BTreeTrace<T, Cmp> &trace);

    bool empty();

#ifdef DEBUG

    /**
     * @deprecated
     */
    double calRate() const;

    void showBTree(std::ostream &os = std::cout) const;

#endif


private:
    [[nodiscard]] BTreeNode<T, Cmp> *instanceNode() const;

    /**
     * @param trace 其index总是指向child_index
     */
    void insertLeaf(const T &data, BTreeTrace<T, Cmp> &trace);


    void removeLeaf(BTreeTrace<T, Cmp> &trace, BTreeNode<T, Cmp> *cur);
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

    // friend class BTree<T, Cmp>;

    friend class BTreeElement<T, Cmp>;


    [[nodiscard]] bool empty() const;

    [[nodiscard]] bool leaf() const;

    /**
     * @return 对data进行new拷贝构造
     */
    bool insert(int index, int level,
                const InsertGroup<T, Cmp> &insertGroup);

    /**
     * @return 增加后转移到返回值, 自己清空
     */
    BTreeNode<T, Cmp> plus(int index, const InsertGroup<T, Cmp> &insertGroup) const;


    T *resetData(int index, const T &value);


    void removeFirst();

    void insertFirst(T *data, BTreeNode<T, Cmp> *firstChild);

public:

    explicit BTreeNode(int level);

    ~BTreeNode();


    [[nodiscard]] bool full(int level) const;

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

    [[nodiscard]] T *dataAt(int index) const;

    [[nodiscard]] BTreeNode<T, Cmp> *childAt(int index) const;

    /**
     * @return 被填充的节点数量
     */
    inline int filledCount();

    void reset();

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


#include "impl/BTreeElement_impl.h"
#include "impl/BTree_impl.h"
#include "impl/BTreeNode_impl.h"

#endif //ALGORITHM_B_TREE_DECLARE_H
