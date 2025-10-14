/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/25
 *
 */
#ifndef ALGORITHM_STACK_LINKED_NODE_H
#define ALGORITHM_STACK_LINKED_NODE_H

#include "impl/DoublyLinkedList_impl.h"

template<class T>
struct StackLinkedNode {
    T *value;
    StackLinkedNode<T> *next;

    StackLinkedNode(const T &value, StackLinkedNode<T> *next);

    StackLinkedNode(const StackLinkedNode<T> &node);

    explicit StackLinkedNode();

    virtual ~StackLinkedNode<T>();

    T &getValue();

};

template<class T>
T &StackLinkedNode<T>::getValue() {
    if (value == nullptr) {
        throw NullPointException();
    }
    return *value;
}

template<class T>
StackLinkedNode<T>::StackLinkedNode(const T &value, StackLinkedNode<T> *next) : value(new T(value)), next(next) {}

template<class T>
StackLinkedNode<T>::StackLinkedNode(const StackLinkedNode<T> &node) :StackLinkedNode<T>(*node.value, node.next) {
}

template<class T>
StackLinkedNode<T>::StackLinkedNode() : value(nullptr), next(nullptr) {}

template<class T>
StackLinkedNode<T>::~StackLinkedNode() {
    delete value;
}

#endif //ALGORITHM_STACK_LINKED_NODE_H
