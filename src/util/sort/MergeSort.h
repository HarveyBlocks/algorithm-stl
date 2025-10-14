#ifndef ALGORITHM_MERGE_SORT_H
#define ALGORITHM_MERGE_SORT_H

#include "ComparisonSort.h"

template<class T>
class MergeSort : public ComparisonSort<T> {
private:
    void mergePartition(int start, int end);

    void merge(int start, int mid, int end);


public:
    MergeSort(Array<T>& arr, const Compare<T> & cmp)
            : ComparisonSort<T>(arr, cmp) {}

    explicit MergeSort(Array<T>& arr, bool ascending = true)
            : ComparisonSort<T>(arr, ascending) {}

    void sort() override;
};

template<class T>
void MergeSort<T>::mergePartition(int start, int end) {
    if (1 >= end - start) {
        return;
    }
    int mid = (start + end) / 2;
    mergePartition(start, mid);
    mergePartition(mid, end);
    merge(start, mid, end);
}

template<class T>
void MergeSort<T>::sort() {
    this->mergePartition(0, this->arr.getSize());
}

template<class T>
void MergeSort<T>::merge(int start, int mid, int end) {
    // start, mid, end为索引
    // this->arr[start:mid]已排序
    // this->arr[mid:end]已排序
    int len1 = mid - start;
    int len2 = end - mid;

    // 合并两个数组, 合成一个新有序数组
    T temp1[len1];
    T temp2[len2];
    for (int i = 0; i < len1; i++) {
        temp1[i] = this->arr[start + i];
    }
    for (int i = 0; i < len2; i++) {
        temp2[i] = this->arr[mid + i];
    }
    int i = 0;
    int j = 0;
    int k = start;

    for (; k < end; k++) {
        if (i != len1 && (j == len2 || this->cmp(temp1[i], temp2[j]) < 0)) {
            this->arr[k] = temp1[i];
            i++;
        } else {
            this->arr[k] = temp2[j];
            j++;
        }
    }
}


#endif //ALGORITHM_MERGE_SORT_H
