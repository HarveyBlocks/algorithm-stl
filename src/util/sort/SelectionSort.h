/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/9/13
 *
 */
#ifndef ALGORITHM_SELECTION_SORT_H
#define ALGORITHM_SELECTION_SORT_H


#include "ComparisonSort.h"

template<class T>
class SelectionSort : public ComparisonSort<T> {
public:
    explicit SelectionSort(Array<T> &arr, bool ascending = true) : ComparisonSort<T>(arr, ascending) {}

    SelectionSort(Array<T> &arr, const Compare<T> &cmp) : ComparisonSort<T>(arr, cmp) {}

    void sort() override {
        int size = this->arr.getSize();
        for (int i = 0; i < size-1; ++i) {
            int min = this->arr.at(i);
            int minIndex = i;
            for (int j = i + 1; j < size; ++j) {
                T &item = this->arr.at(j);
                if (this->cmp(item, min) < 0) {
                    min = item;
                    minIndex = j;
                }
            }
            this->arr.elementSwap(i, minIndex);
        }
    }
};


#endif //ALGORITHM_SELECTION_SORT_H
