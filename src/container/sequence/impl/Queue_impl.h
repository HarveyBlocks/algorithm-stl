/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/22
 *
 */
#ifndef ALGORITHM_QUEUE_IMPL_H
#define ALGORITHM_QUEUE_IMPL_H

#include "../Queue.h"

template<class T>
int Queue<T>::size() {
    return list.getSize();
}

template<class T>
bool Queue<T>::empty() const {
    return list.empty();
}


template<class T>
T Queue<T>::back() const {
    return list.back();
}

template<class T>
T Queue<T>::pop() {
    T front = list.front();
    list.popFront();
    return front;
}

template<class T>
T Queue<T>::front() const {
    return list.front();
}

template<class T>
void Queue<T>::push(const T &value) {
    list.pushBack(value);
}

#endif //ALGORITHM_QUEUE_IMPL_H
