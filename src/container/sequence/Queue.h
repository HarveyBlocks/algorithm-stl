/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/22
 *
 */
#ifndef ALGORITHM_QUEUE_H
#define ALGORITHM_QUEUE_H

#include "QueueLinkedList.h"

template<class T>
class Queue {
private:
    QueueLinkedList<T> list;
public:
    Queue() = default;

    void push(const T &value);

    T pop();

    T front() const;

    T back() const;

    T popThenPush() const {
        const T front = list.front();
        list.popFront();
        list.pushBack(front);
        return front;
    }

    int size();

    [[nodiscard]] bool empty() const;

    void clear() {
        while (!this->empty()) {
            this->pop();
        }
    }

    [[nodiscard]] int getSize() const {
        return list.getSize();
    }
};


#include "impl/Queue_impl.h"

#endif //ALGORITHM_QUEUE_H
