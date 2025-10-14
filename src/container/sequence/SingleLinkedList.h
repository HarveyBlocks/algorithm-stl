/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/24
 */
#ifndef ALGORITHM_SINGLE_LINK_LIST_H
#define ALGORITHM_SINGLE_LINK_LIST_H


#include "QueueLinkedList.h"
#include "../../lang/exception/IndexOutOfBoundException.h"
#include "../../lang/exception/NullPointException.h"
#include "../../util/sort/QuickSort.h"
#include "../../lang/String.h"

template<class T>
class SingleLinkedList : public QueueLinkedList<T> {
public:
    SingleLinkedList() = default;

    SingleLinkedList(const SingleLinkedList<T> &list) : QueueLinkedList<T>(list) {};

    void removeElement(const T &element) {
        QueueLinkedNode<T> *pre = this->head;
        QueueLinkedNode<T> *node = pre->next;
        while (node->next != nullptr) {
            if (element == *(node->value)) {
                pre->next = node->next;
                delete node;
                this->size--;
            } else {
                pre = pre->next;
            }
            node = pre->next;
        }
        if (element == *(node->value)) {
            this->tail->next = pre;
            pre->next = node->next;
            delete node;
            this->size--;
        }
    }

    void insert(int index, const T &element) {
        QueueLinkedNode<T> *node = this->head;
        int i = 0;
        for (; node->next != nullptr && i < index; ++i) {
            node = node->next;
        }
        if (node->next == nullptr) {
            if (i == this->size) {
                // 修改队尾
                auto *newNode = new QueueLinkedNode<T>(element, node->next);
                node->next = newNode;
                this->tail->next = newNode;
                this->size++;
            } else {
                throw IndexOutOfBoundException();
            }
        } else {
            auto *newNode = new QueueLinkedNode<T>(element, node->next);
            node->next = newNode;
            this->size++;
        }

    }

    void pushFront(const T &element) {
        this->insert(0, element);
    }

    T remove(int index) {
        QueueLinkedNode<T> *pre = this->head;
        QueueLinkedNode<T> *node = pre->next;
        int i = 0;
        for (; node != nullptr && i < index; ++i) {
            pre = pre->next;
            node = pre->next;
        }
        if (node == nullptr) {
            throw IndexOutOfBoundException();
        }
        if (index == this->size - 1) {
            // 删除最后一个节点, 需要移动尾指针
            this->tail->next = pre;
        }
        pre->next = node->next;
        T result = *(node->value);
        delete node;
        this->size--;
        if (this->size == 0) {
            this->tail->next = nullptr;
        }
        return result;
    }

    /**
     * @param task (pre,node)->break?, 不能把pre置为null, 不能删除pre;
     */
    void forEach(BiFunction<QueueLinkedNode<T> *, QueueLinkedNode<T> *, bool> task) {
        QueueLinkedNode<T> *pre = this->head;
        QueueLinkedNode<T> *node = pre->next;
        while (node->next != nullptr) {
            if (!task(pre, node)) {
                break;
            }
            if (pre == nullptr) {
                throw NullPointException();
            }
            pre = pre->next;
            node = pre->next;
        }
    }

    void forEach(const Function<T &, bool> &task) const {
        this->QueueLinkedList<T>::forEach(task);
    }

    /**
     *
     * @param cmp
     */
    void sort(const Compare<T> &cmp) {
        Array<T> temp(this->size);
        int i = 0;
        this->QueueLinkedList<T>::forEach([&temp, &i](T &value) {
            temp[i] = value;
            i++;
            return true;
        });
        Compare<T> cmp_fixed = [&cmp](const T &a, const T &b) {
            return -cmp(a, b);
        };

        QuickSort<T>(temp, cmp_fixed).sort();

        this->clear();
        int tempSize = temp.getSize();
        for (int j = 0; j < tempSize; ++j) {
            this->pushFront(temp[j]);
        }
    }

    const T &at(int index) const {
        if (index > this->size) {
            throw IndexOutOfBoundException();
        }
        QueueLinkedNode<T> *node = this->head->next;
        for (int i = 0; node != nullptr && i < index; i++) {
            node = node->next;
        }
        if (node == nullptr) {
            throw IndexOutOfBoundException();
        }
        if (node->value == nullptr) {
            throw NullPointException();
        }
        return *(node->value);
    }

    SingleLinkedList<T> &operator=(const SingleLinkedList<T> &list) {
        if (this == &list) {
            return *this;
        }
        this->QueueLinkedList<T>::operator=(list);
        return *this;
    }
};


#endif //ALGORITHM_SINGLE_LINK_LIST_H
