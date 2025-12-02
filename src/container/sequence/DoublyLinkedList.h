/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/24
 *
 */
#ifndef ALGORITHM_DOUBLY_LINKED_LIST_H
#define ALGORITHM_DOUBLY_LINKED_LIST_H

#include "LinkedList.h"
#include "../../lang/exception/NullPointException.h"
#include "../../lang/exception/IllegalArgumentException.h"
#include "../../util/function/function.h"
#include <iostream>

template<class T>
struct DoublyLinkedNode {
    T *value;
    DoublyLinkedNode *pre;
    DoublyLinkedNode *post;

    DoublyLinkedNode(const T &value, DoublyLinkedNode *pre, DoublyLinkedNode *post) :
            value(new T(value)), pre(pre), post(post) {}

    DoublyLinkedNode() :
            value(nullptr), pre(nullptr), post(nullptr) {}

    DoublyLinkedNode(const DoublyLinkedNode<T> &node) :
            DoublyLinkedNode(*node.value, node.pre, node.post) {}

    ~DoublyLinkedNode() {
        delete value;
    }
};

template<class T>
class DoublyLinkedList : public LinkedList<T> {
private:
    mutable int size;
    // 哨兵
    DoublyLinkedNode<T> *head;
    // 哨兵
    DoublyLinkedNode<T> *tail;

    void initList() const;

public:
    DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList<T> &list);

    void clear();

    virtual ~DoublyLinkedList();

    [[nodiscard]] int getSize() const override;

    [[nodiscard]] bool empty() const override;

    T &front() const override;

    DoublyLinkedNode<T> *frontNode() const;

    DoublyLinkedNode<T> *backNode() const;

    void popFront() const override;

    void pushFront(const T &value);

    void pushBack(const T &value);

    void popBack() const;

    void remove(DoublyLinkedNode<T> *node) const;

    void insert(DoublyLinkedNode<T> *node, const T &value, bool nodeAtPre = true) const;

    /**
     * @param task (pre,node)->break?, 不能把pre置为null, 不能删除pre;
     */
    void forEach(Function<DoublyLinkedNode<T> *, bool> task, bool reverse = false) const;

    void forEach(const Function<T &, bool> &task) const override;

    void forEachReverse(const Function<T &, bool> &task) const;

    /**
     * 是端点, 指node的pre为head或post为tail, 当然, 参数必须来自该链表, 否则本方法不会进行检查
     * @return
     */
    bool isEndpoint(DoublyLinkedNode<T> *node) const {
        if (node == nullptr) {
            throw NullPointException();
        }
        if (node->pre == nullptr || node->post == nullptr) {
            throw IllegalArgumentException();
        }
        return node->pre == head || node->post == tail;
    }

    /**
    * 是哨兵, 指node为head或tail, 当然, 参数必须来自该链表, 否则本方法不会进行检查
    * @return
    */
    bool isSentinel(DoublyLinkedNode<T> *node) const {
        if (node == nullptr) {
            throw NullPointException();
        }
        return node == head || node == tail;
    }

};


#include "impl/DoublyLinkedList_impl.h"


#endif //ALGORITHM_DOUBLY_LINKED_LIST_H
