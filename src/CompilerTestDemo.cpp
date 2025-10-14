/**
 *  一次关于对三元运算符的解析的尝试, 原理是使用三叉树
 *  但并不正确
 *  如`()()()()()`中
 *  几个括号等价, 不能因为解析读取的顺序不同, 就将它们放到树不同层
 *  正确的应该参考XML
 *  故本方案废弃, 类似XML的实现亲参考其他文件
 *
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/11/11
 *
 */

#include "compiler/analysis/TernaryExpressionPhaserByTree.h"

#include "lang/String.h"
#include "lang/StringBuilder.h"
#include "container/sequence/SingleLinkedList.h"


int ternaryExpressionPhaserDemo() {
    TernaryExpressionPhaser phaser(String("("), String(")"));
    TernaryExpression *expression = phaser.phase(String("1(2(3)4)5(6)7(8(9)10(11)12)13"));
    TernaryExpressions::traversal(expression, [](TernaryExpression *te) {
        TernaryExpressionEnd *tee = TernaryExpressionEnd::castToEnd(te);
        if (tee != nullptr) {
            std::cout << "`" << tee->expression << "` ";
        }
        return true;
    });
    std::cout << std::endl;
    TernaryExpressions::clear(expression);
    return 0;
}


int expressionDemo() {
    return 0;
}

// int CompilerTestDemoCode = expressionDemo();