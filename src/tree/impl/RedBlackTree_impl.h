/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/30
 *
 */
#ifndef ALGORITHM_RED_BLACK_TREE_IMPL_H
#define ALGORITHM_RED_BLACK_TREE_IMPL_H

#include "../RedBlackTree.h"


template<class T>
bool RedBlackTree<T>::colorCurrent(BinaryTreeNode<T> *root) {
    if (root == nullptr) {
        return true;
    }
    // 根节点一定是黑色的
    if (RedBlackTreeNode<T>::isRed(root)) {
        return false;
    }
    Stack<BinaryTreeNode<T> *> trace;
    // 栈用于迭代遍历树
    Stack<int> blackHeight;
    trace.push(root);
    blackHeight.push(0);
    int firstBlackHeight = 0;
    BinaryTreeNode<T> *first = root;
    while (first) {
        if (RedBlackTreeNode<T>::isBlack(first)) {
            firstBlackHeight++;
        }
        first = first->getLeft();
    }
    firstBlackHeight++;
    while (!trace.empty()) {
        BinaryTreeNode<T> *node = trace.pop();
        int currentBlackHeight = blackHeight.pop();
        if (node == nullptr) {
            if (currentBlackHeight != firstBlackHeight) {
                return false; // 如果当前路径的黑高度与第一个叶子节点的黑高度不同，则违反性质
            }
            continue;
        }
        BinaryTreeNode<T> *left = node->getLeft();
        BinaryTreeNode<T> *right = node->getRight();
        // 检查当前节点是否违反红黑树性质
        if (RedBlackTreeNode<T>::isRed(node)) {
            if (RedBlackTreeNode<T>::isRed(left)) {
                return false;
            }
            if (RedBlackTreeNode<T>::isRed(right)) {
                return false;
            }
        } else {
            // 更新当前节点的黑高度
            currentBlackHeight++;
        }
        if (right) {
            trace.push(right);
            blackHeight.push(currentBlackHeight);
        } else {
            trace.push(nullptr);
            blackHeight.push(currentBlackHeight + 1);
        }
        // 将左右子节点入栈，并记录黑高度
        if (left) {
            trace.push(left);
            blackHeight.push(currentBlackHeight);
        } else {
            trace.push(nullptr);
            blackHeight.push(currentBlackHeight + 1);
        }
    }
    return true;
}

template<class T>
BinaryTreeNode<T> *RedBlackTree<T>::insertNode(Stack<BinaryTreeNode<T> *> &trace) {
    // 将节点调整为红黑树的节点
    BinaryTreeNode<T> *newNode = trace.pop();
    if (newNode == nullptr) {
        return newNode;
    }
    RedBlackTreeNode<T> *nodeAfterCast = castInsertNode(newNode);
    trace.push(nodeAfterCast);
    delete newNode;
    // 增加
    this->BinarySearchTree<T>::insertNode(trace);
    // 调整
    while (!rbInsertAdjust(trace));
    return nodeAfterCast;
}

template<class T>
RedBlackTreeNode<T> *
RedBlackTree<T>::castInsertNode(BinaryTreeNode<T> *newNode) const {
    return new RedBlackTreeNode<T>(newNode);
}

template<class T>
bool RedBlackTree<T>::rbInsertAdjust(Stack<BinaryTreeNode<T> *> &trace) {
    BinaryTreeNode<T> *node = trace.pop();

    if (trace.empty()) {
        // 根节点, 直接为黑
        RedBlackTreeNode<T>::cast(node)->setColor(tree::BLACK);
        return true;
    }
    BinaryTreeNode<T> *nodeParent = trace.pop();
    if (RedBlackTreeNode<T>::isBlack(nodeParent)) {
        // 已经正常
        return true;
    }
    if (trace.empty()) {
        throw IllegalStateException();
    }
    BinaryTreeNode<T> *nodeGrandParent = trace.pop();
    bool isLeft = this->BinaryTree<T>::isLeftChild(nodeParent, nodeGrandParent);
    BinaryTreeNode<T> *nodeUncle = isLeft ? nodeGrandParent->getRight() : nodeGrandParent->getLeft();
    if (RedBlackTreeNode<T>::isRed(nodeUncle)) {
        RedBlackTreeNode<T>::painting(nodeParent);
        RedBlackTreeNode<T>::painting(nodeUncle);
        RedBlackTreeNode<T>::painting(nodeGrandParent);
        trace.push(nodeGrandParent);
        return false;
    }

    BinaryTreeNode<T> *nodeGrandGrandParent = trace.empty() ? nullptr : trace.top();
    bool leftChild = false;
    if (nodeGrandGrandParent != nullptr) {
        leftChild = BinaryTree<T>::isLeftChild(nodeGrandParent, nodeGrandGrandParent);
    }
    this->BinaryBalanceSearchTree<T>::rotateAdjust(nodeGrandParent, nodeGrandGrandParent);
    if (nodeGrandGrandParent == nullptr) {
        RedBlackTreeNode<T>::painting(this->root);
    } else {
        if (leftChild) {
            RedBlackTreeNode<T>::painting(nodeGrandGrandParent->getLeft());
        } else {
            RedBlackTreeNode<T>::painting(nodeGrandGrandParent->getRight());
        }
    }
    RedBlackTreeNode<T>::painting(nodeGrandParent);
    return true;
}

template<class T>
bool RedBlackTree<T>::removeNode0(Stack<BinaryTreeNode<T> *> &trace) {
    // 获取删除的节点, 获取颜色
    BinaryTreeNode<T> *removedNode = trace.pop();
    bool leftChild = trace.empty() ? true : BinaryTree<T>::isLeftChild(removedNode, trace.top());

    trace.push(removedNode);
    tree::RedBlackTreeNodeColor color = RedBlackTreeNode<T>::getColor(removedNode);
    BinaryTreeNode<T> *left = removedNode->getLeft();
    BinaryTreeNode<T> *right = removedNode->getRight();
    int removeType = -1;
    if (left == nullptr && right == nullptr) {
        removeType = 0;
    } else if (left || right) {
        removeType = 1;
    }
    if (this->BinarySearchTree<T>::removeNode0(trace)) {
        return true;
    }
    switch (removeType) {
        case 0:
            if (color == tree::RedBlackTreeNodeColor::BLACK) {
                int result;
                while ((result = fixBlackNoneChildNodeRemove(trace, leftChild)) >= 0) {
                    leftChild = result ? true : false;
                }
            }
            // 红节点不需要调整
            break;
        case 1: {
            BinaryTreeNode<T> *replaceNode = this->root;
            if (!trace.empty()) {
                replaceNode = leftChild ? trace.top()->getLeft() : trace.top()->getRight();

            }
            if (RedBlackTreeNode<T>::isBlack(replaceNode)) {
                throw IllegalStateException();
            }
            RedBlackTreeNode<T>::painting(replaceNode);
            break;
        }
        default:
            throw IllegalStateException();
    }
    return false;
}

template<class T>
int RedBlackTree<T>::fixBlackNoneChildNodeRemove(Stack<BinaryTreeNode<T> *> &trace, const bool removedNodeIsLeftChild) {
    if (trace.empty()) {
        return -1;
    }
    BinaryTreeNode<T> *nodeParent = trace.pop();
    BinaryTreeNode<T> *sibling = removedNodeIsLeftChild ? nodeParent->getRight() : nodeParent->getLeft();
    if (RedBlackTreeNode<T>::isBlack(sibling)) {
        // 兄弟是黑色
        if (sibling == nullptr) {
            // RedBlackTreeNode<T>::painting(nodeParent, tree::RedBlackTreeNodeColor::BLACK);
            return -1;
        }
        BinaryTreeNode<T> *leftNephew = sibling->getLeft();
        BinaryTreeNode<T> *rightNephew = sibling->getRight();
        if (RedBlackTreeNode<T>::isBlack(leftNephew) && RedBlackTreeNode<T>::isBlack(rightNephew)) {
            // 两个侄子节点都是黑色节点
            // 兄弟变红
            RedBlackTreeNode<T>::painting(sibling, tree::RedBlackTreeNodeColor::RED);
            if (trace.empty() || RedBlackTreeNode<T>::isRed(nodeParent)) {
                // nodeParent是根, 根变黑
                // nodeParent是红色父亲, 红色父亲变黑
                // +1
                RedBlackTreeNode<T>::painting(nodeParent, tree::RedBlackTreeNodeColor::BLACK);
                return -1;
            }
            // fixBlackNoneChildNodeRemove(trace, trace.top()->getLeft() == nodeParent); // 小型的判断左孩子
            return trace.top()->getLeft() == nodeParent;
        } else {
            // 至少有一个红色的侄子节点
            paintingAndRotate(removedNodeIsLeftChild, sibling, nodeParent, trace.empty() ? nullptr : trace.top());
        }
    } else {
        // 兄弟是红色,
        // 父兄变色
        RedBlackTreeNode<T>::painting(nodeParent);
        RedBlackTreeNode<T>::painting(sibling);
        // 朝被删除节点旋转

        BinaryTreeNode<T> *nodeGrandParent = trace.empty() ? nullptr : trace.top();
        if (removedNodeIsLeftChild) {
            this->BinaryBalanceSearchTree<T>::leftRotate(nodeParent, nodeGrandParent);
        } else {
            this->BinaryBalanceSearchTree<T>::rightRotate(nodeParent, nodeGrandParent);
        }
        trace.push(sibling);
        trace.push(nodeParent);
        return removedNodeIsLeftChild;
    }
    return -1;
}

template<class T>
void RedBlackTree<T>::paintingAndRotate(
        const bool removedNodeIsLeftChild, BinaryTreeNode<T> *sibling, BinaryTreeNode<T> *nodeParent,
        BinaryTreeNode<T> *nodeGrandParent) {
    BinaryTreeNode<T> *leftNephew = sibling->getLeft();
    BinaryTreeNode<T> *rightNephew = sibling->getRight();
    if (removedNodeIsLeftChild) {
        if (RedBlackTreeNode<T>::isRed(rightNephew)) { //RR
            RedBlackTreeNode<T>::painting(rightNephew, RedBlackTreeNode<T>::getColor(sibling));
            RedBlackTreeNode<T>::painting(sibling, RedBlackTreeNode<T>::getColor(nodeParent));
        } else if (RedBlackTreeNode<T>::isRed(leftNephew)) { // RL
            RedBlackTreeNode<T>::painting(leftNephew, RedBlackTreeNode<T>::getColor(nodeParent));
            this->BinaryBalanceSearchTree<T>::rightRotate(sibling, nodeParent);
        } else {
            // 全是null, 应该是全部都是黑色子节点的情况
            throw IllegalStateException();
        }
        this->BinaryBalanceSearchTree<T>::leftRotate(nodeParent, nodeGrandParent);
    } else {
        if (RedBlackTreeNode<T>::isRed(leftNephew)) { // LL
            RedBlackTreeNode<T>::painting(leftNephew, RedBlackTreeNode<T>::getColor(sibling));
            RedBlackTreeNode<T>::painting(sibling, RedBlackTreeNode<T>::getColor(nodeParent));
        } else if (RedBlackTreeNode<T>::isRed(rightNephew)) { // LR
            RedBlackTreeNode<T>::painting(rightNephew, RedBlackTreeNode<T>::getColor(nodeParent));
            this->BinaryBalanceSearchTree<T>::leftRotate(sibling, nodeParent);
        } else {
            throw IllegalStateException();
        }
        this->BinaryBalanceSearchTree<T>::rightRotate(nodeParent, nodeGrandParent);
    }
    RedBlackTreeNode<T>::painting(nodeParent, tree::RedBlackTreeNodeColor::BLACK);
}

template<class T>
std::ostream &RedBlackTree<T>::printWithColor(std::ostream &os) {
    return RedBlackTree<T>::printNodeWithColor(os, this->root);
}

template<class T>
std::ostream &RedBlackTree<T>::printNodeWithColor(std::ostream &os, BinaryTreeNode<T> *node) {
    return BinaryTree<int>::printNode(
            os, node, 1,
            [](std::ostream &os, BinaryTreeNode<int> *node) {
                os << *(RedBlackTreeNode<T>::cast(node));
            });
}


#endif //ALGORITHM_RED_BLACK_TREE_IMPL_H
