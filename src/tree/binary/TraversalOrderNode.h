/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/11/14
 *
 */
#ifndef ALGORITHM_TRAVERSAL_ORDER_NODE_H
#define ALGORITHM_TRAVERSAL_ORDER_NODE_H

// 双分支
template<class T>
class DoubleBranchedNode {
private:
    DoubleBranchedNode<T> *left;
    DoubleBranchedNode<T> *right;
protected:
    DoubleBranchedNode() : left(nullptr), right(nullptr) {}

public:

    DoubleBranchedNode<T> *getLeft() const;

    DoubleBranchedNode<T> *getRight() const;

    virtual void setRight(DoubleBranchedNode<T> *right);

    virtual void setLeft(DoubleBranchedNode<T> *left);

    void setLeftRemoveOld(DoubleBranchedNode<T> *left);

    void setRightRemoveOld(DoubleBranchedNode<T> *right);

    int compareTo(const DoubleBranchedNode<T> *node) const;
};

#include "impl/TraversalOrderNode_impl.h"

#endif //ALGORITHM_TRAVERSAL_ORDER_NODE_H
