/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/26
 *
 */
#ifndef ALGORITHM_BLACK_RED_TREE_H
#define ALGORITHM_BLACK_RED_TREE_H

#include "BinaryBalanceSearchTree.h"
#include "RedBlackTreeNode.h"
#include "../lang/exception/IllegalArgumentException.h"

template<class T>
class RedBlackTree : public BinaryBalanceSearchTree<T> {
private:
    /**
     * @return 调整完成返回true
     */
    bool rbInsertAdjust(Stack<BinaryTreeNode<T> *> &trace);

    /**
     * 需要被循环以应对删除黑色节点中有关递归的逻辑
     * @return
     *      0 新的removedNodeIsLeftChild为false<p>
     *      1 新的removedNodeIsLeftChild为true<p>
     *      -1 已经完成调整,暂停循环
     */
    int fixBlackNoneChildNodeRemove(Stack<BinaryTreeNode<T> *> &trace, bool removedNodeIsLeftChild);

    void paintingAndRotate(bool removedNodeIsLeftChild,
                           BinaryTreeNode<T> *sibling,
                           BinaryTreeNode<T> *nodeParent,
                           BinaryTreeNode<T> *nodeGrandParent
    ) ;

protected:
    bool removeNode0(Stack<BinaryTreeNode<T> *> &trace) override;

    virtual RedBlackTreeNode<T> *castInsertNode(BinaryTreeNode<T> *newNode) const;
public:
    /**
     * @param trace
     * @return 真正增加到树里的节点(由于本函数会对节点进行进一步的封装, 最终的节点和节点可能不一致)
     */
    BinaryTreeNode<T> * insertNode(Stack<BinaryTreeNode<T> *> &trace) override;


    std::ostream &printWithColor(std::ostream &os);

    static std::ostream &printNodeWithColor(std::ostream &os, BinaryTreeNode<T> *node);


    static bool colorCurrent(BinaryTreeNode<T> *root);

};
#include "impl/RedBlackTree_impl.h"

#endif //ALGORITHM_BLACK_RED_TREE_H
