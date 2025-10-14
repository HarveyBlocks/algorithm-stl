/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/22
 *
 */
#ifndef ALGORITHM_BINARY_SEARCH_TREE_H
#define ALGORITHM_BINARY_SEARCH_TREE_H

#include "BinaryTree.h"

#define GO_LEFT_BY(cmp) ((cmp)>=0)
template<class T>
class BinarySearchTree : public BinaryTree<T> {
private:


    /**
     * 使用循环删除都有左右子树的情况
     */
    void removeNodeByLoop(Stack<BinaryTreeNode<T> *> &trace);

    /**
     * 使用递归删除都有左右子树的情况
     */
    void removeNodeByRecursive(Stack<BinaryTreeNode<T> *> &trace);
protected:
    /**
     * @return 如果需要左右子树都存在, 需要递归/循环删除, 则返回true
     */
    virtual bool removeNode0(Stack<BinaryTreeNode<T> *> &trace);

public:
    BinarySearchTree() : BinaryTree<T>() {}

    BinarySearchTree(const BinarySearchTree<T> &tree);

    Stack<BinaryTreeNode<T> *> search(const T &value);

    void insert(const T &value);

    int remove(const T &value);

    /**
     * @param trace 该函数保证, 不会更改原trace, trace的栈顶是要新增加的节点
     * 次数trace.empty() 说明是根节点需要被删除
     */
    virtual BinaryTreeNode<T> * insertNode(Stack<BinaryTreeNode<T> *> &trace);

    /**
     * 不会被递归(其内部含递归)
     * @param trace 不会拷贝一份, 因为如果在两个叶子都存在的情况下的删除, 可能涉及删除节点的变化<p>
     *      本函数将会对trace进行进一步的加工<p>
     *      在如果在两个叶子都存在的情况下, 替换的节点在值被替换后不被释放内存, 依然出现在栈中<p>
     *      trace的栈顶不包含已经删除的节点(指已经被真正释放内存的节点), 栈顶是被删除节点的父节点<p>
     */
    virtual void removeNode(Stack<BinaryTreeNode<T> *> &trace);


    void resetRoot(BinaryTreeNode<T> *newRoot);

    static void traceFamily(Stack<BinaryTreeNode<T> *> trace, BinaryTreeNode<T> *root);
};


#include "impl/BinarySearchTree_impl.h"

#endif //ALGORITHM_BINARY_SEARCH_TREE_H
