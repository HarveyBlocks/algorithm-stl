#ifndef ALGORITHM_STACK_LINKED_LIST_H
#define ALGORITHM_STACK_LINKED_LIST_H

#include "LinkedList.h"

#include "StackLinkedNode.h"

template<class T>
class StackLinkedList : public LinkedList<T> {
private:

    StackLinkedNode<T> *head;
    mutable int size;
public:
    StackLinkedList();

    StackLinkedList(const StackLinkedList<T> &list);

    void pushFront(const T &value) const;

    void popFront() const override;

    T &front() const override;

    void clear();

    ~StackLinkedList();

    StackLinkedList<T> &operator=(const StackLinkedList<T> &src);

    [[nodiscard]] int getSize() const override;

    [[nodiscard]] bool empty() const override;

    void forEach(const Function<T &, bool> &task) const override;
};
#include "impl/StackLinkedList_impl.h"

#endif //ALGORITHM_STACK_LINKED_LIST_H
