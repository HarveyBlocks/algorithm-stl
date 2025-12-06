//
// Created by Lenovo on 2025/12/7.
//

#ifndef ALGORITHM_BTREE_BULK_SPLIT_POLICY_FACTORY_H
#define ALGORITHM_BTREE_BULK_SPLIT_POLICY_FACTORY_H

#include "SplitPolicy.h"

namespace harvey::algorithm::tree::btree::bulk {
    class SplitPolicyFactory {
    public:
        const int order;
    private:
        static int power(int a, int b);

    protected:
        [[nodiscard]] int maxOn(int layer) const;

        [[nodiscard]] int minOn(int layer) const;

        [[nodiscard]]  SplitPolicy create(int sourceSize, int layer, int lowerBound) const;

        [[nodiscard]] virtual int getLayer(int sourceSize, int layer) const = 0;

    public:

        explicit SplitPolicyFactory(int order);

        /**
         * 1. 让size尽可能大, 这样layer就会尽可能小 <br>
         * 2. size=order-1, 取得理论layer最小值 <br>
         * 3. size--, 这样layer就会逐渐丰满 <br>
         * @param sourceSize
         * @param layer 包含node
         * @return
         */
        [[nodiscard]] virtual SplitPolicy create(int sourceSize, int layer) = 0;

        virtual SplitPolicyFactory *childFactory() = 0;

        virtual ~SplitPolicyFactory() = default;
    };
}

#endif //ALGORITHM_BTREE_BULK_SPLIT_POLICY_FACTORY_H
