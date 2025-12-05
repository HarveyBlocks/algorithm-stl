/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/28
 *
 */
#ifndef ALGORITHM_BINARY_BALANCE_SEARCH_TREE_H
#define ALGORITHM_BINARY_BALANCE_SEARCH_TREE_H

#include "BinarySearchTree.h"

template<class T>
class BinaryBalanceSearchTree : public BinarySearchTree<T> {
public:
    static int balanceFactor(BinaryTreeNode<T> *node) {
        if (node == nullptr) {
            return 0;
        }
        return BinaryTree<T>::maxDepth(node->getLeft()) - BinaryTree<T>::maxDepth(node->getRight());
    }

    /**
     *
     * @return 是否转过一次了
     * @param nodeGrandParent 为nullptr时表示nodeParent为根节点
     */
    bool rotateAdjust(BinaryTreeNode<T> *node, BinaryTreeNode<T> *nodeParent);

    void rightRotate(BinaryTreeNode<T> *node, BinaryTreeNode<T> *parentNode);

    void leftRotate(BinaryTreeNode<T> *node, BinaryTreeNode<T> *parentNode);
};

#include "impl/BinaryBalanceSearchTree_impl.h"

#endif //ALGORITHM_BINARY_BALANCE_SEARCH_TREE_H
