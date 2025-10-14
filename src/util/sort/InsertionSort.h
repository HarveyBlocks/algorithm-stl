#ifndef ALGORITHM_INSERTION_SORT_H
#define ALGORITHM_INSERTION_SORT_H

#include "ComparisonSort.h"
#include "../Arrays.h"

template<class T>
class InsertionSort : public ComparisonSort<T> {
public:
    InsertionSort(Array<T> &arr, const Compare<T> &cmp)
            : ComparisonSort<T>(arr, cmp) {}

    explicit InsertionSort(Array<T> &arr, bool ascending = true)
            : ComparisonSort<T>(arr, ascending) {}

    void sort() override;
};

template<class T>
void InsertionSort<T>::sort() {
    for (int i = 0; i < this->arr.getSize(); ++i) {
        T key = this->arr[i];
        //  Insert this->arr[i] into the sorted sequence A[1 ... i —1].
        int j = i - 1;
        for (; j >= 0 && this->cmp(this->arr[j], key) > 0; j--) {
            this->arr[j + 1] = this->arr[j];
        }
        this->arr[j + 1] = key;
    }
}

/**
 * 折半查找+插入排序
 */
template<class T>
class BinarySearchInsertionSort : public ComparisonSort<T> {
private:
    /**
     *
     * @param index 要进行二叉查找的区域, 结束处的索引, 包括
     */
    int findInsertIndex(int index, T key) const;

public:
    BinarySearchInsertionSort(Array<T> &arr, const Compare<T> &cmp)
            : ComparisonSort<T>(arr, cmp) {}

    explicit BinarySearchInsertionSort(Array<T> &arr, bool ascending = true)
            : ComparisonSort<T>(arr, ascending) {}

    void sort() override;
};

template<class T>
void BinarySearchInsertionSort<T>::sort() {
    for (int i = 1; i < this->arr.getSize(); ++i) {
        T key = this->arr[i];
        int j = i - 1;
        int insertIndex = findInsertIndex(i - 1, key);
        for (; j >= insertIndex; j--) {
            this->arr[j + 1] = this->arr[j];
        }
        this->arr[j + 1] = key;
    }
}

template<class T>
int BinarySearchInsertionSort<T>::findInsertIndex(int index, T key) const {
    // 对已经有顺序的部分折半查找减少查找, 比较次数
    // 但插入需要挪动, 赋值交换次数不变
    // 但是每次查找都要创建一个新的数组, 进行
    int insertIndex = Arrays::binarySearch(this->arr, key, this->cmp, 0, index, 1);
    if (insertIndex < 0) {
        insertIndex = -insertIndex - 1;
    } else {
        insertIndex++;// 如果相同, 就插入后面, 保证排序的稳定性(原来在后面的还在后面)
    }
    return insertIndex;
}

/**
 * 希尔排序
 */
template<class T>
class ShellSort : public ComparisonSort<T> {
private:
    /**
     *
     * @param start 需要进行二叉查找的区域,索引, 包括
     * @param end 需要进行二叉查找的区域,索引, 包括
     */
    int findInsertIndex(int start, int end, T key, int step) const;

    void sort0(int start, int direct);

public:
    ShellSort(Array<T> &arr, const Compare<T> &cmp)
            : ComparisonSort<T>(arr, cmp) {}

    explicit ShellSort(Array<T> &arr, bool ascending = true)
            : ComparisonSort<T>(arr, ascending) {}

    void sort() override;

};

template<class T>
int ShellSort<T>::findInsertIndex(int start, int end, T key, int step) const {
    if (end < 0) {
        return 0;
    }
    int insertIndex = Arrays::binarySearch(this->arr, key, this->cmp, start, end, step);
    if (insertIndex < 0) {
        insertIndex = -insertIndex - step;
    } else {
        insertIndex++;// 如果相同, 就插入后面, 保证排序的稳定性(原来在后面的还在后面)
    }
    return insertIndex;
}


template<class T>
void ShellSort<T>::sort() {
    for (int direct = this->arr.getSize() >> 1; direct > 0; direct >>= 1) {
        for (int start = 0; start < direct; ++start) {
            sort0(start, direct);
        }
    }
}

template<class T>
void ShellSort<T>::sort0(int start, int direct) {
    int size = this->arr.getSize();
    for (int i = start; i < size; i += direct) {
        T key = this->arr[i];
        int j = i - direct;
        int insertIndex = findInsertIndex(start, j, key, direct);
        for (; j >= insertIndex
            /*j >= 0 && this->cmp(this->arr[j], key) > 0*/;
               j -= direct) {
            this->arr[j + direct] = this->arr[j];
        }
        this->arr[j + direct] = key;
    }
}


#endif //ALGORITHM_INSERTION_SORT_H
