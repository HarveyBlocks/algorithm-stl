/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/22
 *
 */
#ifndef ALGORITHM_TREE_TRAVERSAL_IMPL_H
#define ALGORITHM_TREE_TRAVERSAL_IMPL_H

#include "../TraversalOrder.h"

template<class T>
DoubleBranchedTraversalOrder<T>::DoubleBranchedTraversalOrder(BiConsumer<Stack<BinaryTreeNode<T> *> &,  BinaryTreeNode<T> *> order)
        :BiConsumer<Stack<BinaryTreeNode<T> *> &, BinaryTreeNode<T> *>(order) {}

template<class T>
DoubleBranchedTraversalOrder<T> DoubleBranchedTraversalOrder<T>::choose(tree::TreeTraversalWay way) {
    switch (way) {
        case tree::TreeTraversalWay::LRM:
            return DoubleBranchedTraversalOrder<T>::createLrm();
        case tree::TreeTraversalWay::LMR:
            return DoubleBranchedTraversalOrder<T>::createLmr();
        case tree::TreeTraversalWay::MLR:
            return DoubleBranchedTraversalOrder<T>::createMlr();
        case tree::TreeTraversalWay::RLM:
            return DoubleBranchedTraversalOrder<T>::createRlm();
        case tree::TreeTraversalWay::RML:
            return DoubleBranchedTraversalOrder<T>::createRml();
        case tree::TreeTraversalWay::MRL:
            return DoubleBranchedTraversalOrder<T>::createMrl();
        default:
            throw IllegalArgumentException();
    }
}


template<class T>
void DoubleBranchedTraversalOrder<T>::traversalRoot(Stack<BinaryTreeNode<T> *> &st,  BinaryTreeNode<T> *root) {
    st.push(root);                          // 添加中节点
    st.push(nullptr); // 中节点访问过，但是还没有处理，加入空节点做为标记。
}

template<class T>
void DoubleBranchedTraversalOrder<T>::traversalBranch(Stack<BinaryTreeNode<T> *> &st, BinaryTreeNode<T> *branch) {
    if (branch) {
        st.push(branch);    // 添加左节点（空节点不入栈）
    }
}

template<class T>
DoubleBranchedTraversalOrder<T> DoubleBranchedTraversalOrder<T>::createMrl() {
    return DoubleBranchedTraversalOrder(
            [](Stack<BinaryTreeNode<T> *> &st,  BinaryTreeNode<T> *node) {
                DoubleBranchedTraversalOrder<T>::traversalBranch(st, node->getLeft());
                DoubleBranchedTraversalOrder<T>::traversalBranch(st, node->getRight());
                DoubleBranchedTraversalOrder<T>::traversalRoot(st, node);
            });
}

template<class T>
DoubleBranchedTraversalOrder<T> DoubleBranchedTraversalOrder<T>::createLrm() {
    return DoubleBranchedTraversalOrder(
            [](Stack<BinaryTreeNode<T> *> &st,  BinaryTreeNode<T> *node) {
                DoubleBranchedTraversalOrder<T>::traversalRoot(st, node);
                DoubleBranchedTraversalOrder<T>::traversalBranch(st, node->getRight());
                DoubleBranchedTraversalOrder<T>::traversalBranch(st, node->getLeft());
            });
}

template<class T>
DoubleBranchedTraversalOrder<T> DoubleBranchedTraversalOrder<T>::createLmr() {
    return DoubleBranchedTraversalOrder(
            [](Stack<BinaryTreeNode<T> *> &st,  BinaryTreeNode<T> *node) {
                DoubleBranchedTraversalOrder<T>::traversalBranch(st, node->getRight());
                DoubleBranchedTraversalOrder<T>::traversalRoot(st, node);
                DoubleBranchedTraversalOrder<T>::traversalBranch(st, node->getLeft());
            });
}

template<class T>
DoubleBranchedTraversalOrder<T> DoubleBranchedTraversalOrder<T>::createMlr() {
    return DoubleBranchedTraversalOrder(
            [](Stack<BinaryTreeNode<T> *> &st,  BinaryTreeNode<T> *node) {
                DoubleBranchedTraversalOrder<T>::traversalBranch(st, node->getRight());
                DoubleBranchedTraversalOrder<T>::traversalBranch(st, node->getLeft());
                DoubleBranchedTraversalOrder<T>::traversalRoot(st, node);
            });
}

template<class T>
DoubleBranchedTraversalOrder<T> DoubleBranchedTraversalOrder<T>::createRlm() {
    return DoubleBranchedTraversalOrder(
            [](Stack<BinaryTreeNode<T> *> &st,  BinaryTreeNode<T> *node) {
                DoubleBranchedTraversalOrder<T>::traversalRoot(st, node);
                DoubleBranchedTraversalOrder<T>::traversalBranch(st, node->getLeft());
                DoubleBranchedTraversalOrder<T>::traversalBranch(st, node->getRight());
            });
}

template<class T>
DoubleBranchedTraversalOrder<T> DoubleBranchedTraversalOrder<T>::createRml() {
    return DoubleBranchedTraversalOrder(
            [](Stack<BinaryTreeNode<T> *> &st,  BinaryTreeNode<T> *node) {
                DoubleBranchedTraversalOrder<T>::traversalBranch(st, node->getLeft());
                DoubleBranchedTraversalOrder<T>::traversalRoot(st, node);
                DoubleBranchedTraversalOrder<T>::traversalBranch(st, node->getRight());
            });
}


#endif //ALGORITHM_TREE_TRAVERSAL_IMPL_H
