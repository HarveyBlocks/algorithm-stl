
/**
 *  一次关于对三元运算符的解析的尝试, 原理是使用三叉树
 *  但并不正确
 *  如`()()()()()`中
 *  几个括号等价, 不能因为解析读取的顺序不同, 就将它们放到树不同层
 *  正确的应该参考XML
 *  故本方案废弃, 类似XML的实现亲参考其他文件
 *
 *  @author [mailto:harvey.blocks@outlook.com] Harvey Blocks
 *  @date 2024/11/11
 *
 */
#ifndef ALGORITHM_TERNARY_EXPRESSION_PHASER_BY_TESS_H
#define ALGORITHM_TERNARY_EXPRESSION_PHASER_BY_TESS_H


#include "../../lang/String.h"
#include "../../container/sequence/Stack.h"
#include "../../container/sequence/Queue.h"

class  TernaryExpression {
protected:
    TernaryExpression() = default;

public:
    virtual ~TernaryExpression() = default;
};

/**
 * 解析条件运算符
 * @return Exit Code
 */
class /*[[deprecated("实现不合理")]] */TernaryExpressionEdge : public TernaryExpression {
public:
    TernaryExpression *left;
    TernaryExpression *mid;
    TernaryExpression *right;

    TernaryExpressionEdge();;

    TernaryExpressionEdge(const TernaryExpressionEdge &obj) = default;

    static TernaryExpressionEdge *castToEdge(TernaryExpression *origin);

    ~TernaryExpressionEdge() override = default;
};

class /*[[deprecated("实现不合理")]]*/ TernaryExpressionEnd : public TernaryExpression {
public:
    String expression;

    explicit TernaryExpressionEnd(const String &expression);

    TernaryExpressionEnd(const TernaryExpressionEnd &ternaryExpressionEnd) = default;

    ~TernaryExpressionEnd() override = default;

   static TernaryExpressionEnd *castToEnd(TernaryExpression *origin);;
};

struct TernaryExpressions {
    // 左中右根
    static void traversal(TernaryExpression *root, const Function<TernaryExpression *, bool> &task);

    static void clear(TernaryExpression *root);
};

class /*[[deprecated("实现不合理")]]*/ TernaryExpressionPhaser {
private:
    static const TernaryExpression EMPTY_TERNARY_EXPRESSION;
    String preToken;
    String postToken;

    struct LinkedListNodePair {
        DoublyLinkedNode<String> *pre;
        DoublyLinkedNode<String> *post;
        int interval = 0;
        LinkedListNodePair(DoublyLinkedNode<String> *pre, DoublyLinkedNode<String> *post);
    private:
        [[nodiscard]] bool noPair() const;
        [[nodiscard]] int calInterval() const;
    };

public:
    TernaryExpressionPhaser(const String &preToken, const String &postToken);
    [[nodiscard]] TernaryExpression *phase(const String &text) const;

    [[nodiscard]] bool isToken(const String &str) const;

    [[nodiscard]] bool isPreToken(const String &str) const;

    [[nodiscard]]  bool isPostToken(const String &str) const;

private:

    [[nodiscard]] DoublyLinkedList<String> separateText(const String &text) const;

    [[nodiscard]] bool validText(const DoublyLinkedList<String> &text) const;

    TernaryExpression *construct(
            TernaryExpression *root,
            const DoublyLinkedList<String> &separatedText, LinkedListNodePair nodePair) const;

    [[nodiscard]] TernaryExpression *constructMid(
            const DoublyLinkedList<String> &separatedText, const LinkedListNodePair &nodePair) const;

    [[nodiscard]] TernaryExpression *constructLeft(
            const DoublyLinkedList<String> &separatedText, const LinkedListNodePair &nodePair) const;

    [[nodiscard]] TernaryExpression *constructRight(
            const DoublyLinkedList<String> &separatedText, const LinkedListNodePair &nodePair) const;

    /**
     * @param nodePair post不重要, 只要不在pre之前就行, 不存在也行
     */
    [[nodiscard]] LinkedListNodePair getInnerPair(
            const DoublyLinkedList<String> &separatedText, const LinkedListNodePair &nodePair) const;


};


#endif //ALGORITHM_TERNARY_EXPRESSION_PHASER_BY_TESS_H
