//
// Created by Lenovo on 2025/12/2.
//

#ifndef ALGORITHM_B_TREE_H
#define ALGORITHM_B_TREE_H

#include "BTreeData.h"
#include "InsertGroup.h"
#include "BTreeReference.h"
#include "BTreeNode.h"
#include "BTreeElement.h"
#include "BTreeDeclarations.h"

#define BULK

#ifdef DEBUG

#include <iostream>

#endif
#ifdef BULK

#include <vector>
#include <stack>

#endif

namespace harvey::algorithm::tree::btree {

    namespace bulk {
        template<typename T>
        class BulkSource;
    }
    template<typename T, typename Cmp>
    class BTree {
    private:
        BTreeNodeReference<T, Cmp> root;
        // n 级 B 树...
        int order;
        Cmp cmp;

        friend class BTreeNode<T, Cmp>;

    public:
        explicit BTree(int order, const Cmp &cmp = Cmp());

        ~BTree();

        void clear();


        [[nodiscard]] BTreeTrace<T, Cmp> search(const T &value) const;

        void insert(const T &data);

        // remove, 是删除一个, 还是删除多个? 依据trace去删除, 倒是可以
        void remove(BTreeTrace<T, Cmp> &trace);

        bool empty();

#ifdef DEBUG

        double calRate() const;

        void showBTree(std::ostream &os = std::cout) const;

        int qualified() const {
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
#ifdef BULK


        /**
         *
         * @return
         */
        BTree &bulk(const bulk::BulkSource<T> &sorted);

#endif


    private:
        [[nodiscard]] BTreeNodeReference<T, Cmp> instanceNode() const;

        /**
         * @param trace 其index总是指向child_index
         */
        void insertLeaf(const T &data, BTreeTrace<T, Cmp> &trace);


        void removeLeaf(BTreeTrace<T, Cmp> &trace, BTreeNodeReference<T, Cmp> cur);
    };

}

#include "impl/BTree_impl.h"

#endif //ALGORITHM_B_TREE_H
