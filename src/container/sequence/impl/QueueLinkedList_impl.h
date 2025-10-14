/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/22
 *
 */
#ifndef ALGORITHM_QUEUE_LINKED_LIST_IMPL_H
#define ALGORITHM_QUEUE_LINKED_LIST_IMPL_H

#include "../QueueLinkedList.h"

template<class T>
QueueLinkedList<T>::QueueLinkedList() : head(new QueueLinkedNode<T>()), size(0), tail(new QueueLinkedNode<T>()) {}

template<class T>
QueueLinkedList<T>::QueueLinkedList(const QueueLinkedList &list):QueueLinkedList() {
    this->operator=(list);
}


template<class T>
QueueLinkedList<T> &QueueLinkedList<T>::operator=(const QueueLinkedList<T> &list) {
    if (this == &list) {
        return *this;
    }
    this->clear();
    this->size = list.size;
    if (this->size == 0) {
        return *this;
    }
    QueueLinkedNode<T> *node = list.head->next;
    QueueLinkedNode<T> *pre = this->head;
    while (node != nullptr) {
        QueueLinkedNode<T> *target = new QueueLinkedNode(*node);
        pre->next = target;
        pre = target;
        node = node->next;
    }
    tail->next = pre;
    pre->next = nullptr;
    return *this;
}

template<class T>
void QueueLinkedList<T>::pushBack(const T &value) const {
    auto *node = new QueueLinkedNode<T>(value, nullptr);
    if (tail->next == nullptr) {
        head->next = node;
        tail->next = head->next;
    } else {
        tail->next->next = node;
        tail->next = node;
    }
    size++;
}

template<class T>
void QueueLinkedList<T>::popFront() const {
    if (this->empty()) {
        return;
    }
    QueueLinkedNode<T> *node = head->next;
    if (node == nullptr) {
        return;
    }
    head->next = node->next;
    delete node;
    size--;
    if (size == 0) {
        tail->next = nullptr;
    }
}

template<class T>
T &QueueLinkedList<T>::front() const {
    return *(frontNode()->value);
}

template<class T>
T &QueueLinkedList<T>::back() const {
    return *(backNode()->value);
}

template<class T>
QueueLinkedNode<T> *QueueLinkedList<T>::frontNode() const {
    if (this->empty()) {
        throw IllegalStateException("Stack link list is empty");
    }
    return head->next;
}

template<class T>
QueueLinkedNode<T> *QueueLinkedList<T>::backNode() const {
    if (this->empty()) {
        throw IllegalStateException("Stack link list is empty");
    }
    return tail->next;
}

template<class T>
void QueueLinkedList<T>::clear() {
    QueueLinkedNode<T> *node = head->next;
    while (node != nullptr) {
        QueueLinkedNode<T> *next = node->next;
        delete node;
        size--;
        node = next;
    }
    head->next = nullptr;
    tail->next = nullptr;
}

template<class T>
QueueLinkedList<T>::~QueueLinkedList() {
    this->clear();
    delete head;
    delete tail;
}

template<class T>
int QueueLinkedList<T>::getSize() const {
    return size;
}

template<class T>
bool QueueLinkedList<T>::empty() const {
    return size == 0 || head == nullptr || tail == nullptr;
}

template<class T>
void QueueLinkedList<T>::forEach(const Function<T &, bool> &task) const {
    QueueLinkedNode<T> *node = head->next;
    while (node != nullptr) {
        if (!task(*(node->value))) {
            break;
        }
        node = node->next;
    }
}


#endif //ALGORITHM_QUEUE_LINKED_LIST_IMPL_H
