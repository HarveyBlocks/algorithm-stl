/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/11/14
 *
 */
#ifndef ALGORITHM_TRAVERSAL_ORDER_NODE_IMPL_H
#define ALGORITHM_TRAVERSAL_ORDER_NODE_IMPL_H

#include "../TraversalOrderNode.h"

template<class T>
DoubleBranchedNode<T> *DoubleBranchedNode<T>::getLeft() const {
    return left;
}

template<class T>
void DoubleBranchedNode<T>::setLeftRemoveOld(DoubleBranchedNode<T> *left_) {
    DoubleBranchedNode<T> *oldLeft = this->left;
    this->setLeft(left_);
    delete oldLeft;
}

template<class T>
DoubleBranchedNode<T> *DoubleBranchedNode<T>::getRight() const {
    return right;
}


template<class T>
void DoubleBranchedNode<T>::setRightRemoveOld(DoubleBranchedNode<T> *right_) {
    DoubleBranchedNode<T> *oldRight = this->right;
    this->setRight(right_);
    delete oldRight;
}

template<class T>
void DoubleBranchedNode<T>::setRight(DoubleBranchedNode<T> *right_) {
    this->right = right_;
}

template<class T>
void DoubleBranchedNode<T>::setLeft(DoubleBranchedNode<T> *left_) {
    this->left = left_;
}

template<class T>
int DoubleBranchedNode<T>::compareTo(const DoubleBranchedNode<T> *node) const {
    /*TODO*/
    return 0;
}

#endif //ALGORITHM_TRAVERSAL_ORDER_NODE_IMPL_H
