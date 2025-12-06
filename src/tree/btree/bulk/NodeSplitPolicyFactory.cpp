//
// Created by Lenovo on 2025/12/7.
//
#include "NodeSplitPolicyFactory.h"

namespace harvey::algorithm::tree::btree::bulk {
    NodeSplitPolicyFactory::NodeSplitPolicyFactory(int order) : SplitPolicyFactory(order), cache() {}

    int NodeSplitPolicyFactory::getLayer(int sourceSize, int layer) const {
        return layer - 1;
    }

    SplitPolicy NodeSplitPolicyFactory::create(int sourceSize, int layer) {
#ifndef CLOSE_BULK_POLICY_CACHE
        // 缓存增强
        int64 key = int64(sourceSize) << 32 | layer;
        const std::unordered_map<int64, SplitPolicy>::iterator &find = cache.find(key);
        if (find != cache.end()) {
            return find->second;
        }
#endif
        const SplitPolicy &policy = this->SplitPolicyFactory::create(sourceSize, layer, (order - 1) >> 1);
#ifndef CLOSE_BULK_POLICY_CACHE
        cache.insert({key, policy});
#endif
        return policy;
    }

    SplitPolicyFactory *NodeSplitPolicyFactory::childFactory() { return this; }

}