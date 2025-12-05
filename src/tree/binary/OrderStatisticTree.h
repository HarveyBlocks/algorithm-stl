/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/7/4
 *
 */
#ifndef ALGORITHM_ORDER_STATISTIC_TREE_H
#define ALGORITHM_ORDER_STATISTIC_TREE_H

#include "OrderStatisticTreeNode.h"
#include "RedBlackTree.h"

/**
 * 能够获取第N小的值, head(0)就是最小值
 */
template<class T>
class OrderStatisticTree : public RedBlackTree<T> {
protected:
    RedBlackTreeNode<T> *castInsertNode(BinaryTreeNode<T> *newNode) const override {
        return new OrderStatisticTreeNode<T>(newNode);
    }

public:
    BinaryTreeNode<T> *insertNode(Stack<BinaryTreeNode<T> *> &trace) override {
        BinaryTreeNode<T> *pNode = RedBlackTree<T>::insertNode(trace);
        while (!trace.empty()) {
            OrderStatisticTreeNode<T>::updateSize(trace.pop());
        }
        Stack<OrderStatisticTreeNode<T> *> st;
        this->traversal([&st](BinaryTreeNode<T> *node, int depth) {
            st.push(OrderStatisticTreeNode<T>::cast(node));
            return true;
        });
        while (!st.empty()) {
            st.pop()->updateSize();
        }
        return pNode;
    }

    T *head(int level = 0) {
        BinaryTreeNode<T> *node = this->getRoot();
        int lessCount = 0;
        while (node != nullptr) {
            int leftSize = OrderStatisticTreeNode<T>::getSize(node->getLeft());
            lessCount += leftSize;
            if (lessCount == level) {
                break;
            }
            if (lessCount < level) {
                node = node->getRight();
                lessCount++; // for root
            } else {
                node = node->getLeft();
                lessCount -= leftSize;
            }
        }
        if (node == nullptr) {
            return nullptr;
        }
        if (node->getValue() == nullptr) {
            throw NullPointException();
        }
        return (node->getValue());

    }

};


#endif //ALGORITHM_ORDER_STATISTIC_TREE_H
