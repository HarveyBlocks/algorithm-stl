//
// Created by Lenovo on 2025/12/7.
//

#ifndef ALGORITHM_BTREE_BULK_NODE_SPLIT_POLICY_FACTORY_H
#define ALGORITHM_BTREE_BULK_NODE_SPLIT_POLICY_FACTORY_H

#include "SplitPolicyFactory.h"

#ifndef CLOSE_BULK_POLICY_CACHE

#include "../../../util/type.h"
#include <unordered_map>

#endif

namespace harvey::algorithm::tree::btree::bulk {
    /**
     * 要求layer, 就一定是layer!
     */
    class NodeSplitPolicyFactory : public SplitPolicyFactory {
    private:
#ifndef CLOSE_BULK_POLICY_CACHE
        std::unordered_map<int64, SplitPolicy> cache;
#endif
    public:
        explicit NodeSplitPolicyFactory(int order);

        [[nodiscard]] int getLayer(int sourceSize, int layer) const override;

        SplitPolicy create(int sourceSize, int layer) override;

        SplitPolicyFactory *childFactory() override;
    };
}

#endif //ALGORITHM_BTREE_BULK_NODE_SPLIT_POLICY_FACTORY_H
