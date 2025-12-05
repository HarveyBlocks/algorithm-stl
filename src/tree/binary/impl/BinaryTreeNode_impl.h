/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/21
 *
 */
#ifndef ALGORITHM_TREE_NODE_IMPL_H
#define ALGORITHM_TREE_NODE_IMPL_H

#include "../BinaryTreeNode.h"


template<class T>
BinaryTreeNode<T>::BinaryTreeNode(const T &value) : value(new T(value)), left(nullptr), right(nullptr) {
}

template<class T>
T *BinaryTreeNode<T>::getValue() const {
    if (value == nullptr) {
        throw IllegalStateException("Null Value Point");
    }
    return value;
}

template<class T>
void BinaryTreeNode<T>::setValue(T *value_) {
    delete value;
    BinaryTreeNode::value = new T(*value_);
}


template<class T>
BinaryTreeNode<T> *BinaryTreeNode<T>::getLeft() const {
    return left;
}

template<class T>
void BinaryTreeNode<T>::setLeftRemoveOld(BinaryTreeNode<T> *left_) {
    BinaryTreeNode<T> *oldLeft = this->left;
    this->setLeft(left_);
    delete oldLeft;
}

template<class T>
BinaryTreeNode<T> *BinaryTreeNode<T>::getRight() const {
    return right;
}


template<class T>
void BinaryTreeNode<T>::setRightRemoveOld(BinaryTreeNode<T> *right_) {
    BinaryTreeNode<T> *oldRight = this->right;
    this->setRight(right_);
    delete oldRight;
}

template<class T>
void BinaryTreeNode<T>::setRight(BinaryTreeNode<T> *right_) {
    this->right = right_;
}

template<class T>
void BinaryTreeNode<T>::setLeft(BinaryTreeNode<T> *left_) {
    this->left = left_;
}

template<class T>
int BinaryTreeNode<T>::compareTo(const BinaryTreeNode<T> *node) const {
    return this->compareTo(*(node->value));
}

template<class T>
int BinaryTreeNode<T>::compareTo(const T &value_) const {
    return *(this->value) == value_ ? 0 : *(this->value) > value_ ? 1 : -1;
}

template<class T>
BinaryTreeNode<T>::~BinaryTreeNode() {
    delete value;
}

#endif //ALGORITHM_TREE_NODE_IMPL_H
