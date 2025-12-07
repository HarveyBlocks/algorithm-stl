//
// Created by Lenovo on 2025/12/2.
//

#ifndef ALGORITHM_BTREE_IMPL_H
#define ALGORITHM_BTREE_IMPL_H

#include "../BTree.h"

#ifdef DEBUG

#include <queue>

#include <stack>

#endif

namespace harvey::algorithm::tree::btree {
    template<typename T, typename Cmp>
    BTree<T, Cmp>::BTree(int order, const Cmp &cmp) :
            order(order), cmp(::std::move(cmp)) {
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
            if (node == nullptr) continue;
            for (int i = 0; i < node->filledCount(); ++i) {
                node->dataAt(i).release();
                const BTreeNodeReference<T, Cmp> &child = node->childAt(i);
                if (child != nullptr) stack.push(child);
            }
            if (node->filledCount() != 0) {
                const BTreeNodeReference<T, Cmp> &child = node->childAt(node->filledCount());
                if (child != nullptr) stack.push(child);
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
        return BTreeNodeReference(new BTreeNode<T, Cmp>(order));
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
        InsertGroup insertGroup(data);
        int upperBound = order - 1;
        while (!trace.empty()) {
            BTreeElement<T, Cmp> top = trace.pop();
            // 2. 如果节点未满, 插入节点
            if (!top.node->full(order)) {
                top.insert(this->order, insertGroup);
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
        BTreeElement<T, Cmp>(root, -1/*children[0]*/).insert(this->order, insertGroup);
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
        target.data().release();
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
        int lowerBound = (order - 1) >> 1; // 4:1, 5:2, 6:2
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
            parent.combine(order);
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

#ifdef BULK

    template<typename T, typename Cmp>
    BTree<T, Cmp> &BTree<T, Cmp>::bulk(const bulk::BulkSource<T> &source) {
        // 1. 用count算出能建造出几层的树(不考虑是否需要分裂)->N层及以上, N+1层以下
        // 2. 构建N-1层(满), 需要元素X_1个, count==K*X+(K-1)+M
        //      特别的, 构建N-2层满, 需要元素X_2个
        // 3. 如果M==0, 构建K个N-1层(满), root节点的元素是K-1个, 由于条件一, K<order-1
        // 4. 如果M>0, 构建K+1个N-1层, 但不满, 每一个的个数是count_1 = (count-k)/(k+1)
        //      由条件1,2得X_2<count_1<X_1
        // 故可以递归得构建, 步骤一二的判断过程直接执行, 步骤三四递归构架树, 将source划分成一块一块的, 然后构建
        clear();
        root.release();
        root = source.template build<Cmp>(order);
        return *this;
    }

#endif
#ifdef DEBUG

    template<typename T, typename Cmp>
    double BTree<T, Cmp>::calRate() const {
        ::std::queue<BTreeNodeReference<T, Cmp>> que;
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
            for (int i = 0; i < order - 1; ++i) {
                const BTreeData<T> &data = node->dataAt(i);
                if (data != nullptr) {
                    used++;
                }
                que.push(node->childAt(i));
            }
            que.push(node->childAt(order - 1));
        }
        return double(used) / nodeCnt / (order - 1);
    }

    template<typename T, typename Cmp>
    void BTree<T, Cmp>::showBTree(::std::ostream &os) const {
        os << "-------------------" << order << "-------------------" << ::std::endl;
        this->root->showBTree(this->order, os);
    }

    template<typename T, typename Cmp>
    int BTree<T, Cmp>::qualified() const {
        // 1. lower bound 和 upper bound
        // 2. 层数都一样
        // 3. size都匹配
        ::std::stack<::std::pair<int, BTreeNodeReference<T, Cmp>>> stk;
        stk.push({1, this->root});
        int depthMax = 0;
        while (!stk.empty()) {
            auto pair = stk.top();
            int depth = pair.first;
            BTreeNodeReference<T, Cmp> node = pair.second;
            stk.pop();
            int filledCount = node->filledCount();
            if (filledCount >= order || (this->root != node && filledCount < (order - 1) >> 1)) {
                throw IllegalStateException("filled count is not match with order");
            }
            bool leaf = node->leaf();
            for (int i = 0; i < filledCount; ++i) {
                const BTreeData<T> &data = node->dataAt(i);
                BTreeNodeReference<T, Cmp> child = node->childAt(i);
                if (data == nullptr) {
                    throw IllegalStateException("null data in filled element");
                }
                if (leaf) {
                    continue;
                }
                if (child == nullptr) {
                    throw IllegalStateException("null child in filled element");
                }
                stk.push({depth + 1, child});
            }
            if (leaf) {
                if (depthMax == 0) {
                    depthMax = depth;
                } else if (depthMax != depth) {
                    throw IllegalStateException("depth not equals with other node");
                }
            } else if (!node->empty()) {
                BTreeNodeReference<T, Cmp> child = node->childAt(filledCount);
                if (child == nullptr) {
                    throw IllegalStateException("null child in filled element");
                }
                stk.push({depth + 1, child});
            }
            for (int i = filledCount; i < order - 1; ++i) {
                const BTreeData<T> &data = node->dataAt(i);
                BTreeNodeReference<T, Cmp> child = node->childAt(i + 1);
                if (data != nullptr) {
                    throw IllegalStateException("unreleased data in filled element");
                }
                if (child != nullptr) {
                    throw IllegalStateException("unreleased data in filled element");
                }
            }
        }
        return depthMax;
    }

#endif
}

#endif //ALGORITHM_BTREE_IMPL_H
