/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/25
 *
 */
#ifndef ALGORITHM_QUEUE_LINKED_NODE_H
#define ALGORITHM_QUEUE_LINKED_NODE_H

template<class T>
struct QueueLinkedNode {
    T *value;
    QueueLinkedNode *next;

    QueueLinkedNode(const T &value, QueueLinkedNode *next);

    explicit QueueLinkedNode();

    QueueLinkedNode(const QueueLinkedNode &node);

    virtual ~QueueLinkedNode();
};

template<class T>
QueueLinkedNode<T>::QueueLinkedNode(const T &value, QueueLinkedNode *next)
        : value(new T(value)), next(next) {

}

template<class T>
QueueLinkedNode<T>::QueueLinkedNode(const QueueLinkedNode &node) : QueueLinkedNode(*node.value, node.next) {}

template<class T>
QueueLinkedNode<T>::QueueLinkedNode() : value(nullptr), next(nullptr) {}

template<class T>
QueueLinkedNode<T>::~QueueLinkedNode() {
    delete value;
}

#endif //ALGORITHM_QUEUE_LINKED_NODE_H
