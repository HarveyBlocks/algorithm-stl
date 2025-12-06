//
// Created by Lenovo on 2025/12/7.
//

#ifndef ALGORITHM_BTREE_BULK_SOURCE_H
#define ALGORITHM_BTREE_BULK_SOURCE_H

#include <vector>
#include "RootSplitPolicyFactory.h"
#include "../BTreeDeclarations.h"
#include "../../../util/Comparator.h"

namespace harvey::algorithm::tree::btree::bulk {
    template<typename T>
    class BulkSource {
        typename std::vector<T>::const_iterator begin;
        typename std::vector<T>::const_iterator end;
    public:
        explicit BulkSource(
                const typename std::vector<T>::const_iterator &begin,
                const typename std::vector<T>::const_iterator &end);

        template<typename Cmp = Greater<T>>
        [[nodiscard]] BTreeNodeReference<T, Cmp> build(int order) const;

    private:

        [[nodiscard]] int sourceSize() const;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

        /**
         * 解开递归? <br>
         * 递归最深和树的深度一致, <br>
         * 树的深度最多30层左右(order=3, 千亿数据), 对于递归的压力来说还好吧?  <br>
         * 而且生产中, order一般在100左右, 数据量百万级就已经很多了, 这种情况下深度一般是不到10层的 <br>
         * 而且递归的速度比栈要稍微快一点
         */
        template<typename Cmp = Greater<T>>
        [[nodiscard]] BTreeNodeReference<T, Cmp> build(bulk::SplitPolicyFactory *factory, int layer) const;

#pragma clang diagnostic pop
    };
}
#include "BulkSource_impl.h"
#endif //ALGORITHM_BTREE_BULK_SOURCE_H
