#ifndef ALGORITHM_COUNT_SORT_H
#define ALGORITHM_COUNT_SORT_H

#include "SortAlgorithm.h"
#include "../Arrays.h"

class CountSort : public SortAlgorithm<int> {
public:
    explicit CountSort(Array<int> &arr) : SortAlgorithm(arr) {}

    void sort() override {
        // 适合整形排序, 小数量的(256不能再多了), 范围限定的, 范围不大的
        int len = this->arr.getSize();
        if (len <= 1) {
            return;
        }
        int init = this->arr[0];
        int maxInArr = init;
        int minInArr = init;
        // 已知数组中的最大值
        for (int i = 1; i < len; ++i) {
            int code = this->arr[i];
            if (code > maxInArr) {
                maxInArr = code;
            }
            if (code < minInArr) {
                minInArr = code;
            }
        }
        int scope = maxInArr - minInArr + 1;
        Array<int> indexLib(scope);
        for (int i = 0; i < scope; ++i) {
            indexLib[i] = 0;
        }

        for (int i = 0; i < len; ++i) {
            indexLib[this->arr[i] - minInArr]++; // 统计数量
        }
        indexLib[0]--;
        for (int i = 1; i < scope; ++i) {
            indexLib[i] += indexLib[i - 1];
        }
        Array<int> result(len);
        for (int i = len - 1; i >= 0; --i) {
            int element = this->arr[i]; // 210ms
            result[indexLib[element - minInArr]--] = element; // 530ms
        } // 740ms
        Array<int>::copy(result, arr); // 200ms
    }
};


#endif //ALGORITHM_COUNT_SORT_H
