/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/28
 *
 */
#ifndef ALGORITHM_BINARY_BALANCE_SEARCH_TREE_IMPL_H
#define ALGORITHM_BINARY_BALANCE_SEARCH_TREE_IMPL_H

#include "../BinaryBalanceSearchTree.h"

template<class T>
bool BinaryBalanceSearchTree<T>::rotateAdjust(BinaryTreeNode<T> *node, BinaryTreeNode<T> *nodeParent) {
    if (node == nullptr) {
        return false;
    }
    int factor = BinaryBalanceSearchTree<T>::balanceFactor(node);
    if (factor >= 2) {
        factor = BinaryBalanceSearchTree<T>::balanceFactor(node->getLeft());
        if (factor >= 0) {
            // LL型
            this->rightRotate(node, nodeParent);
        } else {
            // LR型
            this->leftRotate(node->getLeft(), node);
            this->rightRotate(node, nodeParent);
        }
        return false;
    } else if (factor <= -2) {
        factor = BinaryBalanceSearchTree<T>::balanceFactor(node->getRight());
        if (factor <= 0) {
            // RR型
            this->leftRotate(node, nodeParent);
        } else {
            // RL型
            this->rightRotate(node->getRight(), node);
            this->leftRotate(node, nodeParent);
        }
        return false;
    }
    return true;
}


template<class T>
void BinaryBalanceSearchTree<T>::rightRotate(BinaryTreeNode<T> *node, BinaryTreeNode<T> *parentNode) {
    if (node == nullptr) {
        throw NullPointException();
    }
    BinaryTreeNode<T> *left = node->getLeft();
    if (left == nullptr) {
        throw NullPointException();
    }
    node->setLeft(left->getRight());
    // 调整parent, 将left替换node的位置
    if (parentNode == nullptr) {
        if (node != this->root) {
            throw IllegalArgumentException();
        }
        // node = root;
        this->root = left;
    } else if (parentNode->getRight() == node && parentNode->getLeft() != node) {
        // node = left
        parentNode->setRight(left);
    } else if (parentNode->getLeft() == node && parentNode->getRight() != node) {
        // node = right
        parentNode->setLeft(left);
    } else {
        throw IllegalArgumentException();
    }
    left->setRight(node);
}

template<class T>
void BinaryBalanceSearchTree<T>::leftRotate(BinaryTreeNode<T> *node, BinaryTreeNode<T> *parentNode) {
    if (node == nullptr) {
        throw NullPointException();
    }
    BinaryTreeNode<T> *right = node->getRight();
    if (right == nullptr) {
        throw NullPointException();
    }
    node->setRight(right->getLeft());
    // 调整parent, 将right替换node的位置
    if (parentNode == nullptr) {
        if (node != this->root) {
            throw IllegalArgumentException();
        }
        // node = root;
        this->root = right;
    } else if (parentNode->getRight() == node && parentNode->getLeft() != node) {
        // node = left
        parentNode->setRight(right);
    } else if (parentNode->getLeft() == node && parentNode->getRight() != node) {
        // node = right
        parentNode->setLeft(right);
    } else {
        throw IllegalArgumentException();
    }
    right->setLeft(node);
}

#endif //ALGORITHM_BINARY_BALANCE_SEARCH_TREE_IMPL_H
