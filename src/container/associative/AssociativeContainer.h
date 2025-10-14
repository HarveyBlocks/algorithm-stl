/**
 * 关联容器, 指key-value关联
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/22
 *
 */
#ifndef ALGORITHM_ASSOCIATIVE_CONTAINER_H
#define ALGORITHM_ASSOCIATIVE_CONTAINER_H

#include "Entry.h"

template<class K, class V>
class AssociativeContainer : public Container<Entry<K, V>> {
public:
    virtual V &operator[](const K &index) const = 0;

    virtual void forEach(const BiFunction<K &, V &, bool> &task) const = 0;
};


#endif //ALGORITHM_ASSOCIATIVE_CONTAINER_H
