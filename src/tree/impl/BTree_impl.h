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
    while (cur != nullptr) {
        int index = cur->search(value, this);
        trace.push(BTreeElement<T, Cmp>(cur, index));
        if (index >= 0) {
            // 找到了
            return trace;
        } else {
            cur = cur->childAt(-index - 1);
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
        int childIndex = index >= 0 ? index : -index - 1;
        trace.push(BTreeElement<T, Cmp>(cur, -childIndex - 1));
        cur = cur->childAt(childIndex);
    }
    insert(data, trace);
}

template<typename T, typename Cmp>
BTreeNode<T, Cmp> *BTree<T, Cmp>::instanceNode() const {
    return new BTreeNode<T, Cmp>(level);
}


template<typename T, typename Cmp>
void BTree<T, Cmp>::insert(const T &data, BTreeTrace<T, Cmp> &trace) {
    BTreeNode<T, Cmp> *left = nullptr;
    BTreeNode<T, Cmp> *right = nullptr;
    T *ref = new T(data);
    while (!trace.empty()) {
        const BTreeElement<T, Cmp> &top = trace.pop();
        BTreeNode<T, Cmp> *node = top.node;
        int index = -top.index - 1; // 总是child_index
        // 2. 如果节点未满, 插入节点
        if (!node->full(level)) {
            node->insert(index, ref, this->level, left, right);
            return;
        }
        // 3. 如果节点满了
        // 3.1. 分裂
        const BTreeNode<T, Cmp> &tempNode = node->plus(index, ref, left, right);
        node->reset();
        left = node, right = instanceNode();
        tempNode.split(ref, left, right);
        //  3.2. 指针指向上面的节点, 返回3
    }
    // 新root
    root = instanceNode();
    root->insert(0, ref, this->level, left, right);
}

template<typename T, typename Cmp>
bool BTree<T, Cmp>::tryMoveFromBrother(
        BTreeNode<T, Cmp> *cur, BTreeElement<T, Cmp> parent, int lowerBound) {
    //  5.1.1 先检查是否存在右兄弟
    if (parent.index > parent.node->size) {
        return false;
    }
    if (parent.index < parent.node->size) {
        // 存在右兄弟
        BTreeNode<T, Cmp> *brother = parent.node->childAt(parent.index + 1);
        if (brother->size > lowerBound) {
            // 右兄弟合理
            //  5.1.2 选了右兄弟, 叶子被父偏右覆盖, 父偏右被右子最左覆盖, 删除父右子最左
            parent.moveFromRightBrother(cur, brother);
            return true;
        }
    }
    if (parent.index <= 0) {
        return false;
    }
    BTreeNode<T, Cmp> *brother = parent.node->childAt(parent.index - 1);
    if (brother->size <= lowerBound) {
        return false;
    }
    parent.index--;// 左移, 指向偏左的data
    // 5.1.1 选了左兄弟, 叶子被父偏左覆盖, 父偏左被左子最右覆盖, 删除父左子最右
    parent.moveFromLeftBrother(cur, brother);
    return true;
}

template<typename T, typename Cmp>
void BTree<T, Cmp>::remove(BTreeTrace<T, Cmp> &trace) {
    if (trace.empty()) {
        return;
    }
    // 1. 到前驱
    BTreeElement<T, Cmp> target = trace.pop();
    if (target.index < 0) {
        // 没找到目标, 不删除不存在的节点
        return;
    }
    // 2. 前驱一定是叶子, 值和当前节点替换
    target.pushPrevious(trace);
    BTreeElement<T, Cmp> element = trace.pop();
    // 2.1 释放资源
    delete target.data();
    target.data() = element.data();
    element.data() = nullptr;
    // 3. 将问题转化为删除叶子节点 cur (size 变化, 等等)
    element.tidyLeaf();
    if (trace.empty()) {
        // 没爹了? 自己就是根
        return;
    }
    removeLeaf(trace, element.node);
}

template<typename T, typename Cmp>
void BTree<T, Cmp>::removeLeaf(BTreeTrace<T, Cmp> &trace, BTreeNode<T, Cmp> *cur) {
    int lowerBound = (level - 1) >> 1; // 4:1, 5:2, 6:2
    while (!trace.empty()) {
        // 4. 删除后叶子不小于下限(>=lowerBound), 直接删除
        if (cur->size >= lowerBound) {
            //  5.3 检查父亲是否小于下限, 是, 则回到4
            return;
        }
        // 5. 删除叶子小于下限(<lowerBound)
        // 5.1 存在至少一个兄弟, 去掉一个后依旧满足下限
        BTreeElement<T, Cmp> parent = trace.pop();
        parent.index = -parent.index - 1; // 指向child偏右的data
        if (tryMoveFromBrother(cur, parent, lowerBound)) {
            return;
        }
        // 没有合适的兄弟
        // 5.2 兄弟都恰好在下限, 选择右兄弟(尽可能, 如果自己就是最右则另当别论)
        if (parent.index == parent.node->size) {
            // 最右边, 则选择左兄弟, cur is last
            parent.index--;
        }
        // 选择右兄弟
        parent.combine(level);
        // for next loop
        cur = parent.node;
    }
    // 此时cur就是root
    // 6. 如果root被合并到下方节点, 则更换root
    if (cur->size > 0) {
        return;// 根节点允许小于lowerBound
    }
    // 需要更换root了
    root = cur->children[0];
    cur->children[0] = nullptr;
    delete cur;
}
#ifdef DEBUG

template<typename T, typename Cmp>
void BTree<T, Cmp>::showBTree(std::ostream &os) const {
    os << "-------------------" << level << "-------------------" << std::endl;
    this->root->showBTree(this->level, os);
}

#endif


#endif //ALGORITHM_BTREE_IMPL_H
