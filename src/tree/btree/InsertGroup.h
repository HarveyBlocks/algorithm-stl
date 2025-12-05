//
// Created by Lenovo on 2025/12/5.
//

#ifndef ALGORITHM_INSERT_GROUP_H
#define ALGORITHM_INSERT_GROUP_H

#include "BTreeDeclarations.h"

namespace harvey::algorithm::tree::btree {
    template<typename T, typename Cmp>
    struct InsertGroup {
        BTreeData<T> data;
        BTreeNodeReference<T, Cmp> left;
        BTreeNodeReference<T, Cmp> right;

        explicit InsertGroup(const T& data);
    };

    template<typename T, typename Cmp>
    InsertGroup<T, Cmp>::InsertGroup(const T& data) : data(new T(data)), left(nullptr),
                                                          right(BTreeNodeReference<T, Cmp>(nullptr)) {}
}
#endif //ALGORITHM_INSERT_GROUP_H
