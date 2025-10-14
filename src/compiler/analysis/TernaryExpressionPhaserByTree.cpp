/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/11/14
 *
 */
#include "TernaryExpressionPhaserByTree.h"

TernaryExpressionEdge::TernaryExpressionEdge() : left(nullptr), right(nullptr), mid(nullptr) {}

TernaryExpressionEdge *TernaryExpressionEdge::castToEdge(TernaryExpression *origin) {
    return dynamic_cast<TernaryExpressionEdge *>(origin);
}

TernaryExpressionEnd::TernaryExpressionEnd(const String &expression) :
        expression(expression) {
}

TernaryExpressionEnd *TernaryExpressionEnd::castToEnd(TernaryExpression *origin) {
    return dynamic_cast<TernaryExpressionEnd *>(origin);
}

void TernaryExpressions::traversal(TernaryExpression *root, const Function<TernaryExpression *, bool> &task) {
    Stack<TernaryExpression *> st;
    if (root == nullptr) {
        throw IllegalStateException("Null Root");
    }
    st.push(root);
    while (!st.empty()) {
        TernaryExpression *node = st.pop(); // 将空节点弹出
        if (node == nullptr) {
            // 只有遇到空节点的时候，才将下一个节点放进结果集
            node = st.pop();    // 重新取出栈中元素
            if (!task(node)) {
                st.push(node);
                break;
            }
            continue;
        }

        st.push(node);
        st.push(nullptr);
        TernaryExpressionEdge *edgeNode = TernaryExpressionEdge::castToEdge(node);
        if (edgeNode == nullptr) {
            continue;
        }
        if (edgeNode->right) {
            st.push(edgeNode->right);
        }
        if (edgeNode->mid) {
            st.push(edgeNode->mid);
        }
        if (edgeNode->left) {
            st.push(edgeNode->left);
        }
    }
}

void TernaryExpressions::clear(TernaryExpression *root) {
    if (root == nullptr) {
        return;
    }
    traversal(root, [](TernaryExpression *node) {
        delete node;
        return true;
    });
}

TernaryExpressionPhaser::LinkedListNodePair::LinkedListNodePair(DoublyLinkedNode<String> *pre,
                                                                DoublyLinkedNode<String> *post) :
        pre(pre), post(post), interval(calInterval()) {
    if (noPair()) {
        throw NullPointException();
    }
    if (pre == nullptr || post == nullptr) {
        throw IllegalArgumentException("配对不准确");
    }
}

bool TernaryExpressionPhaser::LinkedListNodePair::noPair() const {
    return pre == nullptr && post == nullptr;
}

int TernaryExpressionPhaser::LinkedListNodePair::calInterval() const {
    int _interval = 0;
    if (noPair()) {
        return _interval;
    }
    if (pre == nullptr) {
        throw NullPointException();
    }
    const DoublyLinkedNode<String> *node = pre;
    while (node->post != post) {
        node = node->post;
        _interval++;
    }
    if (_interval < 0) {
        throw IllegalStateException();
    }
    return _interval;
}

TernaryExpressionPhaser::TernaryExpressionPhaser(const String &preToken, const String &postToken) :
        preToken(preToken.trim()), postToken(postToken.trim()) {
    if (preToken.empty() || postToken.empty()) {
        throw IllegalArgumentException("俩Token不应该为空");;
    }
    if (preToken == postToken) {
        throw IllegalArgumentException("俩Token不应该相同");;
    }
}

TernaryExpression *TernaryExpressionPhaser::phase(const String &text) const {
    DoublyLinkedList<String> separatedText = separateText(text);
    if (!validText(separatedText)) {
        throw IllegalArgumentException("不正确的匹配");
    }
    std::cout << separatedText << std::endl;
    auto root = new TernaryExpressionEdge();
    separatedText.pushFront(preToken);
    separatedText.pushBack(postToken);
    construct(root, separatedText,
              LinkedListNodePair(separatedText.frontNode(), separatedText.backNode()));
    delete root->right;
    delete root->left;
    return root->mid;
}

bool TernaryExpressionPhaser::isToken(const String &str) const {
    return isPreToken(str) || isPostToken(str);
}

bool TernaryExpressionPhaser::isPreToken(const String &str) const { return preToken.equals(str); }

bool TernaryExpressionPhaser::isPostToken(const String &str) const { return postToken.equals(str); }

DoublyLinkedList<String> TernaryExpressionPhaser::separateText(const String &text) const {
    int preLen = preToken.getSize();
    int postLen = postToken.getSize();
    DoublyLinkedList<String> separatedText;
    int textSize = text.getSize();
    for (int start = 0; start < textSize;) {
        int preIndex = text.getFirstIndex(preToken, start);
        int postIndex = text.getFirstIndex(postToken, start);
        if (preIndex == -1 && postIndex == -1) {
            separatedText.pushBack(text.subString(start));
            break;
        }
        if (preIndex != -1 && preIndex < postIndex) {
            separatedText.pushBack(text.subString(start, preIndex));
            separatedText.pushBack(preToken);
            start = preIndex + preLen;
        } else if (postIndex < preIndex || (preIndex == -1 /*&& postIndex != -1*/)) {
            separatedText.pushBack(text.subString(start, postIndex));
            separatedText.pushBack(postToken);
            start = postIndex + postLen;
        }
    }
    return separatedText;
}

bool TernaryExpressionPhaser::validText(const DoublyLinkedList<String> &text) const {
    int pair = 0;
    text.forEach([this, &pair](String &item) {
        if (this->isPreToken(item)) {
            pair++;
        } else if (this->isPostToken(item)) {
            pair--;
        }
        return pair >= 0;
    });
    return pair == 0;
}

TernaryExpression *TernaryExpressionPhaser::construct(
        TernaryExpression *root, const DoublyLinkedList<String> &separatedText,
        TernaryExpressionPhaser::LinkedListNodePair nodePair) const {
    TernaryExpressionEdge *edgeRoot = TernaryExpressionEdge::castToEdge(root);
    if (edgeRoot == nullptr) {
        return root;
    }
    edgeRoot->mid = constructMid(separatedText, nodePair);
    edgeRoot->left = constructLeft(separatedText, nodePair);
    edgeRoot->right = constructRight(separatedText, nodePair);
    return root;

}

TernaryExpression *TernaryExpressionPhaser::constructMid(
        const DoublyLinkedList<String> &separatedText,
        const TernaryExpressionPhaser::LinkedListNodePair &nodePair) const {
    switch (nodePair.interval) {
        case 0:
            return new TernaryExpressionEnd(String(""));
        case 1:
            return new TernaryExpressionEnd(*(nodePair.pre->post->value));
        default:
            return construct(new TernaryExpressionEdge(), separatedText, getInnerPair(separatedText, nodePair));
    }
}

TernaryExpression *TernaryExpressionPhaser::constructLeft(
        const DoublyLinkedList<String> &separatedText,
        const TernaryExpressionPhaser::LinkedListNodePair &nodePair) const {
    if (separatedText.isEndpoint(nodePair.pre) ||
        isToken(*(nodePair.pre->pre->value))) {
        return new TernaryExpressionEnd(String(""));
    } else if (separatedText.isEndpoint(nodePair.pre->pre) ||
               isPreToken(*(nodePair.pre->pre->pre->value))) {
        return new TernaryExpressionEnd(*(nodePair.pre->pre->value));
    } else if (isPostToken(*(nodePair.pre->pre->pre->value))) {
        // 由于是从前向后分析的
        // 前一个) , 就是该if分支检测的isPostToken
        // 这个的)对应的一组)在左边, 一整个都是属于当前pair需要分析的
        // 所以是*(nodePair.pre->pre->value)
        return new TernaryExpressionEnd(*(nodePair.pre->pre->value));
    } else {
        return construct(new TernaryExpressionEdge(), separatedText, getInnerPair(separatedText, nodePair));
    }
}

TernaryExpression *TernaryExpressionPhaser::constructRight(
        const DoublyLinkedList<String> &separatedText,
        const TernaryExpressionPhaser::LinkedListNodePair &nodePair) const {
    if (separatedText.isEndpoint(nodePair.post) ||
        isToken(*(nodePair.post->post->value))) {
        return new TernaryExpressionEnd(String(""));
    } else if (separatedText.isEndpoint(nodePair.post->post) ||
               isPostToken(*(nodePair.post->post->post->value))) {
        return new TernaryExpressionEnd(*(nodePair.post->post->value));
    } else if (isPreToken(*(nodePair.post->post->post->value))) {
        // 由于是从前向后分析的
        // 后一个( , 就是该if分支检测的isPreToken
        // 这个的(对应的一组()在右边, 一整个都是属于当前pair的left
        // 延迟到下一个递归中去分析
        // 所以是*(nodePair.pre->pre->value)
        // 由于是从前向后分析的, 所以postToken是最后一个
        auto root = new TernaryExpressionEdge();
        separatedText.insert(nodePair.post, preToken);
        construct(root, separatedText, LinkedListNodePair(nodePair.post->post, separatedText.backNode()));
        delete root->left;
        return root->mid;
    } else {
        return construct(new TernaryExpressionEdge(), separatedText, getInnerPair(separatedText, nodePair));
    }
}

TernaryExpressionPhaser::LinkedListNodePair
TernaryExpressionPhaser::getInnerPair(const DoublyLinkedList<String> &separatedText,
                                      const TernaryExpressionPhaser::LinkedListNodePair &nodePair) const {
    DoublyLinkedNode<String> *preNode = nullptr;
    DoublyLinkedNode<String> *postNode = nullptr;
    int pair = 0;
    bool passedOuterPre = false;
    Function<DoublyLinkedNode<String> *, bool> findInnerPair =
            [this, &preNode, &postNode, &pair, &nodePair, &passedOuterPre](
                    DoublyLinkedNode<String> *node) {

                if (!passedOuterPre && node != nodePair.pre) {
                    return true; // continue 掠过未到达的
                }
                if (node == nodePair.pre) {
                    passedOuterPre = true;
                    return true; // continue 掠过左括号
                }
                if (node->value == nullptr) {
                    throw NullPointException();
                }

                std::cout << *(node->value) << "->";

                if (node->value->equals(preToken)) {
                    if (preNode == nullptr) {
                        // 目标Inner
                        preNode = node;
                    } else {
                        // 第二个及以后的pre
                        pair++;
                    }
                    return true;
                }
                if (preNode != nullptr && node->value->equals(postToken)) {
                    if (pair == 0) {
                        postNode = node;
                        return false; // break
                    }
                    pair--;
                    return true;
                }
                if (node == nodePair.post) {
                    return false; // break; 掠过右括号
                }
                return true;
            };
    separatedText.forEach(findInnerPair);
    if (pair != 0) {
        throw IllegalArgumentException("不正确的pre-post token 匹配");
    }
    std::cout << "end" << std::endl;
    TernaryExpressionPhaser::LinkedListNodePair innerNodePair(preNode, postNode);
    return innerNodePair;
}
