/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/22
 *
 */
#ifndef ALGORITHM_BINARY_SEARCH_TREE_IMPL_H
#define ALGORITHM_BINARY_SEARCH_TREE_IMPL_H

#include "../BinarySearchTree.h"

template<class T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> &tree) : BinarySearchTree<T>() {
    const BiFunction<BinaryTreeNode<T> *, int, bool> &task = [this](
            BinaryTreeNode<T> *node, int depth) {
        T *value = node->getValue();
        if (value != nullptr) {
            this->insert(*value);
        }
        return true;
    };
    tree.traversal(task);
}

template<class T>
int BinarySearchTree<T>::remove(const T &value) {
    if (this->root == nullptr && this->empty()) {
        return 0;
    } else if (this->root == nullptr || this->empty()) {
        throw IllegalStateException();
    }

    int count = 0;
    Stack<BinaryTreeNode<T> *> trace;
    while (value == *(this->root->getValue())) {
        count++;
        trace.clear();
        if (this->size == 1) {
            resetRoot(nullptr);
            this->size--;
            return count;
        }
        trace.push(this->root);
        removeNode(trace);
    }
    while (true) {
        BinaryTreeNode<T> *node = this->root;
        trace.clear();
        while (node != nullptr) {
            trace.push(node);
            int cmp = node->compareTo(value);
            if (cmp > 0) {
                // root 大
                node = node->getLeft();
            } else if (cmp < 0) {
                node = node->getRight();
            } else {
                break;
            }
        }
        if (node == nullptr) {// 没找到
            break;
        }
        count++;
        removeNode(trace);
    }
    return count;
}

template<class T>
bool BinarySearchTree<T>::removeNode0(Stack<BinaryTreeNode<T> *> &trace) {
    BinaryTreeNode<T> *node = trace.pop();
    //  次数trace.empty() 说明是根节点
    BinaryTreeNode<T> *nodeParent = trace.empty() ? nullptr : trace.top();

    bool leftChild = (nodeParent == nullptr ? true : BinaryTree<T>::isLeftChild(node, nodeParent));

    BinaryTreeNode<T> *left = node->getLeft();
    BinaryTreeNode<T> *right = node->getRight();
    if (left == nullptr && right == nullptr) {
        // 1
        if (nodeParent == nullptr) {
            resetRoot(nullptr);
        } else {
            if (leftChild) {
                nodeParent->setLeftRemoveOld(nullptr);
            } else {
                nodeParent->setRightRemoveOld(nullptr);
            }
        }
    } else if (right == nullptr) {
        // 2
        if (nodeParent == nullptr) {
            resetRoot(left);
        } else {
            if (leftChild) {
                nodeParent->setLeftRemoveOld(left);
            } else {
                nodeParent->setRightRemoveOld(left);
            }
        }
    } else if (left == nullptr) {
        // 3
        if (nodeParent == nullptr) {
            resetRoot(right);
        } else {
            if (leftChild) {
                nodeParent->setLeftRemoveOld(right);
            } else {
                nodeParent->setRightRemoveOld(right);
            }
        }
    } else {
        // 只是修改, 返回true, 表示确实要等待删除
        trace.push(node);
        trace.push(node->getLeft());
        while (trace.top()->getRight() != nullptr) {
            trace.push(trace.top()->getRight());
        }
        node->setValue(trace.top()->getValue());
        return true;
    }
    this->size--;
    return false;
}


template<class T>
void BinarySearchTree<T>::resetRoot(BinaryTreeNode<T> *newRoot) {
    delete this->root;
    this->root = newRoot;
}


template<class T>
void BinarySearchTree<T>::removeNode(Stack<BinaryTreeNode<T> *> &trace) {
    removeNodeByLoop(trace);
}


template<class T>
void BinarySearchTree<T>::removeNodeByRecursive(Stack<BinaryTreeNode<T> *> &trace) {
    if (!removeNode0(trace)) {
        return;
    }
    removeNodeByRecursive(trace);
}

template<class T>
void BinarySearchTree<T>::removeNodeByLoop(Stack<BinaryTreeNode<T> *> &trace) {
    while (removeNode0(trace));
}


template<class T>
void BinarySearchTree<T>::insert(const T &value) {
    Stack<BinaryTreeNode<T> *> trace;
    BinaryTreeNode<T> *node = this->root;
    while (node != nullptr) {
        trace.push(node);
        node = GO_LEFT_BY(node->compareTo(value)) ? node->getLeft() : node->getRight();
    }
    BinaryTreeNode<T> *newNode = new BinaryTreeNode(value);
    trace.push(newNode);
    insertNode(trace);
}


template<class T>
BinaryTreeNode<T> *BinarySearchTree<T>::insertNode(Stack<BinaryTreeNode<T> *> &trace) {
    // 如果没有俩, 说明状态一定错了, pop会抛出异常
    BinaryTreeNode<T> *newNode = trace.pop();
    if (this->root == nullptr && this->size == 0) {
        this->root = newNode;
        this->size++;
        trace.push(newNode);
        return newNode;
    } else if (this->root == nullptr || this->size == 0) {
        throw IllegalStateException();
    }
    BinaryTreeNode<T> *nodeParent = trace.top();
    trace.push(newNode);
    if (nodeParent == nullptr) {
        throw IllegalArgumentException();
    }
    if (GO_LEFT_BY(nodeParent->compareTo(newNode))) {
        nodeParent->setLeftRemoveOld(newNode);
    } else {
        nodeParent->setRightRemoveOld(newNode);
    }
    this->size++;
    return newNode;
}

template<class T>
void BinarySearchTree<T>::traceFamily(Stack<BinaryTreeNode<T> *> trace, BinaryTreeNode<T> *root) {
    if (trace.empty()) {
        return;
    }
    BinaryTreeNode<T> *node = trace.pop();
    if (trace.empty()) {
        return;
    }
    BinaryTreeNode<T> *nodeParent = trace.pop();
    while (true) {
        BinaryTree<T>::isLeftChild(node, nodeParent);
        if (trace.empty()) {
            break;
        }
        node = nodeParent;
        nodeParent = trace.pop();
    }
    if (nodeParent != root) {
        throw IllegalArgumentException();
    }
}

template<class T>
Stack<BinaryTreeNode<T> *> BinarySearchTree<T>::search(const T &value) {
    Stack<BinaryTreeNode<T> *> stack;
    if (this->root == nullptr) {
        return stack;
    }
    BinaryTreeNode<T> *node = this->root;
    while (node != nullptr && *(node->getValue()) != value) {
        stack.push(node);
        node = GO_LEFT_BY(node->compareTo(value)) ? node->getLeft() : node->getRight();
    }
    if (*(node->getValue()) == value) {
        stack.push(node);
    } else {
        stack.push(nullptr);
    }
    return stack;
}

#endif //ALGORITHM_BINARY_SEARCH_TREE_IMPL_H
