#ifndef ALGORITHM_BINARY_TREE_H
#define ALGORITHM_BINARY_TREE_H

#include <functional>
#include <iostream>
#include <iomanip>
#include "../../container/sequence/Stack.h"
#include "../../util/function/function.h"
#include "../../container/sequence/Queue.h"
#include "BinaryTreeNode.h"
#include "TraversalOrder.h"
#include "../../lang/StringBuilder.h"


template<class T>
class BinaryTree {
protected:
    BinaryTreeNode<T> *root;
    int size;
public:
    BinaryTree();

    virtual void insert(const T &value) = 0;

    virtual Stack<BinaryTreeNode<T> *> search(const T &value) = 0;

    virtual int remove(const T &value) = 0;

    void clear();

    [[nodiscard]] int getSize() const {
        return size;
    }

    [[nodiscard]] int empty() const {
        return size == 0;
    }

    BinaryTreeNode<T> *getRoot() {
        return root;
    }

    Stack<BinaryTreeNode<T> *> traversal(const Function<BinaryTreeNode<T> *, bool> &task,
                                         const DoubleBranchedTraversalOrder<T> &order) const;

    static Stack<BinaryTreeNode<T> *> traversal(BinaryTreeNode<T> *root,
                                                const Function<BinaryTreeNode<T> *, bool> &task,
                                                const DoubleBranchedTraversalOrder<T> &order);


    /**
     * 广度优先
     */
    int traversal(const BiFunction<BinaryTreeNode<T> *, int, bool> &task) const;

    static int traversal(BinaryTreeNode<T> *root, const BiFunction<BinaryTreeNode<T> *, int, bool> &task);

    int traversalWithNull(const BiFunction<BinaryTreeNode<T> *, int, bool> &task) const;

    static int traversalWithNull(BinaryTreeNode<T> *root, const BiFunction<BinaryTreeNode<T> *, int, bool> &task);

    static int traversal(
            BinaryTreeNode<T> *root,
            const BiFunction<BinaryTreeNode<T> *, int, bool> &task,
            bool withNull);

    virtual ~BinaryTree();

    friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &obj) {
        if (obj.root == nullptr) {
            return os << "null root";
        }
        obj.traversal([&os](BinaryTreeNode<T> *node) mutable {
            os << *(node->getValue()) << ",";
            return true;
        }, DoubleBranchedTraversalOrder<T>::choose(tree::TreeTraversalWay::LMR));
        return os;
    }

    static std::ostream &printTree(std::ostream &os, const BinaryTree<T> &obj);

    static std::ostream &printNode(std::ostream &os, BinaryTreeNode<T> *node);

    static std::ostream &printNode(std::ostream &os, BinaryTreeNode<T> *node,
                                   unsigned int longestValueLength,
                                   const BiConsumer<std::ostream &, BinaryTreeNode<T> *> &printer);

    std::ostream &print(std::ostream &os) const {
        return BinaryTree<T>::printTree(os, *this);
    }

    /**
     * Root == Null, return 0;<p>
     * Root = 1 &&root.left=root.right=null, return 1;
     */
    static int maxDepth(BinaryTreeNode<T> *root);

    /**
     * Root == Null, return 0;<p>
     * Root = 1 &&root.left=root.right=null, return 1;
     */
    static int minDepth(BinaryTreeNode<T> *root);


    /**
     * 判断节点处于字节点的哪个位置, 要求子节点一定是父节点的子节点, 否则抛出IllegalArgumentException异常
     * 父节点为nullptr, 抛出NullPointException异常
     * 是左孩子返回true, 是有孩子返回false
     */
    static bool isLeftChild(const BinaryTreeNode<T> *node, const BinaryTreeNode<T> *nodeParent);


};


#include "impl/BinaryTree_impl.h"

#endif //ALGORITHM_BINARY_TREE_H
