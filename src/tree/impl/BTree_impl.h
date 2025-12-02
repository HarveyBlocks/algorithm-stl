//
// Created by Lenovo on 2025/12/2.
//

#ifndef ALGORITHM_BTREE_IMPL_H
#define ALGORITHM_BTREE_IMPL_H

#include "../BTree.h"

template<typename T, typename Cmp>
BTree<T, Cmp>::BTree(int level, Cmp cmp) :
        level(level), cmp(std::move(cmp)) {
    root = instanceNode();
}

template<typename T, typename Cmp>
BTree<T, Cmp>::~BTree() {
    clear();
    delete root;
}

template<typename T, typename Cmp>
void BTree<T, Cmp>::clear() {
    // 释放除了root以外所有资源
    Stack<BTreeNode<T, Cmp> *> stack;
    stack.push(root);
    while (!stack.empty()) {
        BTreeNode<T, Cmp> *node = stack.pop();
        if (node == nullptr) {
            continue;
        }
        for (int i = 0; i < node->size; ++i) {
            delete node->datas[i];
            stack.push(node->children[i]);
        }
        if (node->size != 0) {
            stack.push(node->children[node->size]);
        }
        delete node;
    }
    root = instanceNode();
}

template<typename T, typename Cmp>
void BTree<T, Cmp>::clear(BTreeNode<T, Cmp> *node) {
    // 删除root的所有子元素, 然后删除root
    if (node == nullptr) return;
    for (int i = 0; i < node->size; ++i) {
        clear(node->children[i]);
        delete node->children[i];
        delete node->datas[i];
        node->children[i] = nullptr;
    }
    clear(node->children[node->size]);
    delete node->children[node->size];
    node->children[node->size] = nullptr;
}

template<typename T, typename Cmp>
BTreeTrace<T, Cmp> BTree<T, Cmp>::search(const T &value) const {
    BTreeNode<T, Cmp> *cur = root;
    BTreeTrace<T, Cmp> trace;
    int index = -1;
    while (cur != nullptr) {
        index = cur->search(value, this);
        if (index >= 0) {
            // 找到了
            trace.push(BTreeTraceElement<T, Cmp>(cur, index));
            return trace;
        } else {
            index = -index - 1;
            cur = cur->childAt(index);
            trace.push(BTreeTraceElement<T, Cmp>(cur, index));
        }
    }
    // 没找到
    return BTreeTrace<T, Cmp>();
}

template<typename T, typename Cmp>
void BTree<T, Cmp>::insert(const T &data) {
    // 1. search到leaf, 构建trace
    // 规定, 如果相等, 进入data左边
    // 也就是data<=node.data => node.data.left
    // 也就是node.data<=data => node.data.right
    BTreeNode<T, Cmp> *cur = root;
    BTreeTrace<T, Cmp> trace;
    Stack<int> indexTrace;
    while (cur != nullptr) {
        int index = cur->search(data, this);
        index = index >= 0 ? index : -index - 1;
        trace.push(BTreeTraceElement<T, Cmp>(cur, index));
        cur = cur->childAt(index);
    }
    insert(data, trace);
}

template<typename T, typename Cmp>
BTreeNode<T, Cmp> *BTree<T, Cmp>::instanceNode() const {
    return new BTreeNode<T, Cmp>(level);
}

template<typename T, typename Cmp>
void BTree<T, Cmp>::insert(const T &data, BTreeTrace<T, Cmp> &trace) {
    BTreeNode<T, Cmp> *insertLeft = nullptr;
    BTreeNode<T, Cmp> *insertRight = nullptr;
    T *pData = new T(data);
    while (!trace.empty()) {
        const BTreeTraceElement<T, Cmp> &top = trace.pop();
        BTreeNode<T, Cmp> *node = top.getKey();
        int index = top.getValue();
        // 2. 如果节点未满, 插入节点
        if (!node->full(level)) {
            node->insert(index, pData, this->level, insertLeft, insertRight);
            return;
        }
        // 3. 如果节点满了
        // 3.1. 分裂
        const BTreeNode<T, Cmp> &tempNode = node->plus(index, pData, insertLeft, insertRight);
        node->reset();
        insertLeft = node;
        insertRight = instanceNode();
        tempNode.split(pData, insertLeft, insertRight);
        //  3.2. 指针指向上面的节点, 返回3
    }
    // 新root
    root = instanceNode();
    root->insert(0, pData, this->level, insertLeft, insertRight);
}

#ifdef DEBUG

template<typename T, typename Cmp>
void BTree<T, Cmp>::showBTree() const {
    std::cout << "-----------------------------------" << std::endl;
    this->root->showBTree(this->level);
}

#endif


#endif //ALGORITHM_BTREE_IMPL_H
