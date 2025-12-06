//
// Created by Lenovo on 2025/12/7.
//

#ifndef ALGORITHM_BTREE_BULK_ROOT_SPLIT_POLICY_FACTORY_H
#define ALGORITHM_BTREE_BULK_ROOT_SPLIT_POLICY_FACTORY_H

#include "NodeSplitPolicyFactory.h"

namespace harvey::algorithm::tree::btree::bulk {
    class RootSplitPolicyFactory : public SplitPolicyFactory {
    private:
        NodeSplitPolicyFactory *_childFactory = nullptr;
    public:
        explicit RootSplitPolicyFactory(int order);

        [[nodiscard]] int getLayer(int sourceSize, int layer) const override;

         SplitPolicy create(int sourceSize, int layer) override;


        SplitPolicyFactory *childFactory() override;

        ~RootSplitPolicyFactory() override;
    };
}

#endif //ALGORITHM_BTREE_BULK_ROOT_SPLIT_POLICY_FACTORY_H
