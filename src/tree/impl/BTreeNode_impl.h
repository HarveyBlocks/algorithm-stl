//
// Created by Lenovo on 2025/12/2.
//

#ifndef ALGORITHM_BTREE_NODE_H
#define ALGORITHM_BTREE_NODE_H

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
    int high = size - 1;
    int low = 0;
    while (low <= high) {
        int mid = int(low + ((unsigned int) (high - low) >> 1));
        T *data = datas[mid];
        int cmp = belong->cmp(*data, value);
        if (cmp < 0) {
            low = mid + 1;
        } else if (cmp > 0) {
            high = mid - 1;
        } else {
            return mid; // key found
        }
    }
    return -(low + 1);  // key not found.
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
bool BTreeNode<T, Cmp>::leaf() const {
    return this->children[this->size] == nullptr;
}

template<typename T, typename Cmp>
bool BTreeNode<T, Cmp>::insert(int index, T *data, int level, BTreeNode<T, Cmp> *left, BTreeNode<T, Cmp> *right) {
    Objects::requireTrue(index <= size, "can not insert after node dataSize");
    Objects::checkTrue(size < level - 1, "tree node is full");
    for (int i = size; i > index; --i) {
        datas[i] = datas[i - 1];
        children[i + 1] = children[i];
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

template<typename T, typename Cmp>
void BTreeNode<T, Cmp>::insertFirst(T *data, BTreeNode<T, Cmp> *firstChild) {
    for (int i = size; i > 0; --i) {
        datas[i] = datas[i - 1];
        children[i + 1] = children[i];
    }
    children[1] = children[0];
    // 添加data和children
    children[0] = firstChild;
    datas[0] = data;
    size++;
}

template<typename T, typename Cmp>
void BTreeNode<T, Cmp>::removeFirst() {
    for (int i = 0; i < size - 1; ++i) {
        datas[i] = datas[i + 1];
        children[i] = children[i + 1];
    }
    children[size - 1] = children[size];
    // 删除多余的data和children
    children[size] = nullptr;
    size--;
    datas[size] = nullptr;
}
#ifdef DEBUG

#include <queue>

template<typename T, typename Cmp>
double BTree<T, Cmp>::calRate() const {
    std::queue<const BTreeNode<T, Cmp> *> que;
    que.push(this->root);
    unsigned long long used = 0;
    unsigned long long nodeCnt = 0;
    // (id,size,parent)
    while (!que.empty()) {
        const BTreeNode<T, Cmp> *node = que.front();
        que.pop();
        if (node == nullptr) {
            continue;
        }
        nodeCnt++;
        for (int i = 0; i < level - 1; ++i) {
            T *data = node->datas[i];
            if (data != nullptr) {
                used++;
            }
            que.push(node->children[i]);
        }
        que.push(node->children[level - 1]);
    }
    return double(used) * 1.0 / nodeCnt / (level - 1);
}

template<typename T, typename Cmp>
void BTreeNode<T, Cmp>::showBTree(int level, std::ostream &os) const {
    std::queue<std::pair<const BTreeNode<T, Cmp> *, std::pair<int, std::pair<int, int>>>> que;
    int depth = 0;
    int cnt = 0;
    que.emplace(this, std::pair<int, std::pair<int, int>>{depth, std::pair<int, int>{cnt++, -1}});
    // (id,size,parent)
    while (!que.empty()) {
        std::pair<const BTreeNode<T, Cmp> *, std::pair<int, std::pair<int, int>>> front = que.front();
        que.pop();
        const BTreeNode<T, Cmp> *node = front.first;
        int nowDepth = front.second.first;
        int id = front.second.second.first;
        int parentId = front.second.second.second;
        if (nowDepth > depth) {
            os << std::endl;
            depth = nowDepth;
        }
        if (node == nullptr) {
            continue;
        }
        os << "(" << id << "|" << node->size << "|" << parentId << ")" << "(";
        for (int i = 0; i < level - 1; ++i) {
            T *data = node->datas[i];
            if (data != nullptr) {
                os << *data;
            } else {
                os << "n";
            }
            os << "|)"[i == level - 2] << std::flush;;;
            que.push({node->children[i],
                      std::pair<int, std::pair<int, int>>{depth + 1, std::pair<int, int>{cnt++, id}}});
        }
        os << "\t";
        que.push({node->children[level - 1],
                  std::pair<int, std::pair<int, int>>{depth + 1, std::pair<int, int>{cnt++, id}}});
    }
    os << std::endl;
}

#endif

#endif //ALGORITHM_BTREE_NODE_H
