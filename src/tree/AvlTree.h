/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/27
 *
 */
#ifndef ALGORITHM_AVL_TREE_H
#define ALGORITHM_AVL_TREE_H

#include "BinaryBalanceSearchTree.h"

template<class T>
class AvlTree : public BinaryBalanceSearchTree<T> {
public:
    BinaryTreeNode<T> *insertNode(Stack<BinaryTreeNode<T> *> &trace) override;

    void removeNode(Stack<BinaryTreeNode<T> *> &trace) override;
};


template<class T>
BinaryTreeNode<T> *AvlTree<T>::insertNode(Stack<BinaryTreeNode<T> *> &trace) {
    this->BinarySearchTree<T>::insertNode(trace);
    BinaryTreeNode<T> *node = trace.pop();
    BinaryTreeNode<T> *pNode = node;
    BinaryTreeNode<T> *nodeParent = trace.empty() ? nullptr : trace.pop();
    while (this->BinaryBalanceSearchTree<T>::rotateAdjust(node, nodeParent)) {
        node = nodeParent;
        nodeParent = trace.empty() ? nullptr : trace.pop();
    }
    return pNode;
}

template<class T>
void AvlTree<T>::removeNode(Stack<BinaryTreeNode<T> *> &trace) {
    this->BinarySearchTree<T>::removeNode(trace);
    if (trace.empty()) {
        // 树唯有根节点
        return;
    }
    BinaryTreeNode<T> *node = trace.pop();
    if (trace.empty()) {
        // 树唯有一个根节点
        this->BinaryBalanceSearchTree<T>::rotateAdjust(node, nullptr);
        return;
    }
    BinaryTreeNode<T> *nodeParent = trace.pop();
    while (true) {
        this->BinaryBalanceSearchTree<T>::rotateAdjust(node, nodeParent);
        if (nodeParent == nullptr) {
            break;
        }
        node = nodeParent;
        nodeParent = trace.empty() ? nullptr : trace.pop();
    }
}


#endif //ALGORITHM_AVL_TREE_H
