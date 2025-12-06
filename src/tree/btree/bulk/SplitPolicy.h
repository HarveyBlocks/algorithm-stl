//
// Created by Lenovo on 2025/12/7.
//

#ifndef ALGORITHM_BTREE_BULK_SPLIT_POLICY_H
#define ALGORITHM_BTREE_BULK_SPLIT_POLICY_H

namespace harvey::algorithm::tree::btree::bulk {
    struct SplitPolicy {
        int layer;
        int nodeSize;
        /**
         * smallerChildSize = biggerChildSize - 1
         */
        int smallerChildSize;
        /**
         * biggerChildrenCount + smallerChildrenCount = nodeSize + 1
         * 0 <= smallerChildrenCount < nodeSize + 1
         */
        int biggerChildrenCount;

        SplitPolicy();

        SplitPolicy(int layer, int nodeSize, int smallerChildSize, int biggerChildrenCount);

        [[nodiscard]] bool found() const;

        void update(const SplitPolicy &challenger);

        [[nodiscard]] bool ok(int childSizeMin, int childSizeMax) const;
    };

}
#endif //ALGORITHM_BTREE_BULK_SPLIT_POLICY_H
