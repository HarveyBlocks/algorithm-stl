/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/26
 *
 */
#ifndef ALGORITHM_RED_BLACK_TREE_NODE_H
#define ALGORITHM_RED_BLACK_TREE_NODE_H

#include "BinaryTreeNode.h"
#include "../util/ColorfulString.h"

namespace tree {
    enum RedBlackTreeNodeColor {
        BLACK, RED
    };

    util::Color nodeColor2Color(tree::RedBlackTreeNodeColor color) {
        if (color == RedBlackTreeNodeColor::RED) {
            return util::Color::RED;
        }
        if (color == RedBlackTreeNodeColor::BLACK) {
            return util::Color::BLACK;
        }
        throw IllegalArgumentException();
    }
}

template<class T>
class RedBlackTreeNode : public BinaryTreeNode<T> {
private:
    tree::RedBlackTreeNodeColor color;

    explicit RedBlackTreeNode(tree::RedBlackTreeNodeColor color = tree::RedBlackTreeNodeColor::RED) : color(color) {}

public:
    explicit RedBlackTreeNode(const T &value, tree::RedBlackTreeNodeColor color = tree::RedBlackTreeNodeColor::RED);

    explicit RedBlackTreeNode(
            BinaryTreeNode<T> *node,
            tree::RedBlackTreeNodeColor color = tree::RedBlackTreeNodeColor::RED) : RedBlackTreeNode(color) {
        if (node == nullptr) {
            this->color = tree::RedBlackTreeNodeColor::BLACK;
            return;
        }
        this->setValue(node->getValue());
        this->setLeft(node->getLeft());
        this->setRight(node->getRight());
    }

    ~RedBlackTreeNode() override = default;

    static RedBlackTreeNode<T> *cast(BinaryTreeNode<T> *node);

    void setColor(tree::RedBlackTreeNodeColor color);

    [[nodiscard]] tree::RedBlackTreeNodeColor getColor() const;

    static tree::RedBlackTreeNodeColor getColor(BinaryTreeNode<T> *node);

    static bool isRed(BinaryTreeNode<T> *node);

    static bool isBlack(BinaryTreeNode<T> *node);


    /**
     * 着色
     */
    static void painting(BinaryTreeNode<T> *node, tree::RedBlackTreeNodeColor color);

    /**
     * 变色, 红变黑, 黑变红
     */
    static void painting(BinaryTreeNode<T> *node);

    friend std::ostream &operator<<(std::ostream &os, const RedBlackTreeNode<T> &node) {
        T *value = node.getValue();
        if (value == nullptr) {
            return printNil(os);
        }
        String strValue = String::valueOf(*value);
        return os << ColorfulString::painting(strValue, tree::nodeColor2Color(node.color));
    }

    static std::ostream &printNil(std::ostream &os) {
        static const String &nilStr = String("N");
        return os << ColorfulString::painting(nilStr, util::BLACK);
    }
};

#include "impl/RedBlackTreeNode_impl.h"

#endif //ALGORITHM_RED_BLACK_TREE_NODE_H
