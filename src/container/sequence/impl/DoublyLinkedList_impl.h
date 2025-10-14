/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/25
 *
 */
#ifndef ALGORITHM_DOUBLY_LINKED_LIST_IMPL_H
#define ALGORITHM_DOUBLY_LINKED_LIST_IMPL_H

#include "../DoublyLinkedList.h"
#include "../../../lang/exception/IllegalStateException.h"

template<class T>
void DoublyLinkedList<T>::initList() const {
    head->pre = tail;
    head->post = tail;
    tail->pre = head;
    tail->post = head;
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList() :
        size(0), head(new DoublyLinkedNode<T>()), tail(new DoublyLinkedNode<T>()) {
    initList();
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &list) : DoublyLinkedList() {
    DoublyLinkedNode<T> *node = this->head;
    list.forEachReverse([this, &node](T &value) {
        this->insert(node, value);
        return true;
    });
}

template<class T>
void DoublyLinkedList<T>::clear() {
    this->forEach([this](DoublyLinkedNode<T> *node) {
        /* delete node;*/
        this->remove(node);
        return true;
    });
    initList();
    this->size = 0;
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
    delete head;
    delete tail;
}

template<class T>
int DoublyLinkedList<T>::getSize() const {
    return size;
}

template<class T>
bool DoublyLinkedList<T>::empty() const {
    return size == 0 || head == nullptr || tail == nullptr;
}

template<class T>
T &DoublyLinkedList<T>::front() const {
    DoublyLinkedNode<T> *node = head->post;
    if (node == tail) {
        throw IllegalStateException();
    }
    return *(node->value);
}

template<class T>
DoublyLinkedNode<T> *DoublyLinkedList<T>::backNode() const {
    DoublyLinkedNode<T> *node = tail->pre;
    if (node == head) {
        throw IllegalStateException();
    }
    return node;
}

template<class T>
DoublyLinkedNode<T> *DoublyLinkedList<T>::frontNode() const {
    DoublyLinkedNode<T> *node = head->post;
    if (node == tail) {
        throw IllegalStateException();
    }
    return node;
}


template<class T>
void DoublyLinkedList<T>::popFront() const {
    DoublyLinkedNode<T> *node = head->post;
    if (node == tail) {
        return;
    }
    remove(node);
}

template<class T>
void DoublyLinkedList<T>::pushFront(const T &value) {
    insert(head, value);
}

template<class T>
void DoublyLinkedList<T>::pushBack(const T &value) {
    insert(tail, value, false);
}

template<class T>
void DoublyLinkedList<T>::popBack() const {
    DoublyLinkedNode<T> *node = tail->pre;
    if (node == head) {
        return;
    }
    remove(node);
}

template<class T>
void DoublyLinkedList<T>::remove(DoublyLinkedNode<T> *node) const {
    node->post->pre = node->pre;
    node->pre->post = node->post;
    delete node;
    size--;
}

template<class T>
void DoublyLinkedList<T>::insert(DoublyLinkedNode<T> *node, const T &value, bool nodeAtPre) const {
    auto *newNode = new DoublyLinkedNode<T>(value, nullptr, nullptr);
    if (nodeAtPre) {
        newNode->pre = node;
        newNode->post = node->post;
        node->post->pre = newNode;
        node->post = newNode;
    } else {
        newNode->post = node;
        newNode->pre = node->pre;
        node->pre->post = newNode;
        node->pre = newNode;
    }
    size++;
}

template<class T>
void DoublyLinkedList<T>::forEach(const Function<DoublyLinkedNode<T> *, bool> task, bool reverse) const {
    DoublyLinkedNode<T> *start = reverse ? this->tail : this->head;
    DoublyLinkedNode<T> *end = reverse ? this->head : this->tail;
    DoublyLinkedNode<T> *node = reverse ? start->pre : start->post;
    while (node != end) {
        DoublyLinkedNode<T> *next = reverse ? node->pre : node->post;
        if (!task(node)) {
            break;
        }
        if (node == nullptr) {
            throw NullPointException();
        }
        node = next;
    }
}

template<class T>
void DoublyLinkedList<T>::forEach(const Function<T &, bool> &task) const {
    this->forEach([&task](DoublyLinkedNode<T> *node) {
        return task(*(node->value));
    });
}

template<class T>
void DoublyLinkedList<T>::forEachReverse(const Function<T &, bool> &task) const {
    this->forEach([&task](DoublyLinkedNode<T> *node) {
        return task(*(node->value));
    }, true);
}

#endif //ALGORITHM_DOUBLY_LINKED_LIST_IMPL_H
