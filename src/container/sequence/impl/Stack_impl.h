#ifndef ALGORITHM_STACK_IMPL_H
#define ALGORITHM_STACK_IMPL_H

#include "../../../lang/exception/IllegalStateException.h"
#include "../Stack.h"

template<class T>
int Stack<T>::getSize() const {
    return linkList.getSize();
}

template<class T>
bool Stack<T>::empty() const {
    return linkList.empty();
}

template<class T>
T Stack<T>::top() const {
    if (this->empty()) {
        throw IllegalStateException();
    }
    return linkList.front();
}

template<class T>
T Stack<T>::pop() {
    T top = this->top();
    this->linkList.popFront();
    return top;
}

template<class T>
void Stack<T>::push(const T &element) {
    this->linkList.pushFront(element);
}

template<class T>
Stack<T> Stack<T>::sort(Array<T> &array) {
    if (array.getSize() <= 1) {
        return array;
    }
    Stack<T> originSt;
    Stack<T> resultSt;
    int pre = array[0];
    originSt.push(pre);
    for (int i = 1; i < array.getSize(); ++i) {
        T &element = array[i];
        originSt.push(element);
    }
    resultSt.push(originSt.pop());
    while (!originSt.empty()) {
        T top = resultSt.top();
        T element = originSt.pop();
        if (top < element) {
            int count = 0;
            while (!resultSt.empty()) {
                top = resultSt.top();
                if (top >= element) {
                    break;
                }
                originSt.push(resultSt.pop());
                count++;
            }
            resultSt.push(element);
            while (count-- > 0) {
                resultSt.push(originSt.pop());
            }
        } else {
            resultSt.push(element);
        }
    }
    return resultSt;
}

template<class T>
Array<T> &Stack<T>::moveToArray(Array<T> &array) {
    for (int i = 0; i < array.getSize(); ++i) {
        array[i] = this->pop();
    }
    return array;
}

template<class T>
void Stack<T>::clear() {
    linkList.clear();
}

#endif //ALGORITHM_STACK_IMPL_H
