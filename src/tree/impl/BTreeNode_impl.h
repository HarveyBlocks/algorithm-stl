//
// Created by Lenovo on 2025/12/2.
//

#ifndef ALGORITHM_B_TREE_NODE_H
#define ALGORITHM_B_TREE_NODE_H

#include "../../util/Objects.h"
#include "../BTree.h"

template<typename T, typename Cmp>
BTreeNode<T, Cmp>::BTreeNode(int level) :
        datas(new T *[level - 1]), children(new BTreeNode<T, Cmp> *[level]), size(0) {
    for (int i = 0; i < level - 1; ++i) {
        datas[i] = nullptr;
        children[i] = nullptr;
    }
    children[level - 1] = nullptr;
}

template<typename T, typename Cmp>
BTreeNode<T, Cmp>::~BTreeNode() {
    delete[] datas;
    delete[] children;
}

template<typename T, typename Cmp>
int BTreeNode<T, Cmp>::search(const T &value, const BTree<T, Cmp> *belong) const {
    // 依据level, 获悉datas长度, 即可返回目标索引
    // TODO 用二叉查找优化
    for (int i = 0; i <= size; ++i) {
        if (i == size) {
            return -i - 1;
        }
        T *data = datas[i];
        int cmp = belong->cmp(*data, value);
        if (cmp == 0) {
            return i;
        } else if (cmp > 0) {
            // result is between (i-1,i)
            return -i - 1;
        }
    }
    // never
    return -size;
}

template<typename T, typename Cmp>
BTreeNode<T, Cmp> *BTreeNode<T, Cmp>::childAt(int index) const {
    return children[index];
}

template<typename T, typename Cmp>
bool BTreeNode<T, Cmp>::full(int level) const {
    return level - 1 == size;
}

template<typename T, typename Cmp>
bool BTreeNode<T, Cmp>::empty() const {
    return size == 0;
}

template<typename T, typename Cmp>
bool BTreeNode<T, Cmp>::insert(int index, T *data, int level, BTreeNode<T, Cmp> *left, BTreeNode<T, Cmp> *right) {
    Objects::requireTrue(index <= size, "can not insert after node dataSize");
    Objects::checkTrue(size < level - 1, "tree node is full");
    for (int i = size; i > index; --i) {
        datas[i] = datas[i - 1];
    }
    datas[index] = data;
    size++;
    children[index] = left;
    children[index + 1] = right;
    return level - 1 == size;
}

template<typename T, typename Cmp>
BTreeNode<T, Cmp> BTreeNode<T, Cmp>::plus(int index, T *data, BTreeNode<T, Cmp> *left, BTreeNode<T, Cmp> *right) const {
    Objects::requireTrue(index <= size, "can not insert after node dataSize");
    int level = size + 1;
    BTreeNode<T, Cmp> target(level + 1);
    for (int i = 0, j = 0, k = 0; i < size + 1; ++i) {
        if (i == index) {
            target.datas[i] = data;
            target.children[k++] = left;
            target.children[k++] = right;
        } else {
            target.datas[i] = datas[j++];
            target.children[k++] = children[i];
        }
    }
    target.size = level;
    return target;
}

template<typename T, typename Cmp>
void BTreeNode<T, Cmp>::reset() {
    for (int i = 0; i < size; ++i) {
        datas[i] = nullptr;
        children[i] = nullptr;
    }
    children[size] = nullptr;
    size = 0;
}

template<typename T, typename Cmp>
void BTreeNode<T, Cmp>::split(T *&mid, BTreeNode<T, Cmp> *left, BTreeNode<T, Cmp> *right) const {
    int level = size;
    // 1. 的值移动到上面的节点 4->1, 5->2, 6->2
    int midIndex = (level - 1) >> 1;
    // 2. update left
    for (int i = 0; i < midIndex; ++i) {
        left->datas[i] = datas[i];
        left->children[i] = children[i];
    }
    left->size = midIndex;
    left->children[left->size] = this->children[left->size];
    // 3. update data = top->at(index = level>>1);
    mid = datas[midIndex];
    // 4. update right
    for (int i = midIndex + 1, j = 0; i < level; ++i, ++j) {
        right->datas[j] = datas[i];
        right->children[j] = children[i];
    }
    right->size = level - midIndex - 1;
    right->children[right->size] = this->children[level];
}

template<typename T, typename Cmp>
T *BTreeNode<T, Cmp>::resetData(int index, const T &value) {
    T *old = datas[index];
    T *reset = datas[index] = new T(value);
    delete old;
    return reset;
}

template<typename T, typename Cmp>
T *BTreeNode<T, Cmp>::dataAt(int index) const {
    return datas[index];
}

#ifdef DEBUG

#include <queue>

template<typename T, typename Cmp>
void BTreeNode<T, Cmp>::showBTree(int level) const {
    std::queue<std::pair<const BTreeNode<T, Cmp> *, int>> que;
    int depth = 0;
    que.push({this, depth});
    while (!que.empty()) {
        std::pair<const BTreeNode<T, Cmp> *, int> front = que.front();
        que.pop();
        const BTreeNode<T, Cmp> *node = front.first;
        int nowDepth = front.second;
        if (nowDepth > depth) {
            std::cout << std::endl;
            depth = nowDepth;
        }
        if (node == nullptr) {
            std::cout << "nil_node " << std::flush;
            continue;
        }
        std::cout << node->size << "(";
        for (int i = 0; i < level - 1; ++i) {
            T *data = node->datas[i];
            if (data != nullptr) {
                std::cout << *data;
            } else {
                std::cout << "nil";
            }
            std::cout << "|)"[i == level - 2] << std::flush;
            que.push({node->children[i], depth + 1});
        }
        std::cout << "\t";
        que.push({node->children[level - 1], depth + 1});
    }
    std::cout << std::endl;
}

#endif

#endif //ALGORITHM_B_TREE_NODE_H
