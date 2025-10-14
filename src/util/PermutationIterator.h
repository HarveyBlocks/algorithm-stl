/**
 *
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/7/12
 *
 */
#ifndef ALGORITHM_PERMUTATION_ITERATOR_H
#define ALGORITHM_PERMUTATION_ITERATOR_H


#include "../lang/exception/IllegalStateException.h"
#include "Arrays.h"
/**
 * 给出全排列的各个情况
 */
class PermutationIterator {
private:
    Array<int> *nums;
    Array<int> *last;

    static void toNext(Array<int> &array);

public:
    explicit PermutationIterator(int n);

    virtual ~PermutationIterator();


    Array<int> &next(Array<int> &result);

    bool hasNext();

    void reset();
};


#endif //ALGORITHM_PERMUTATION_ITERATOR_H
