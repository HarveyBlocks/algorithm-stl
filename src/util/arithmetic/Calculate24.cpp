/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/7/12
 *
 */
#include "Calculate24.h"

Calculator24::Calculator24(int a, int b, int c, int d) {
    nums = new int[4];
    nums[0] = a;
    nums[1] = b;
    nums[2] = c;
    nums[3] = d;
}


void Calculator24::exec() const {
    SingleLinkedList<ResultExpression> list;
    PermutationIterator iterator(4);
    Array<int> numArr(4);
    while (iterator.hasNext()) {
        iterator.next(numArr);
        for (int i0 = 0; i0 < 6; ++i0) {
            for (int i1 = 0; i1 < 6; ++i1) {
                for (int i2 = 0; i2 < 6; ++i2) {
                    double result = ArithmeticalOperation::CALCULATE_FUNCTION_ARRAY[i0](
                            ArithmeticalOperation::CALCULATE_FUNCTION_ARRAY[i1](
                                    ArithmeticalOperation::CALCULATE_FUNCTION_ARRAY[i2](
                                            nums[numArr[0]],
                                            nums[numArr[1]]
                                    ),
                                    nums[numArr[2]]
                            ),
                            nums[numArr[3]]
                    );
                    if ( std::abs(std::abs(result) - target) < 1e-6) {
                        list.pushFront(ResultExpression(
                                i0, i1, i2,
                                nums[numArr[0]],
                                nums[numArr[1]],
                                nums[numArr[2]],
                                nums[numArr[3]], true));
                    }
                }
            }
        }
    }
    iterator.reset();
    while (iterator.hasNext()) {
        iterator.next(numArr);
        for (int i0 = 0; i0 < 6; ++i0) {
            for (int i1 = 0; i1 < 6; ++i1) {
                for (int i2 = 0; i2 < 6; ++i2) {
                    double result = ArithmeticalOperation::CALCULATE_FUNCTION_ARRAY[i0](
                            ArithmeticalOperation::CALCULATE_FUNCTION_ARRAY[i2](
                                    nums[numArr[0]],
                                    nums[numArr[1]]
                            ),
                            ArithmeticalOperation::CALCULATE_FUNCTION_ARRAY[i1](
                                    nums[numArr[2]],
                                    nums[numArr[3]]
                            ));
                    if (std::abs(std::abs(result) - target) < 1e-6) {
                        list.pushFront(
                                ResultExpression(
                                        i0, i1, i2,
                                        nums[numArr[0]],
                                        nums[numArr[1]],
                                        nums[numArr[2]],
                                        nums[numArr[3]], false));
                    }
                }
            }
        }
    }

    std::cout << list << "\n";
}

Calculator24::~Calculator24() {
    delete[] nums;
}

Calculator24::ResultExpression::ResultExpression(int i0, int i1, int i2, int a, int b, int c, int d, bool methodA) :
        i0(i0), i1(i1), i2(i2), a(a), b(b), c(c), d(d), methodA(methodA) {}

std::ostream &operator<<( std::ostream &os, const Calculator24::ResultExpression &obj) {
    if (obj.methodA) {
        // "((a i2 b ) i1 c) i0 d";
        return os << ArithmeticalOperation::map2Expr(
                ArithmeticalOperation::map2Expr(
                        ArithmeticalOperation::map2Expr(
                                obj.a, obj.b, ArithmeticalOperation::map2Char(obj.i2)
                        ),
                        obj.c, ArithmeticalOperation::map2Char(obj.i1)
                ),
                obj.d, ArithmeticalOperation::map2Char(obj.i0)
        ) << "\n";
    } else {
        // "(a i2 b ) i0 (c i1 d)";
        return os << ArithmeticalOperation::map2Expr(
                ArithmeticalOperation::map2Expr(
                        obj.a, obj.b, ArithmeticalOperation::map2Char(obj.i2)
                ),
                ArithmeticalOperation::map2Expr(
                        obj.c, obj.d, ArithmeticalOperation::map2Char(obj.i1)
                ), ArithmeticalOperation::map2Char(obj.i0)
        ) << "\n";
    }

}
