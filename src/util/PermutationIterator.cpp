/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/7/12
 *
 */
#include "PermutationIterator.h"

void PermutationIterator::toNext(Array<int> &array) {
    int len = array.getSize();
    if (len <= 1) {
        return;
    }
    int i = len - 2;
    // 56784321
    // i指向索引, 表示从最右端开始检查, 不符合升序的部分
    for (; i > 0 && array[i] > array[i + 1]; --i);
    // 56 7 8 4321
    // 56 7 8 4321
    //  8 7 654321
    // 56784321
    // 56812347
    int j = len - 1;
    // 找到大于i的j所在
    for (; j >= 0 && array[i] > array[j]; --j);
    if (j < 0) {
        // 没找到,说明已经完成升序
        throw IllegalStateException("Doesn't have next");
    }
    array.elementSwap(i, j);
    // 倒置array的后半本来有序的部分, 表示从头开始
    array.reverse(i + 1, len - 1);
}

PermutationIterator::PermutationIterator(int n) : nums(new Array<int>(n)), last(new Array<int>(n)) {
    for (int i = 0; i < n; ++i) {
        (*nums)[i] = i;
    }
    nums->clone(*last);
}

PermutationIterator::~PermutationIterator() {
    delete nums;
    delete last;
}

Array<int> &PermutationIterator::next(Array<int> &result) {
    if (!hasNext()) {
        last->clone(result);
        return result;
    }
    nums->clone(*last);
    PermutationIterator::toNext(*nums);
    last->clone(result);
    return result;
}

bool PermutationIterator::hasNext() {
    return !Arrays::checkSorted(*(this->last), Comparators::GREATER<int>(), false);
}

void PermutationIterator::reset() {
    int n = nums->getSize();
    for (int i = 0; i < n; ++i) {
        (*nums)[i] = i;
    }
    nums->clone(*last);
}
