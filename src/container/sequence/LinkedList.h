/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/22
 *
 */
#ifndef ALGORITHM_LINKED_LIST_H
#define ALGORITHM_LINKED_LIST_H

#include <ostream>
#include "../Container.h"
#include "../../util/function/function.h"

template<class T>
class LinkedList : public Container<T> {
public:
    [[nodiscard]] virtual int getSize() const = 0;

    [[nodiscard]] virtual bool empty() const = 0;

    virtual T &front() const = 0;

    virtual void popFront() const = 0;


    /**
     * @param task 返回false, 就终止遍历
     */
    virtual void forEach(const Function<T &, bool>& task) const = 0;

    friend std::ostream &operator<<(std::ostream &os, const LinkedList<T> &obj) {
        obj.forEach([&os](T &value) {
            os << value << "->";
            return true;
        });
        return os << "null";
    }

};

#endif //ALGORITHM_LINKED_LIST_H
