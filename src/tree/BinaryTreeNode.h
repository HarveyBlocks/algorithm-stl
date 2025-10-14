/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/21
 *
 */
#ifndef ALGORITHM_TREE_NODE_H
#define ALGORITHM_TREE_NODE_H

#include "../lang/exception/IllegalStateException.h"

template<class T>
class BinaryTreeNode {
private:
    T *value;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;
protected:
    BinaryTreeNode() : value(nullptr), left(nullptr), right(nullptr) {}

public:
    explicit BinaryTreeNode(const T &value);

    T *getValue() const;

    void setValue(T *value);

    BinaryTreeNode<T> *getLeft() const;

    void setLeftRemoveOld(BinaryTreeNode<T> *left);

    BinaryTreeNode<T> *getRight() const;

    void setRightRemoveOld(BinaryTreeNode<T> *right);

    virtual void setRight(BinaryTreeNode<T> *right);

    virtual void setLeft(BinaryTreeNode<T> *left);
    /**
     * 只比值, 不比左右子树
     */
    int compareTo(const BinaryTreeNode<T> *node) const;

    int compareTo(const T &value) const;

    virtual ~BinaryTreeNode();

    friend std::ostream &operator<<(std::ostream &os, const BinaryTreeNode<T> &obj) {
        return os << *(obj.value);
    }
};



#include "impl/BinaryTreeNode_impl.h"

#endif //ALGORITHM_TREE_NODE_H
