//
// Created by Lenovo on 2025/12/2.
//

#ifndef ALGORITHM_BTREE_NODE_H
#define ALGORITHM_BTREE_NODE_H

#include "../BTreeNode.h"
#include "../../../util/Objects.h"

#ifdef DEBUG

#include <queue>

#endif

namespace harvey::algorithm::tree::btree {
    template<typename T, typename Cmp>
    BTreeNode<T, Cmp>::BTreeNode(int level) :
            datas(new BTreeData<T>[level - 1]), children(new BTreeNodeReference<T, Cmp>[level]), size(0) {
        for (int i = 0; i < level - 1; ++i) {
            datas[i] = nullptr;
        }
    }

    template<typename T, typename Cmp>
    BTreeNode<T, Cmp>::~BTreeNode() {
        delete[] children;
        delete[] datas;
    }

    template<typename T, typename Cmp>
    int BTreeNode<T, Cmp>::search(const T &value, const BTree<T, Cmp> *belong) const {
        int high = size - 1;
        int low = 0;
        while (low <= high) {
            int mid = int(low + ((unsigned int) (high - low) >> 1));
            BTreeData<T> data = datas[mid];
            int cmp = belong->cmp(*data, value);
            if (cmp < 0) {
                low = mid + 1;
            } else if (cmp > 0) {
                high = mid - 1;
            } else {
                return mid; // key found
            }
        }
        return -(low + 1);  // key not found.
    }

    template<typename T, typename Cmp>
    BTreeNodeReference<T, Cmp> BTreeNode<T, Cmp>::childAt(int index) const {
        return children[index];
    }

    template<typename T, typename Cmp>
    BTreeNodeReference<T, Cmp> BTreeNode<T, Cmp>::setChild(int index, const BTreeNodeReference<T, Cmp> &child) {
        BTreeNodeReference<T, Cmp> old = children[index];
        children[index] = child;
        return old;
    }


    template<typename T, typename Cmp>
    BTreeData<T> BTreeNode<T, Cmp>::setData(int index, const BTreeData<T> &data) {
        BTreeData<T> old = datas[index];
        datas[index] = data;
        return old;
    }

    template<typename T, typename Cmp>
    void BTreeNode<T, Cmp>::resetChild(int index) {
        children[index] = nullptr;
    }

    template<typename T, typename Cmp>
    bool BTreeNode<T, Cmp>::full(int level) const {
        return level - 1 == size;
    }

    template<typename T, typename Cmp>
    bool BTreeNode<T, Cmp>::empty() const {
        return size == 0;
    }

    template<typename T, typename Cmp>
    bool BTreeNode<T, Cmp>::leaf() const {
        return this->children[this->size] == nullptr;
    }

    template<typename T, typename Cmp>
    bool BTreeNode<T, Cmp>::insert(int index, int level, const InsertGroup<T, Cmp> &insertGroup) {
        Objects::requireTrue(index <= size, "can not insert after node dataSize");
        Objects::checkTrue(size < level - 1, "tree node is full");
        for (int i = size; i > index; --i) {
            datas[i] = datas[i - 1];
            children[i + 1] = children[i];
        }
        datas[index] = insertGroup.data;
        size++;
        children[index] = insertGroup.left;
        children[index + 1] = insertGroup.right;
        return level - 1 == size;
    }

    template<typename T, typename Cmp>
    BTreeNode<T, Cmp> BTreeNode<T, Cmp>::plus(int index, const InsertGroup<T, Cmp> &insertGroup) const {
        Objects::requireTrue(index <= size, "can not insert after node dataSize");
        int level = size + 1;
        BTreeNode<T, Cmp> target(level + 1);
        for (int i = 0, j = 0, k = 0; i < size + 1; ++i) {
            if (i == index) {
                target.datas[i] = insertGroup.data;
                target.children[k++] = insertGroup.left;
                target.children[k++] = insertGroup.right;
            } else {
                target.datas[i] = datas[j++];
                target.children[k++] = children[i];
            }
        }
        target.size = level;
        return target;
    }

    template<typename T, typename Cmp>
    void BTreeNode<T, Cmp>::reset() {
        for (int i = 0; i < size; ++i) {
            datas[i] = nullptr;
            children[i] = nullptr;
        }
        children[size] = nullptr;
        size = 0;
    }

    template<typename T, typename Cmp>
    void BTreeNode<T, Cmp>::split(InsertGroup<T, Cmp> &insertGroup) const {
        int level = size;
        // 1. 的值移动到上面的节点 4->1, 5->2, 6->2
        int midIndex = (level - 1) >> 1;
        // 2. update left
        for (int i = 0; i < midIndex; ++i) {
            insertGroup.left->datas[i] = datas[i];
            insertGroup.left->children[i] = children[i];
        }
        insertGroup.left->size = midIndex;
        insertGroup.left->children[insertGroup.left->size] = this->children[insertGroup.left->size];
        // 3. update data = top->at(index = level>>1);
        insertGroup.data = datas[midIndex];
        // 4. update right
        for (int i = midIndex + 1, j = 0; i < level; ++i, ++j) {
            insertGroup.right->datas[j] = datas[i];
            insertGroup.right->children[j] = children[i];
        }
        insertGroup.right->size = level - midIndex - 1;
        insertGroup.right->children[insertGroup.right->size] = this->children[level];
    }


    template<typename T, typename Cmp>
    BTreeData<T> BTreeNode<T, Cmp>::resetData(int index, const T &value) {
        BTreeData<T> old = datas[index];
        BTreeData<T> reset = datas[index] = new T(value);
        delete old;
        return reset;
    }

    template<typename T, typename Cmp>
    BTreeData<T> BTreeNode<T, Cmp>::dataAt(int index) const {
        return datas[index];
    }

    template<typename T, typename Cmp>
    void
    BTreeNode<T, Cmp>::insertFirst(const BTreeData<T> &data, const BTreeNodeReference<T, Cmp> &firstChild) {
        for (int i = size; i > 0; --i) {
            datas[i] = datas[i - 1];
            children[i + 1] = children[i];
        }
        children[1] = children[0];
        // 添加data和children
        children[0] = firstChild;
        datas[0] = data;
        size++;
    }

    template<typename T, typename Cmp>
    void BTreeNode<T, Cmp>::removeFirst() {
        for (int i = 0; i < size - 1; ++i) {
            datas[i] = datas[i + 1];
            children[i] = children[i + 1];
        }
        children[size - 1] = children[size];
        // 删除多余的data和children
        children[size] = nullptr;
        size--;
        datas[size] = nullptr;
    }


    template<typename T, typename Cmp>
    int BTreeNode<T, Cmp>::filledCount() {
        return size;
    }

#ifdef DEBUG


    template<typename T, typename Cmp>
    void BTreeNode<T, Cmp>::showBTree(int level, ::std::ostream &os) const {
        std::queue<::std::pair<BTreeNodeReference<T, Cmp>, ::std::pair<int, ::std::pair<int, int>>>> que;
        int depth = 0;
        int cnt = 0;
        que.emplace(BTreeNodeReference<T, Cmp>(this),
                    ::std::pair<int, ::std::pair<int, int>>{depth, ::std::pair<int, int>{cnt++, -1}});
        // [id,size,parent]
        while (!que.empty()) {
            ::std::pair<BTreeNodeReference<T, Cmp>, ::std::pair<int, ::std::pair<int, int>>> front = que.front();
            que.pop();
            BTreeNodeReference<T, Cmp> node = front.first;
            int nowDepth = front.second.first;
            int id = front.second.second.first;
            int parentId = front.second.second.second;
            if (nowDepth > depth) {
                os << ::std::endl;
                depth = nowDepth;
            }
            if (node == nullptr) {
                continue;
            }
            os << "[" << id << "|" << node->size << "|";
            parentId < 0 ? os << "-" : os << parentId;
            os << "]" << "(";
            for (int i = 0; i < level - 1; ++i) {
                BTreeData<T> data = node->datas[i];
                if (data != nullptr) {
                    os << *data;
                } else {
                    os << "n";
                }
                os << "|)"[i == level - 2] << ::std::flush;
                que.push({node->children[i],
                          ::std::pair<int, ::std::pair<int, int>>{depth + 1, ::std::pair<int, int>{cnt++, id}}});
            }
            os << "\t";
            que.push({node->children[level - 1],
                      ::std::pair<int, ::std::pair<int, int>>{depth + 1, ::std::pair<int, int>{cnt++, id}}});
        }
        os << ::std::endl;
    }

#endif
}
#endif //ALGORITHM_BTREE_NODE_H
