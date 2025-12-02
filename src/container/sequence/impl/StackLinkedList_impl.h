#ifndef ALGORITHM_STACK_LINKED_LIST_IMPL_H
#define ALGORITHM_STACK_LINKED_LIST_IMPL_H

#include "../../../lang/exception/IllegalStateException.h"


template<class T>
StackLinkedList<T>::StackLinkedList() : head(new StackLinkedNode<T>()), size(0) {}


template<class T>
void StackLinkedList<T>::pushFront(const T &value) const {
    StackLinkedNode<T> *node = new StackLinkedNode<T>(value, head->next);
    head->next = node;
    size++;
}

template<class T>
void StackLinkedList<T>::popFront() const {
    if (this->empty()) {
        return;
    }
    StackLinkedNode<T> *node = head->next;
    if (node == nullptr) {
        return;
    }
    head->next = node->next;
    delete node;
    size--;
}

template<class T>
T &StackLinkedList<T>::front() const {
    if (this->empty()) {
        throw IllegalStateException("Stack link list is empty");
    }
    return head->next->getValue();
}

template<class T>
void StackLinkedList<T>::clear() {
    StackLinkedNode<T> *node = head->next;
    while (node != nullptr) {
        StackLinkedNode<T> *next = node->next;
        delete node;
        node = next;
    }
    size = 0;
    head->next = nullptr;
}

template<class T>
StackLinkedList<T>::~StackLinkedList() {
    this->clear();
    delete head;
}

template<class T>
int StackLinkedList<T>::getSize() const {
    return size;
}

template<class T>
bool StackLinkedList<T>::empty() const {
    return size == 0;
}

template<class T>
StackLinkedList<T>::StackLinkedList(const StackLinkedList &list) :StackLinkedList() {
    this->size = list.size;
    if (this->size == 0) {
        return;
    }
    StackLinkedNode<T> *node = list.head->next;
    StackLinkedNode<T> *pre = this->head;
    while (node != nullptr) {
        StackLinkedNode<T> *target = new StackLinkedNode<T>(*node);
        pre->next = target;
        pre = target;
        node = node->next;
    }
    pre->next = nullptr;
}

template<class T>
void StackLinkedList<T>::forEach(const Function<T &, bool> &task) const {
    StackLinkedList<T> temp;
    while (!this->empty()) {
        T top = this->front();
        this->popFront();
        if (!task(top)) {
            break;
        }
        temp.pushFront(top);
    }

    while (!temp.empty()) {
        T top = temp.front();
        temp.popFront();
        this->pushFront(top);
    }
}

#endif //ALGORITHM_STACK_LINKED_LIST_IMPL_H
