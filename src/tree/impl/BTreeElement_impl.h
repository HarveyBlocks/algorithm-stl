//
// Created by Lenovo on 2025/12/3.
//

#ifndef ALGORITHM_BTREE_ELEMENT_IMPL_H
#define ALGORITHM_BTREE_ELEMENT_IMPL_H

#include "../BTree.h"
#include "../../util/Objects.h"

template<typename T, typename Cmp>
BTreeElement<T, Cmp>::BTreeElement(BTreeNode<T, Cmp> *node, int index) : node(node), index(index) {}

template<typename T, typename Cmp>
void BTreeElement<T, Cmp>::pushPrevious(BTreeTrace<T, Cmp> &stack) const {
    if (node->leaf()) {
        stack.push(*this);
        return;
    }
    BTreeElement cur(node, -index - 1);
    while (!cur.node->leaf()) {
        stack.push(cur);
        BTreeNode<T, Cmp> *child = cur.child();
        cur = BTreeElement(child, -child->size - 1);
    }
    cur.index = -cur.index - 2;
    stack.push(cur);
}

template<typename T, typename Cmp>
BTreeElement<T, Cmp> &BTreeElement<T, Cmp>::operator=(const BTreeElement<T, Cmp> &src) {
    if (this == &src) {
        return *this;
    }
    this->node = src.node;
    this->index = src.index;
    return *this;
}

template<typename T, typename Cmp>
T *&BTreeElement<T, Cmp>::data() {
    Objects::checkTrue(index >= 0, "index not refer to data");
    return node->datas[index];
}

template<typename T, typename Cmp>
BTreeNode<T, Cmp> *&BTreeElement<T, Cmp>::child() const {
    Objects::checkTrue(index < 0, "index not refer to child");
    return node->children[-index - 1];
}

template<typename T, typename Cmp>
void BTreeElement<T, Cmp>::tidyLeaf() {
    Objects::requireTrue(node->leaf(), "only leaf can tidy");
    for (int i = index; i < node->size - 1; ++i) {
        node->datas[i] = node->datas[i + 1];
    }
    node->size--;
    node->datas[node->size] = nullptr;
}


template<typename T, typename Cmp>
void BTreeElement<T, Cmp>::moveFromRightBrother(BTreeNode<T, Cmp> *cur, BTreeNode<T, Cmp> *right) {
    T *parentData = this->data();
    // parent->cur.last
    cur->datas[cur->size] = parentData;
    cur->size++;
    cur->children[cur->size] = right->childAt(0);
    // right.first->parent
    this->data() = right->datas[0];
    // remove right.first
    right->removeFirst();
}

template<typename T, typename Cmp>
void BTreeElement<T, Cmp>::moveFromLeftBrother(BTreeNode<T, Cmp> *cur, BTreeNode<T, Cmp> *left) {
    T *parentData = this->data();
    // parent->cur.first
    cur->insertFirst(parentData, left->childAt(left->size)/*left.children.last*/);
    // left.last->parent
    this->data() = left->datas[left->size - 1];
    // remove left.last
    left->children[left->size] = nullptr;
    left->size--;
    left->datas[left->size] = nullptr;
}

template<typename T, typename Cmp>
void BTreeElement<T, Cmp>::combine(int level) {
    // (left|parent|right)->left
    T *data = this->data();
    BTreeNode<T, Cmp> *left = this->node->children[this->index];
    BTreeNode<T, Cmp> *right = this->node->children[this->index + 1];
    int combineSize = left->size + 1 + right->size;
    Objects::requireTrue(combineSize < level, "can not combine for node is larger than upper bound after combine!");
    left->datas[left->size] = data;
    left->size++;
    for (int i = 0; i < right->size; ++i) {
        left->datas[left->size] = right->datas[i];
        left->children[left->size] = right->children[i];
        left->size++;
    }
    left->children[left->size] = right->children[right->size];
    // delete node right
    delete right;
    // parent.datas[index+1:]->[index:]
    // parent.children[index+2:]->[index+1:]
    for (int i = index; i < node->size - 1; ++i) {
        node->datas[i] = node->datas[i + 1];
        node->children[i + 1] = node->children[i + 2];
    }
    // parent.children.last = nullptr
    node->children[node->size] = nullptr;
    node->size--;
    // parent.datas.last = nullptr
    node->datas[node->size] = nullptr;
}


#endif //ALGORITHM_BTREE_ELEMENT_IMPL_H
