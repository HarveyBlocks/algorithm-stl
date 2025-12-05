/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/7/4
 *
 */
#ifndef ALGORITHM_ORDER_STATISTIC_TREE_NODE_H
#define ALGORITHM_ORDER_STATISTIC_TREE_NODE_H

#include "RedBlackTreeNode.h"

template<class T>
class OrderStatisticTreeNode : public RedBlackTreeNode<T> {
private:
    int size;
public:

    explicit OrderStatisticTreeNode(
            const T &value, tree::RedBlackTreeNodeColor color = tree::RedBlackTreeNodeColor::RED) :
            RedBlackTreeNode<T>(value, color), size(1) {

    }

    explicit OrderStatisticTreeNode(
            BinaryTreeNode<T> *node, tree::RedBlackTreeNodeColor color= tree::RedBlackTreeNodeColor::RED) :
            RedBlackTreeNode<T>(node, color), size(1) {
        this->updateSize();
    }


    static OrderStatisticTreeNode<T> *cast(BinaryTreeNode<T> *node) {
        return dynamic_cast<OrderStatisticTreeNode<T> *>(node);
    }

    [[nodiscard]] int getSize() const {
        return this->size;
    }

    static int getSize(BinaryTreeNode<T> *node) {
        return node == nullptr ? 0 : OrderStatisticTreeNode<T>::cast(node)->getSize();
    }

    void setRight(BinaryTreeNode<T> *right) override {
        this->size -= OrderStatisticTreeNode<T>::getSize(this->getRight());
        BinaryTreeNode<T>::setRight(right);
        this->size += OrderStatisticTreeNode<T>::getSize(this->getRight());
    }

    void setLeft(BinaryTreeNode<T> *left) override {
        this->size -= OrderStatisticTreeNode<T>::getSize(this->getLeft());
        BinaryTreeNode<T>::setLeft(left);
        this->size += OrderStatisticTreeNode<T>::getSize(this->getLeft());
    }

    int updateSize() {
        return this->size = getSize(this->getLeft()) + getSize(this->getRight()) + 1;
    }

    static int updateSize(BinaryTreeNode<T> *node) {
        return OrderStatisticTreeNode<T>::cast(node)->updateSize();
    }
};


#endif //ALGORITHM_ORDER_STATISTIC_TREE_NODE_H
