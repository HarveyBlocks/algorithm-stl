#ifndef ALGORITHM_STACK_H
#define ALGORITHM_STACK_H

#include "StackLinkedList.h"
#include "../../lang/Array.h"

template<class T>
class Stack {
private:
    StackLinkedList<T> linkList;
public:
    [[nodiscard]] bool empty() const;

    Stack() = default;

    Stack(const Stack<T> &stack) : linkList(stack.linkList) {
    }

    [[nodiscard]] int getSize() const;

    T top() const;

    T pop();

    void push(const T &element);

    void clear();

    static Stack<T> sort(Array<T> &array);

    Array<T> &moveToArray(Array<T> &array);

    Stack<T> &operator=(const Stack<T> &src);

    friend std::ostream &operator<<(std::ostream &os, Stack<T> &stack) {
        Stack<T> temp;
        os << "top: ";
        while (!stack.empty()) {
            T top = stack.pop();
            os << top << " ";
            temp.push(top);
        }
        os << '\n';
        while (!temp.empty()) {
            stack.push(temp.pop());
        }
        return os;
    }

    T &topRef();
};



#include "impl/Stack_impl.h"

#endif //ALGORITHM_STACK_H
