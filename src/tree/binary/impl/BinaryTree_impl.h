/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/21
 *
 */
#ifndef ALGORITHM_BINARY_TREE_IMPL_H
#define ALGORITHM_BINARY_TREE_IMPL_H


#include "../BinaryTree.h"


template<class T>
BinaryTree<T>::BinaryTree() : size(0), root(nullptr) {}

template<class T>
void BinaryTree<T>::clear() {
    if (root == nullptr) {
        return;
    }
    traversal([](BinaryTreeNode<T> *node) {
        delete node;
        return true;
    }, DoubleBranchedTraversalOrder<T>::choose(tree::TreeTraversalWay::LRM));
}

template<class T>
BinaryTree<T>::~BinaryTree() {
    if (size < 0) {
        return;
    }
    clear();
}


template<class T>
Stack<BinaryTreeNode<T> *> BinaryTree<T>::traversal(BinaryTreeNode<T> *root,
                                                    const Function<BinaryTreeNode<T> *, bool> &task,
                                                    const DoubleBranchedTraversalOrder<T> &order) {
    Stack<BinaryTreeNode<T> *> st;
    if (root == nullptr) {
        throw IllegalStateException("Null Root");
    }
    st.push(root);
    while (!st.empty()) {
        BinaryTreeNode<T> *node = st.pop(); // 将空节点弹出
        if (node == nullptr) {
            // 只有遇到空节点的时候，才将下一个节点放进结果集
            node = st.pop();    // 重新取出栈中元素
            if (!task(node)) {
                st.push(node);
                break;
            }
            continue;
        }
        order(st, node);
    }
    return st;
}

template<class T>
int BinaryTree<T>::traversal(BinaryTreeNode<T> *root,
                             const BiFunction<BinaryTreeNode<T> *, int, bool> &task) {
    if (root == nullptr) {
        return 0;
    }
    Queue<BinaryTreeNode<T> *> que;
    que.push(root);
    int depth = 0;
    bool taskResult = false;
    while (!que.empty()) {
        depth++;
        int queSize = que.size();
        // 这里一定要使用固定大小size，不要使用que.queSize()，因为que.size是不断变化的
        for (int i = 0; i < queSize; i++) {
            BinaryTreeNode<T> *node = que.pop();
            if (!(taskResult = task(node, depth))) {
                break;
            }
            if (node->getLeft()) {
                que.push(node->getLeft());
            }
            if (node->getRight()) {
                que.push(node->getRight());
            }
        }
        if (!taskResult) {
            break;
        }
    }
    return depth;
}

template<class T>
int
BinaryTree<T>::traversalWithNull(
        BinaryTreeNode<T> *root, const BiFunction<BinaryTreeNode<T> *, int, bool> &task) {
    return BinaryTree<T>::traversal(root, task, true);
}

template<class T>
int BinaryTree<T>::traversal(
        BinaryTreeNode<T> *root,
        const BiFunction<BinaryTreeNode<T> *, int, bool> &task,
        bool withNull) {
    if (root == nullptr) {
        return 0;
    }
    Queue<BinaryTreeNode<T> *> que;
    que.push(root);
    int depth = 0;
    bool taskResult = false;
    while (!que.empty()) {
        int queSize = que.size();
        depth++;
        // 这里一定要使用固定大小size，不要使用que.queSize()，因为que.size是不断变化的
        bool allNull = true;
        for (int i = 0; i < queSize; i++) {
            BinaryTreeNode<T> *node = que.pop();
            que.push(node);
            if (allNull && node != nullptr) {
                allNull = false;
            }
        }
        if (allNull) {
            depth--;
            break;
        }
        for (int i = 0; i < queSize; i++) {
            BinaryTreeNode<T> *node = que.pop();
            if (!(taskResult = task(node, depth))) {
                break;
            }
            if (withNull && node == nullptr) {
                que.push(nullptr);
                que.push(nullptr);
                continue;
            }
            if (node->getLeft()) {
                que.push(node->getLeft());
            } else if (withNull) {
                que.push(nullptr);
            }
            if (node->getRight()) {
                que.push(node->getRight());
            } else if (withNull) {
                que.push(nullptr);
            }
        }
        if (!taskResult) {
            break;
        }
    }
    return depth;
}

template<class T>
Stack<BinaryTreeNode<T> *>
BinaryTree<T>::traversal(const Function<BinaryTreeNode<T> *, bool> &task,
                         const DoubleBranchedTraversalOrder<T> &order) const {
    return BinaryTree<T>::traversal(this->root, task, order);
}


template<class T>
int BinaryTree<T>::traversal(const BiFunction<BinaryTreeNode<T> *, int, bool> &task) const {
    return BinaryTree<T>::traversal(this->root, task);
}

template<class T>
int BinaryTree<T>::traversalWithNull(const BiFunction<BinaryTreeNode<T> *, int, bool> &task) const {
    return BinaryTree<T>::traversalWithNull(this->root, task);
}


template<class T>
std::ostream &BinaryTree<T>::printTree(std::ostream &os, const BinaryTree<T> &obj) {
    return BinaryTree<T>::printNode(os, obj.root);// os << '\n';
}

template<class T>
std::ostream &BinaryTree<T>::printNode(std::ostream &os, BinaryTreeNode<T> *node) {
    int i = 0;
    static int twoPwdTimes[14] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8196};
    int (*cal2Times)(unsigned int) = [](unsigned int time) {
        if (time < 14) {
            return twoPwdTimes[time];
        }
        int result = 1;
        while (time-- > 0) {
            result <<= 1;
        }
        return result;
    };
    BinaryTree<T>::traversalWithNull(node, [&i, cal2Times, &os](BinaryTreeNode<int> *node, int depth) mutable {
        if (++i == cal2Times(depth - 1)) {
            os << '\n' << "[" << depth << "] ";
        }
        if (node != nullptr) {
            os << *node << " ";
        } else {
            os << "N ";
        }
        return true;
    });
    return os << '\n';
}

template<class T>
std::ostream &BinaryTree<T>::printNode(
        std::ostream &os, BinaryTreeNode<T> *node,
        unsigned int longestValueLength,
        const BiConsumer<std::ostream &, BinaryTreeNode<T> *> &printer) {
    BiFunction<unsigned int, unsigned int, String> spacePow2 = []
            (unsigned int n, unsigned int len) {
        int num = 1;
        while (n-- > 0) {
            num <<= 1;
            num += 1;
        }
        return (String(" ") * (num * len)).toString();
    };
    int height = BinaryTree<T>::maxDepth(node);
    int oldDepth = -1;
    String nilStr = (String("N") * longestValueLength).toString();
    BiFunction<BinaryTreeNode<T> *, int, bool> task =
            [&os, &height, spacePow2, &oldDepth, &nilStr, &printer]
                    (BinaryTreeNode<T> *node, int depth) mutable {
                if (depth != oldDepth) {
                    oldDepth = depth;
                    os << '\n' << "[" << depth << "]:";
                }
                int nilSize = nilStr.getSize();
                if (node == nullptr) {
                    os << spacePow2(height - depth, nilSize)
                       << std::setw(nilSize) << nilStr;
                } else {
                    os << spacePow2(height - depth, nilSize)
                       << std::setw(nilSize);
                    printer(os, node);
                }
                return true;
            };
    BinaryTree<T>::traversalWithNull(node, task);
    return os << "\n";
}

template<class T>
int BinaryTree<T>::minDepth(BinaryTreeNode<T> *root) {
    const BiFunction<BinaryTreeNode<T> *, int, bool> &task = [](
            BinaryTreeNode<T> *node, int depth) mutable {
        return !(node != nullptr && node->getLeft() == nullptr && node->getRight() == nullptr);
    };
    return BinaryTree<T>::traversal(root, task);
}

template<class T>
int BinaryTree<T>::maxDepth(BinaryTreeNode<T> *root) {
    const BiFunction<BinaryTreeNode<T> *, int, bool> &task = [](BinaryTreeNode<T> *node, int depth) {
        return true;
    };
    return BinaryTree<T>::traversal(root, task);
}

template<class T>
bool BinaryTree<T>::isLeftChild(const BinaryTreeNode<T> *node, const BinaryTreeNode<T> *nodeParent) {
    if (nodeParent == nullptr) {
        throw NullPointException();
    }
    BinaryTreeNode<T> *parentLeft = nodeParent->getLeft();
    BinaryTreeNode<T> *parentRight = nodeParent->getRight();
    if (parentLeft == nullptr && parentRight == nullptr) {
        throw IllegalArgumentException();
    }

    bool same2Left = parentLeft == node;
    bool same2Right = parentRight == node;

    if (parentLeft == nullptr && parentRight != nullptr) {
        if (!same2Right) {
            throw IllegalArgumentException();
        }
        return false;
    }
    if (parentLeft != nullptr && parentRight == nullptr) {
        if (!same2Left) {
            throw IllegalArgumentException();
        }
        return true;
    }

    if (same2Left && !same2Right) {
        return true;
    }
    if (!same2Left && same2Right) {
        return false;
    }
    throw IllegalArgumentException();
}

#endif //ALGORITHM_BINARY_TREE_IMPL_H
