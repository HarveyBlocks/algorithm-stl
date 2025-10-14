#ifndef ALGORITHM_BUCKET_SORT_H
#define ALGORITHM_BUCKET_SORT_H

#include "SortAlgorithm.h"
#include "../../container/sequence/SingleLinkedList.h"

/**
 * 暂且只考虑[0,1)的情况
 * 如果可以数值化, 那就可以归一化, 如果可以归一化, 那就可以[0,1)化, 那就可以参与此排序算法
 * 问题在于, 归一化有点耗时
 */
class BucketSort : public SortAlgorithm<double> {
public:
    explicit BucketSort(Array<double> &arr) : SortAlgorithm(arr) {}

    void sort() override;
};

void BucketSort::sort() {
    int n = this->arr.getSize();
    Array<SingleLinkedList<double>> buckets(n);
    for (int i = 0; i < n; ++i) {
        double &value = this->arr[i];
        buckets[(int) (n * value)].pushBack(value);
    }
    for (int i = 0; i < n; ++i) {
        if (!buckets[i].empty()) {
            buckets[i].sort(Comparators::STRICT_GREATER<double>());
        }
    }
    for (int i = 0, j = 0; i < n && j < n; i++) {
        while (!buckets[i].empty()) {
            double front = buckets[i].front();
            buckets[i].popFront();
            this->arr[j] = front;
            j++;
        }
    }
}


#endif //ALGORITHM_BUCKET_SORT_H
