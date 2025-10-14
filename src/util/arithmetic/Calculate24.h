/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/7/12
 *
 */
#ifndef ALGORITHM_CALCULATE_24_H
#define ALGORITHM_CALCULATE_24_H


#include <cfloat>
#include <ostream>
#include "../../lang/exception/IllegalArgumentException.h"
#include "../../container/sequence/SingleLinkedList.h"
#include "../PermutationIterator.h"
#include "../../lang/exception/OutOfMemoryException.h"

#include "ArithmeticalOperation.h"

class Calculator24 {
public:
    static constexpr int target = 24;
    int *nums;

    void exec() const;

    Calculator24(int a, int b, int c, int d);

    virtual ~Calculator24();

    class ResultExpression {
    private:
        int i0;
        int i1;
        int i2;
        int a;
        int b;
        int c;
        int d;
        bool methodA;
    public:
        ResultExpression(int i0, int i1, int i2, int a, int b, int c, int d, bool methodA);

        friend std::ostream &operator<<(std::ostream &os, const Calculator24::ResultExpression &obj);
    };

};


#endif //ALGORITHM_CALCULATE_24_H
