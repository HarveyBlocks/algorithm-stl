//
// Created by Lenovo on 2025/12/3.
//

#ifndef ALGORITHM_BTREE_ELEMENT_IMPL_H
#define ALGORITHM_BTREE_ELEMENT_IMPL_H

#include "../BTree.h"
#include "../../util/Objects.h"

template<typename T, typename Cmp>
BTreeElement<T, Cmp>::BTreeElement(BTreeNodeReference<T, Cmp> node, int index) : node(node), index(index) {}

template<typename T, typename Cmp>
void BTreeElement<T, Cmp>::pushPrevious(BTreeTrace<T, Cmp> &stack) const {
    if (node->leaf()) {
        stack.push(*this);
        return;
    }
    BTreeElement cur(node, -index - 1);
    while (!cur.node->leaf()) {
        stack.push(cur);
        BTreeNodeReference<T, Cmp> child = cur.child();
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
BTreeNodeReference<T, Cmp> &BTreeElement<T, Cmp>::child() const {
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
BTreeNode<T, Cmp> BTreeElement<T, Cmp>::plus(const InsertGroup<T, Cmp> &insertGroup) {
    return node->plus(-index - 1, insertGroup);
}

template<typename T, typename Cmp>
void BTreeElement<T, Cmp>::insert(int level, const InsertGroup<T, Cmp> &insertGroup) {
     node->insert(-index - 1, level, insertGroup);
}

template<typename T, typename Cmp>
bool BTreeElement<T, Cmp>::tryMoveFromBrother(BTreeNodeReference<T, Cmp> cur, int lowerBound) const {
    int rightData = -index - 1;// 指向偏右的data
    //  5.1.1 先检查是否存在右兄弟
    if (rightData < node->size) {
        // 存在右兄弟
        BTreeNodeReference<T, Cmp> brother = node->childAt(rightData + 1);
        if (brother->size > lowerBound) {
            // 右兄弟合理
            //  5.1.2 选了右兄弟, 叶子被父偏右覆盖, 父偏右被右子最左覆盖, 删除父右子最左
            BTreeElement<T, Cmp>(node, rightData).moveFromRightBrother(cur, brother);
            return true;
        }
    }
    int leftData = rightData - 1;
    if (leftData >= node->size || leftData < 0) {
        return false;
    }
    BTreeNodeReference<T, Cmp> brother = node->childAt(leftData);
    if (brother->size > lowerBound) {
        // 5.1.1 选了左兄弟, 叶子被父偏左覆盖, 父偏左被左子最右覆盖, 删除父左子最右
        BTreeElement<T, Cmp>(node, leftData).moveFromLeftBrother(cur, brother);
        return true;
    }
    return false;
}


template<typename T, typename Cmp>
void BTreeElement<T, Cmp>::moveFromRightBrother(BTreeNodeReference<T, Cmp> cur, BTreeNodeReference<T, Cmp> right) {
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
void BTreeElement<T, Cmp>::moveFromLeftBrother(BTreeNodeReference<T, Cmp> cur, BTreeNodeReference<T, Cmp> left) {
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
    BTreeNodeReference<T, Cmp> left = this->node->children[this->index];
    BTreeNodeReference<T, Cmp> right = this->node->children[this->index + 1];
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
    right.release();
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


template<typename T, typename Cmp>
bool BTreeElement<T, Cmp>::tryMoveToBrother(
        const BTreeElement<T, Cmp> &cur, int upperBound,
        const InsertGroup<T, Cmp> &insertGroup) const {
    int leftData = -index - 2;// 指向偏左的data
    //  5.1.1 先检查是否存在左兄弟
    if (leftData >= 0) {
        // 存在左兄弟
        BTreeNodeReference<T, Cmp> brother = node->childAt(leftData);
        if (brother->size < upperBound) {
            BTreeElement<T, Cmp>(node, leftData).moveToLeftBrother(cur, brother, insertGroup);
            return true;
        }
    }
    int rightData = leftData + 1;
    if (rightData < 0 || rightData >= node->size) {
        return false;
    }
    BTreeNodeReference<T, Cmp> brother = node->childAt(rightData + 1);
    if (brother->size < upperBound) {
        // 5.1.1 选了左兄弟, 叶子被父偏左覆盖, 父偏左被左子最右覆盖, 删除父左子最右
        BTreeElement<T, Cmp>(node, rightData).moveToRightBrother(cur, brother, insertGroup);
        return true;
    }
    return false;
}

template<typename T, typename Cmp>
void BTreeElement<T, Cmp>::moveToLeftBrother(BTreeElement<T, Cmp> cur, BTreeNodeReference<T, Cmp> left,
                                             const InsertGroup<T, Cmp> &insertGroup) {
    // this 作为 parent
    T *newLeftLast = this->data(); // 左兄弟的最后
    T *newParentData;
    BTreeNodeReference<T, Cmp> newLeftLastRight;
    if (cur.index == -1) {
        // 最左, 不需要移动
        newParentData = insertGroup.data;
        newLeftLastRight = insertGroup.left;
        cur.child() = insertGroup.right;
    } else {
        // data 放入 cur, 同时左溢出
        newParentData = cur.node->dataAt(0);
        newLeftLastRight = cur.node->childAt(0);// 将成为左兄弟最后的child, 等待插入
        cur.leftMoveInsert(insertGroup); // 参考insert, 可以覆盖掉一个child, insertGroup.left->cur.child()
    }
    // cur 的左溢出放入 parent[parentIndex]
    this->data() = newParentData;
    // parent[parentIndex] 放入 left 的最右
    left->datas[left->size] = newLeftLast;
    left->size++;
    left->children[left->size] = newLeftLastRight;
}

template<typename T, typename Cmp>
void BTreeElement<T, Cmp>::moveToRightBrother(BTreeElement<T, Cmp> cur, BTreeNodeReference<T, Cmp> right,
                                              const InsertGroup<T, Cmp> &insertGroup) {
    // this 作为 parent
    T *newRightFirst = this->data(); // 右兄弟的最前
    T *newParentData;
    BTreeNodeReference<T, Cmp> newRightFirstLeft;
    if (cur.index == -cur.node->size - 1) {
        // 最右, 不需要移动
        newParentData = insertGroup.data;
        cur.child() = insertGroup.left;
        newRightFirstLeft = insertGroup.right;
    } else {
        // data 放入 cur, 同时右溢出
        newParentData = cur.node->dataAt(cur.node->size - 1);
        newRightFirstLeft = cur.node->childAt(cur.node->size);// 将成为右兄弟第一个的child, 等待插入
        cur.rightMoveInsert(insertGroup); // 参考insert, 可以覆盖掉一个child, insertGroup.left->cur.child()
    }
    // cur 的右溢出放入 parent[parentIndex]
    this->data() = newParentData;
    // parent[parentIndex] 放入 right 的最左
    right->insertFirst(newRightFirst, newRightFirstLeft);
}

template<typename T, typename Cmp>
void BTreeElement<T, Cmp>::leftMoveInsert(const InsertGroup<T, Cmp> &insertGroup) {
    int dataIndex = -index - 1 - 1; // 再减一表示偏左, 按照规范是偏右的
    for (int i = 0; i < dataIndex; ++i) {
        node->datas[i] = node->datas[i + 1];
        node->children[i] = node->children[i + 1]; // 此时
    }
    node->datas[dataIndex] = insertGroup.data;
    node->children[dataIndex] = insertGroup.left;
    node->children[dataIndex + 1] = insertGroup.right;
}

template<typename T, typename Cmp>
void BTreeElement<T, Cmp>::rightMoveInsert(const InsertGroup<T, Cmp> &insertGroup) {
    int dataIndex = -index - 1; // 按照规范是偏右的
    for (int i = node->size - 1; i > dataIndex; --i) {
        node->datas[i] = node->datas[i - 1];
        node->children[i + 1] = node->children[i]; // 此时
    }
    node->datas[dataIndex] = insertGroup.data;
    node->children[dataIndex] = insertGroup.left;
    node->children[dataIndex + 1] = insertGroup.right;
}

#endif //ALGORITHM_BTREE_ELEMENT_IMPL_H
