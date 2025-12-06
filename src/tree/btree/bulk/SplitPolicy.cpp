//
// Created by Lenovo on 2025/12/7.
//
#include "SplitPolicy.h"

namespace harvey::algorithm::tree::btree::bulk {
    SplitPolicy::SplitPolicy() : SplitPolicy(0, 0, 0, 0) {}

    SplitPolicy::SplitPolicy(int layer, int nodeSize, int smallerChildSize, int biggerChildrenCount) :
            layer(layer), nodeSize(nodeSize), smallerChildSize(smallerChildSize),
            biggerChildrenCount(biggerChildrenCount) {}

    bool SplitPolicy::found() const {
        return layer != 0;
    }

    void SplitPolicy::update(const SplitPolicy &challenger) {
        // ok and better
        this->layer = challenger.layer;
        this->nodeSize = challenger.nodeSize;
        this->smallerChildSize = challenger.smallerChildSize;
        this->biggerChildrenCount = challenger.biggerChildrenCount;
    }

    bool SplitPolicy::ok(int childSizeMin, int childSizeMax) const {
        // 1. if(smaller) smaller >= child_min
        return (biggerChildrenCount == 0 ||
                childSizeMin <= smallerChildSize + 1 && smallerChildSize + 1 <= childSizeMax) &&
               // 2. if(bigger) bigger >= child_min
               childSizeMin <= smallerChildSize && smallerChildSize <= childSizeMax;
    }
}
