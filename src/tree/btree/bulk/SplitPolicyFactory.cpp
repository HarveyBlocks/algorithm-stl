//
// Created by Lenovo on 2025/12/7.
//
#include "SplitPolicyFactory.h"

namespace harvey::algorithm::tree::btree::bulk {

    int SplitPolicyFactory::power(int a, int b) {
        int res = 1;
        for (int i = 0; i < b; i++) res *= a;
        return res;
    }

    int SplitPolicyFactory::maxOn(int layer) const {
        return power(order, layer) - 1;
    }

    int SplitPolicyFactory::minOn(int layer) const {
        int lb = (order - 1) >> 1;
        return power(lb + 1, layer) - 1;
    }

    SplitPolicy SplitPolicyFactory::create(int sourceSize, int layer, int lowerBound) const {
        if (sourceSize < lowerBound) {
            return {};
        }
        if (sourceSize < order) {// leaf
            return {1, sourceSize, 0, 0};
        }
        layer = getLayer(sourceSize, layer);
        int childMin = minOn(layer);
        int childMax = maxOn(layer);
        SplitPolicy policy;
        for (int nodeSize = order - 1; nodeSize >= lowerBound; --nodeSize) {
            int sourceForChild = sourceSize - nodeSize;
            int childrenCount = nodeSize + 1;
            if (policy.found() && childMax * childrenCount < sourceForChild) {
                // 已经溢出
                break;
            }
            int biggerChildrenCount = sourceForChild % childrenCount;
            int smallerChildSize = (sourceForChild - biggerChildrenCount) / childrenCount;
            SplitPolicy challenger(layer + 1, nodeSize, smallerChildSize, biggerChildrenCount);
            if (challenger.ok(childMin, childMax)) {
                policy.update(challenger);
            }
        }
        return policy;
    }

    SplitPolicyFactory::SplitPolicyFactory(int order) : order(order) {}
}