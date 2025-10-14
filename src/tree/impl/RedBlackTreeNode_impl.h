/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/28
 *
 */
#ifndef ALGORITHM_RED_BLACK_TREE_NODE_IMPL_H
#define ALGORITHM_RED_BLACK_TREE_NODE_IMPL_H

#include "../RedBlackTreeNode.h"

template<class T>
RedBlackTreeNode<T> *RedBlackTreeNode<T>::cast(BinaryTreeNode<T> *node) {
    return dynamic_cast<RedBlackTreeNode<T> *>(node);
}

template<class T>
RedBlackTreeNode<T>::RedBlackTreeNode(const T &value, tree::RedBlackTreeNodeColor color) :
        BinaryTreeNode<T>(value), color(color) {}

template<class T>
tree::RedBlackTreeNodeColor RedBlackTreeNode<T>::getColor(BinaryTreeNode<T> *node) {
    if (node == nullptr) {
        // 黑色的null哨兵节点
        // 根节点的父节点也是null, 也是黑的, 很合理
        return tree::RedBlackTreeNodeColor::BLACK;
    }
    return cast(node)->getColor();
}

template<class T>
bool RedBlackTreeNode<T>::isRed(BinaryTreeNode<T> *node) {
    return tree::RedBlackTreeNodeColor::RED == RedBlackTreeNode<T>::getColor(node);
}

template<class T>
bool RedBlackTreeNode<T>::isBlack(BinaryTreeNode<T> *node) {
    return tree::RedBlackTreeNodeColor::BLACK == RedBlackTreeNode<T>::getColor(node);
}

template<class T>
void RedBlackTreeNode<T>::painting(BinaryTreeNode<T> *node, tree::RedBlackTreeNodeColor color) {
    if (node == nullptr) {
        // 黑色的null哨兵节点
        // 根节点的父节点也是null, 也是黑的, 很合理
        return;
    }
    cast(node)->setColor(color);
}

template<class T>
void RedBlackTreeNode<T>::painting(BinaryTreeNode<T> *node) {
    RedBlackTreeNode<T> *rbNode = cast(node);
    rbNode->color = (rbNode->color == tree::RedBlackTreeNodeColor::BLACK) ?
                    tree::RedBlackTreeNodeColor::RED : tree::RedBlackTreeNodeColor::BLACK;
    std::cout << std::flush;
}

template<class T>
tree::RedBlackTreeNodeColor RedBlackTreeNode<T>::getColor() const {
    return this->color;
}

template<class T>
void RedBlackTreeNode<T>::setColor(tree::RedBlackTreeNodeColor color_) {
    this->color = color_;
}

#endif //ALGORITHM_RED_BLACK_TREE_NODE_IMPL_H
