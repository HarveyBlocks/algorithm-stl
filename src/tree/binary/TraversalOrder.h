/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/21
 *
 */
#ifndef ALGORITHM_TREE_TRAVERSAL_ADD_2_STACK_ORDER_H
#define ALGORITHM_TREE_TRAVERSAL_ADD_2_STACK_ORDER_H

#include <functional>
#include "BinaryTreeNode.h"
#include "../../container/sequence/Stack.h"
#include "TraversalOrderNode.h"

namespace tree {
    enum TreeTraversalWay {
        LRM, LMR, MLR,
        RLM, RML, MRL
    };
}


template<class T>
class DoubleBranchedTraversalOrder : public BiConsumer<Stack<BinaryTreeNode<T> *> &, BinaryTreeNode<T> *> {
private:
    explicit DoubleBranchedTraversalOrder(BiConsumer<Stack<BinaryTreeNode<T> *> &, BinaryTreeNode<T> *> order);

    static void traversalBranch(Stack<BinaryTreeNode<T> *> &st, BinaryTreeNode<T> *branch);

    static void traversalRoot(Stack<BinaryTreeNode<T> *> &st, BinaryTreeNode<T> *root);

    static DoubleBranchedTraversalOrder createLrm();

    static DoubleBranchedTraversalOrder createLmr();

    static DoubleBranchedTraversalOrder createMlr();

    static DoubleBranchedTraversalOrder createRlm();

    static DoubleBranchedTraversalOrder createRml();

    static DoubleBranchedTraversalOrder createMrl();

public:
    static DoubleBranchedTraversalOrder<T> choose(tree::TreeTraversalWay way);
};


#include "impl/TraversalOrder_impl.h"

#endif //ALGORITHM_TREE_TRAVERSAL_ADD_2_STACK_ORDER_H
