//
// Created by Lenovo on 2025/12/2.
//

#ifndef ALGORITHM_BTREE_IMPL_H
#define ALGORITHM_BTREE_IMPL_H

#include "../BTree.h"

template<typename T, typename Cmp>
BTree<T, Cmp>::BTree(int level, const Cmp &cmp) :
        level(level), cmp(std::move(cmp)) {
            root = instanceNode();
}

template<typename T, typename Cmp>
BTree<T, Cmp>::~BTree() {
    clear();
    root.release();
}

template<typename T, typename Cmp>
void BTree<T, Cmp>::clear() {
    // 释放除了root以外所有资源
    Stack<BTreeNodeReference<T, Cmp> > stack;
    stack.push(root);
    while (!stack.empty()) {
        BTreeNodeReference<T, Cmp> node = stack.pop();
        if (node == nullptr) {
            continue;
        }
        for (int i = 0; i < node->filledCount(); ++i) {
            delete node->dataAt(i);
            stack.push(node->childAt(i));
        }
        if (node->filledCount() != 0) {
            stack.push(node->childAt(node->filledCount()));
        }
        for (int i = node->filledCount(); i < level - 1; ++i) {
            if (node->dataAt(i) != nullptr || node->childAt(i + 1) != nullptr) {
                std::cout<< "?" <<std::endl;
            }
        }
        node.release();
    }
    root = instanceNode();
}


template<typename T, typename Cmp>
BTreeTrace<T, Cmp> BTree<T, Cmp>::search(const T &value) const {
    BTreeNodeReference<T, Cmp> cur = root;
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
BTreeNodeReference<T, Cmp> BTree<T, Cmp>::instanceNode() const {
    return BTreeNodeReference(new BTreeNode<T, Cmp>(level));
}

template<typename T, typename Cmp>
void BTree<T, Cmp>::insert(const T &data) {
    // 1. search到leaf, 构建trace
    // 规定, 如果相等, 进入data左边
    // 也就是data<=node.data => node.data.left
    // 也就是node.data<=data => node.data.right
    BTreeNodeReference<T, Cmp> cur = root;
    BTreeTrace<T, Cmp> trace;
    Stack<int> indexTrace;
    while (cur != nullptr) {
        int index = cur->search(data, this);
        int childIndex = index >= 0 ? index : -index - 1;
        trace.push(BTreeElement<T, Cmp>(cur, -childIndex - 1));
        cur = cur->childAt(childIndex);
    }
    insertLeaf(data, trace);
}


template<typename T, typename Cmp>
void BTree<T, Cmp>::insertLeaf(const T &data, BTreeTrace<T, Cmp> &trace) {
    InsertGroup insertGroup(new T(data));
    int upperBound = level - 1;
    while (!trace.empty()) {
        BTreeElement<T, Cmp> top = trace.pop();
        // 2. 如果节点未满, 插入节点
        if (!top.node->full(level)) {
            top.insert(this->level, insertGroup);
            return;
        }
        // 4. 如果节点满了
        if (!trace.empty()) {
            // 4.1. 转移到兄弟
            const BTreeElement<T, Cmp> &parent = trace.top();// 搞一个拷贝, 不要修改了trace了
            if (parent.tryMoveToBrother(top, upperBound, insertGroup)) {
                return;
            }
        }
        // 4.2. 分裂
        const BTreeNode<T, Cmp> &tempNode = top.plus(insertGroup);
        top.node->reset();
        insertGroup.left = top.node, insertGroup.right = instanceNode();
        tempNode.split(insertGroup);
        //  5.2. 指针指向上面的节点, 返回2
    }
    // 新root
    root = instanceNode();
    BTreeElement<T, Cmp>(root, -1/*children[0]*/).insert(this->level, insertGroup);
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
bool BTree<T, Cmp>::empty() {
    return root->empty();
}

template<typename T, typename Cmp>
void BTree<T, Cmp>::removeLeaf(BTreeTrace<T, Cmp> &trace, BTreeNodeReference<T, Cmp> cur) {
    int lowerBound = (level - 1) >> 1; // 4:1, 5:2, 6:2
    while (!trace.empty()) {
        // 4. 删除后叶子不小于下限(>=lowerBound), 直接删除
        if (cur->filledCount() >= lowerBound) {
            //  5.3 检查父亲是否小于下限, 是, 则回到4
            return;
        }
        // 5. 删除叶子小于下限(<lowerBound)
        // 5.1 存在至少一个兄弟, 去掉一个后依旧满足下限
        BTreeElement<T, Cmp> parent = trace.pop();
        if (parent.tryMoveFromBrother(cur, lowerBound)) { // const, 不发生改变
            return;
        }
        // 没有合适的兄弟
        parent.index = -parent.index - 1; // 指向child偏右的data
        // 5.2 兄弟都恰好在下限, 选择右兄弟(尽可能, 如果自己就是最右则另当别论)
        if (parent.index == parent.node->filledCount()) {
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
    if (cur->filledCount() > 0) {
        return;// 根节点允许小于lowerBound
    }
    // 需要更换root了
    root = cur->childAt(0);
    cur->setChild(0, BTreeNodeReference<T, Cmp>(nullptr));
    cur.release();
}

#ifdef DEBUG

#include <queue>

template<typename T, typename Cmp>
double BTree<T, Cmp>::calRate() const {
    std::queue<BTreeNodeReference<T, Cmp>> que;
    que.push(this->root);
    unsigned long long used = 0;
    unsigned long long nodeCnt = 0;
    // (id,size,parent)
    while (!que.empty()) {
        BTreeNodeReference<T, Cmp> node = que.front();
        que.pop();
        if (node == nullptr) {
            continue;
        }
        nodeCnt++;
        for (int i = 0; i < level - 1; ++i) {
            T *data = node->dataAt(i);
            if (data != nullptr) {
                used++;
            }
            que.push(node->childAt(i));
        }
        que.push(node->childAt(level - 1));
    }
    return double(used)  / nodeCnt / (level - 1);
}

template<typename T, typename Cmp>
void BTree<T, Cmp>::showBTree(std::ostream &os) const {
    os << "-------------------" << level << "-------------------" << std::endl;
    this->root->showBTree(this->level, os);
}

#endif


#endif //ALGORITHM_BTREE_IMPL_H
