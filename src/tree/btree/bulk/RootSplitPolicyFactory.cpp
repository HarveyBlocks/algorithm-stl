//
// Created by Lenovo on 2025/12/7.
//
#include "RootSplitPolicyFactory.h"

namespace harvey::algorithm::tree::btree::bulk {
    RootSplitPolicyFactory::RootSplitPolicyFactory(int order) : SplitPolicyFactory(order) {}

    int RootSplitPolicyFactory::getLayer(int sourceSize, int layer) const {
        // child layer
        int sourceForChild = sourceSize - order + 1;
        int childrenCount = order;
        for (layer = 1; maxOn(layer) * childrenCount < sourceForChild; layer++);
        // 此时的layer是完全可以hold住sourceForChild的
        return layer;
    }

    SplitPolicy RootSplitPolicyFactory::create(int sourceSize, int layer) {
        return this->SplitPolicyFactory::create(sourceSize, layer, 1);
    }

    SplitPolicyFactory *RootSplitPolicyFactory::childFactory() {
        if (_childFactory == nullptr) {
            _childFactory = new NodeSplitPolicyFactory(order); // init
        }
        return _childFactory;
    }

    RootSplitPolicyFactory::~RootSplitPolicyFactory() {
        delete _childFactory;
    }

};