//
// Created by Lenovo on 2025/12/7.
//

#ifndef ALGORITHM_BTREE_BULK_SOURCE_IMPL_H
#define ALGORITHM_BTREE_BULK_SOURCE_IMPL_H

#include "BulkSource.h"

namespace harvey::algorithm::tree::btree::bulk {
    template<typename T>
    BulkSource<T>::BulkSource(
            const BulkIterator<T> &begin,
            const BulkIterator<T> &end) :
            begin(begin), end(end) {}

    template<typename T>
    template<typename Cmp>
    BTreeNodeReference<T, Cmp> BulkSource<T>::build(int order) const {// 判断, 调度
        if (sourceSize() == 0) {
            // empty, then return
            return BTreeNodeReference<T, Cmp>(new BTreeNode<T, Cmp>(order));
        }
        RootSplitPolicyFactory factory(order);
        BTreeNodeReference<T, Cmp> node = build<Cmp>(&factory, 1); // 这个layer是随便的, 因为对于root其不生效
        return node;
    }

    template<typename T>
    int BulkSource<T>::sourceSize() const {
        return end - begin;
    }

    template<typename T>
    template<typename Cmp>
    BTreeNodeReference<T, Cmp> BulkSource<T>::build(SplitPolicyFactory *factory, int layer) const {
        BTreeNodeReference<T, Cmp> node(new BTreeNode<T, Cmp>(factory->order));
        const bulk::SplitPolicy policy = factory->create(sourceSize(), layer/*包含node*/);
        if (!policy.found()) {
            throw IllegalStateException("not find bulk build policy!");
        }
        node->resize(policy.nodeSize);
        if (policy.layer == 1) { // leaf
            // 递归出口
            for (int i = 0; i < policy.nodeSize; ++i) {
                node->setData(i, BTreeData<T>(*(begin + i)));
            }
            return node;
        }
        int childLayer = policy.layer - 1; // for children
        SplitPolicyFactory *childFactory = factory->childFactory();
        BulkIterator<T> childBegin = begin;
        for (int i = 0; i < policy.nodeSize; ++i) {
            int limit = policy.smallerChildSize + (i < policy.biggerChildrenCount ? 1 /*bigger*/: 0);
            const BulkIterator<T> &childEnd = childBegin + limit;
            node->setChild(i, BulkSource<T>(childBegin, childEnd).build<Cmp>(childFactory, childLayer));
            node->setData(i, BTreeData<T>(*(childEnd)));
            childBegin = childEnd + 1; // 1 for parent
        }
        node->setChild(policy.nodeSize, BulkSource<T>(childBegin, end).build<Cmp>(childFactory, childLayer));
        return node;
    }
}
#endif //ALGORITHM_BTREE_BULK_SOURCE_IMPL_H
