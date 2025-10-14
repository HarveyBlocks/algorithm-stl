/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/30
 *
 */
#ifndef ALGORITHM_TREAP_H
#define ALGORITHM_TREAP_H

#include "BinaryBalanceSearchTree.h"
#include "../util/Random.h"
#include "TreapNode.h"

template<class T>
class Treap : public BinaryBalanceSearchTree<T> {
public:
    BinaryTreeNode<T> * insertNode(Stack<BinaryTreeNode<T> *> &trace) override;

    /**
     * 通过旋转调整treap的结构, 使其满足Heap的性质
     * @return 还需要上升指针(函数内已完成)进行进一步处理则返回true;
     */
    bool treapInsertAdjustByRotation(Stack<BinaryTreeNode<T> *> &trace);

    void removeNode(Stack<BinaryTreeNode<T> *> &trace) override {
        this->BinarySearchTree<T>::removeNode(trace);
    }

    std::ostream &printPriority(std::ostream &os) const;

    static std::ostream &printPriority(std::ostream &os, BinaryTreeNode<T> *root);


    void split(BinaryTreeNode<T> *root, BinaryTreeNode<T> *targetNode) {
        if (targetNode == nullptr) {
            throw IllegalArgumentException();
        }
        if (root == nullptr) {
            return;
        }
        if (root->compareTo(targetNode) > 0) {
            // root大, 向右走
            split(root->getRight(), targetNode);
        } else {
            // root小, 向左走
            split(root->getLeft(), targetNode);
        }
    }

    /**
     * @param smallerTreeRoot Value更小的树, 其最大value小于biggerTree的最小value
     * @param biggerTreeRoot Value更小的树, 其最大value小于biggerTree的最小value
     * @return 不是nullptr的那个节点, 如果都是nullptr了, 就返回nullptr;
     */
    BinaryTreeNode<T> *merge(BinaryTreeNode<T> *smallerTreeRoot, BinaryTreeNode<T> *biggerTreeRoot) {
        if (biggerTreeRoot == nullptr && smallerTreeRoot == nullptr) {
            return nullptr;
        }
        if (biggerTreeRoot == nullptr) {
            return smallerTreeRoot;
        }
        if (smallerTreeRoot == nullptr) {
            return biggerTreeRoot;
        }
        // 小根树
        if (TreapNode<T>::getPriority(smallerTreeRoot) < TreapNode<T>::getPriority(biggerTreeRoot)) {
            // biggerTreeRoot在smallerTreeRoot的上方
            biggerTreeRoot->setLeft(merge(smallerTreeRoot, biggerTreeRoot->getLeft()));
            return biggerTreeRoot;
        } else {
            smallerTreeRoot->setRight(merge(smallerTreeRoot->getRight(), biggerTreeRoot));
            return smallerTreeRoot;
        }
    }


};

template<class T>
BinaryTreeNode<T> * Treap<T>::insertNode(Stack<BinaryTreeNode<T> *> &trace) {
    // 将节点调整为堆树的节点
    BinaryTreeNode<T> *newNode = trace.pop();
    if (newNode == nullptr) {
        return newNode;
    }
    auto *nodeAfterCast = new TreapNode<T>(newNode);
    trace.push(nodeAfterCast);
    delete newNode;
    this->BinarySearchTree<T>::insertNode(trace);
    while (treapInsertAdjustByRotation(trace));
    return nodeAfterCast;
}

template<class T>
bool Treap<T>::treapInsertAdjustByRotation(Stack<BinaryTreeNode<T> *> &trace) {
    BinaryTreeNode<T> *targetNode = trace.pop();
    // 调整, 小根堆, 根的优先级Priority是最小的
    if (trace.empty()) {
        // 只有一个节点
        return false;
    }
    BinaryTreeNode<T> *parentNode = trace.pop();
    bool leftChild = this->BinaryTree<T>::isLeftChild(targetNode, parentNode);
    // 使用旋转调整树的结构, 旋转不会改变中序遍历时的有序性
    if (!leftChild && TreapNode<T>::comparePriority(parentNode, parentNode->getRight()) > 0) {
        // 右子树更小, 让右子树旋转上来, 使用左旋
        this->BinaryBalanceSearchTree<T>::leftRotate(parentNode, trace.empty() ? nullptr : trace.top());
        trace.push(targetNode);
        return true;
    }
    if (leftChild && TreapNode<T>::comparePriority(parentNode, parentNode->getLeft()) > 0) {
        // 左子树更小, 让左子树旋转上来, 使用右旋
        this->BinaryBalanceSearchTree<T>::rightRotate(parentNode, trace.empty() ? nullptr : trace.top());
        trace.push(targetNode);
        return true;
    }
    // 旋转之后往更上一级
    return false;
}

template<class T>
std::ostream &Treap<T>::printPriority(std::ostream &os) const{
    return Treap<T>::printPriority(os, this->root);
}

template<class T>
std::ostream &Treap<T>::printPriority(std::ostream &os, BinaryTreeNode<T> *root) {
    return BinaryTree<T>::printNode(
            os, root, 1,
            [](std::ostream &os, BinaryTreeNode<int> *node) {
                os.operator<<((unsigned int) TreapNode<T>::getPriority(node));
            });
}


#endif //ALGORITHM_TREAP_H
