//
// Created by Lenovo on 2025/12/7.
//

#ifndef ALGORITHM_BTREE_BULK_SOURCE_IMPL_H
#define ALGORITHM_BTREE_BULK_SOURCE_IMPL_H

#include "BulkSource.h"

namespace harvey::algorithm::tree::btree::bulk {
    template<typename T>
    BulkSource<T>::BulkSource(
            const typename std::vector<T>::const_iterator &begin,
            const typename std::vector<T>::const_iterator &end) :
            begin(begin), end(end) {}

    template<typename T>
    template<typename Cmp>
    BTreeNodeReference<T, Cmp> BulkSource<T>::build(int order) const {// 判断, 调度
        if (sourceSize() == 0) {
            // empty, then return
            return BTreeNodeReference<T, Cmp>(new BTreeNode<T, Cmp>(order));
        }
        bulk::RootSplitPolicyFactory factory(order);
        BTreeNodeReference<T, Cmp> node = build<Cmp>(&factory, 1); // 这个layer是随便的, 因为对于root其不生效
        return node;
    }

    template<typename T>
    int BulkSource<T>::sourceSize() const {
        return end - begin;
    }

    template<typename T>
    template<typename Cmp>
    BTreeNodeReference<T, Cmp> BulkSource<T>::build(bulk::SplitPolicyFactory *factory, int layer) const {
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
        bulk::SplitPolicyFactory *childFactory = factory->childFactory();
        typename std::vector<T>::const_iterator childBegin = begin;
        for (int i = 0; i < policy.nodeSize; ++i) {
            int limit = policy.smallerChildSize + (i < policy.biggerChildrenCount ? 1 /*bigger*/: 0);
            auto childEnd = childBegin + limit;
            BTreeNodeReference<T, Cmp> child = BulkSource<T>(childBegin, childEnd)
                    .build<Cmp>(childFactory, childLayer);
            node->setChild(i, child);
            node->setData(i, BTreeData<T>(*(childEnd)));
            // 1 for parent
            childBegin = childEnd + 1;
        }
        BTreeNodeReference<T, Cmp> child = BulkSource<T>(childBegin, end).build<Cmp>(childFactory, childLayer);
        node->setChild(policy.nodeSize, child);
        return node;
    }
}
#endif //ALGORITHM_BTREE_BULK_SOURCE_IMPL_H
