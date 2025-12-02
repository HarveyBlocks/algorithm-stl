/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/22
 *
 */
#ifndef ALGORITHM_QUEUE_LINKED_LIST_H
#define ALGORITHM_QUEUE_LINKED_LIST_H

#include "../../lang/exception/IllegalStateException.h"
#include "LinkedList.h"
#include "../../util/function/function.h"
#include "../../lang/exception/NullPointException.h"
#include "QueueLinkedNode.h"

/**
 * next==null 用于标记为最后的节点
 * @tparam T
 */
template<class T>
class QueueLinkedList : public LinkedList<T> {
protected:
    void headPointTo(QueueLinkedNode<T> *next) {
        head->next = next;
    }

    // 指向最后的节点, 不存有价值的值
    QueueLinkedNode<T> *tail;
    // 指向第一个节点, 不存有价值的值
    QueueLinkedNode<T> *head;
    mutable int size;
public:
    QueueLinkedList();

    QueueLinkedList(const QueueLinkedList &list);

    void pushBack(const T &value) const;

    void popFront() const;

    T &front() const;

    T &back() const;

    QueueLinkedNode<T> *frontNode() const;

    QueueLinkedNode<T> *backNode() const;

    void clear();

    virtual ~QueueLinkedList();

    [[nodiscard]] int getSize() const;

    [[nodiscard]] bool empty() const;

    /**
     * @param task 返回false, 就终止遍历
     */
    void forEach(const Function<T &, bool> &task) const;

    QueueLinkedList<T> &operator=(const QueueLinkedList<T> &list);
};


#include "impl/QueueLinkedList_impl.h"

#endif //ALGORITHM_QUEUE_LINKED_LIST_H
