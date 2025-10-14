/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/30
 *
 */
#ifndef ALGORITHM_TREAP_NODE_H
#define ALGORITHM_TREAP_NODE_H

template<class T>
class TreapNode : public BinaryTreeNode<T> {
private:
    unsigned int priority{};
protected:
    TreapNode();

public:

    /**
     * @deprecated
     */
    explicit TreapNode(const T &value);

    explicit TreapNode(
            const BinaryTreeNode<T> *node);

    [[nodiscard]] int getPriority() const;

    static TreapNode<T> *cast(BinaryTreeNode<T> *obj);

    static int getPriority(BinaryTreeNode<T> *obj);

    static int comparePriority(BinaryTreeNode<T> *node1, BinaryTreeNode<T> *node2);
};

template<class T>
TreapNode<T>::TreapNode() : BinaryTreeNode<T>(), priority(Random::unsignedInt() % 10) {}

template<class T>
TreapNode<T>::TreapNode(const T &value) : BinaryTreeNode<T>(value), priority(Random::unsignedInt() % 10) {}

template<class T>
TreapNode<T>::TreapNode(const BinaryTreeNode<T> *node) : TreapNode() {
    if (node == nullptr) {
        return;
    }
    this->setValue(node->getValue());
    this->setLeft(node->getLeft());
    this->setRight(node->getRight());
}

template<class T>
int TreapNode<T>::getPriority() const {
    return priority;
}

template<class T>
TreapNode<T> *TreapNode<T>::cast(BinaryTreeNode<T> *obj) {
    return dynamic_cast<TreapNode<T> *>(obj);
}

template<class T>
int TreapNode<T>::getPriority(BinaryTreeNode<T> *obj) {
    TreapNode<T> *pNode = cast(obj);
    return pNode->getPriority();
}

template<class T>
int TreapNode<T>::comparePriority(BinaryTreeNode<T> *node1, BinaryTreeNode<T> *node2) {
    int p1 = getPriority(node1);
    int p2 = getPriority(node2);
    return p1 == p2 ? 0 : (p1 > p2 ? 1 : -1);
}

#endif //ALGORITHM_TREAP_NODE_H
