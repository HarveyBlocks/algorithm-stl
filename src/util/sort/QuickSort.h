#ifndef ALGORITHM_QUICK_SORT_H
#define ALGORITHM_QUICK_SORT_H

#include "ComparisonSort.h"
#include "../../container/sequence/Stack.h"
#include "../Random.h"

template<class T>
class QuickSort : public ComparisonSort<T> {
private:
    void quickSort(int start, int end) {
        if (start + 1 >= end) {
            return;
        }
        int mid = hoarePartition(start, end);
        quickSort(start, mid);
        quickSort(mid + 1, end);
    }

    struct IndexBound {
        int start;
        int end;

        IndexBound(int start, int end) : start(start), end(end) {}
    };

    void quickSort() {
        Stack<IndexBound> st;
        st.push(IndexBound(0, this->arr.getSize()));
        while (!st.empty()) {
            IndexBound top = st.pop();
            int start = top.start;
            int end = top.end;
            if (end <= start) {
                continue;
            }
            int mid = this->hoarePartition(top.start, top.end);
            st.push(IndexBound(start, mid));
            st.push(IndexBound(mid + 1, end));
        }
    }

public:
    int randomPartition(int start, int end) {
        this->arr.elementSwap(Random::signedInt(start, end), start);
        return partition(start, end);
    }

    int partition(int start, int end) {
        T pivot = this->arr[end - 1]; // 选择枢轴(pivot)
        int slow = start;
        for (int fast = start; fast < end - 1; ++fast) {
            if (this->cmp(pivot, this->arr[fast]) > 0) {
                this->arr.elementSwap(slow++, fast);// 移到左边
            }
        }
        this->arr.elementSwap(slow, end - 1);
        return slow;
    }

    int hoarePartition(int start, int end) {
        T pivot = this->arr[start]; // 选择枢轴(pivot)
        int i = start;
        int j = end - 1;
        while (true) {
            for (; j > start && this->cmp(this->arr[j], pivot) > 0; --j);
            for (; i < end && this->cmp(this->arr[i], pivot) <= 0; ++i);
            if (i < j) {
                this->arr.elementSwap(i, j);
            } else {
                this->arr.elementSwap(start, j);
                return j;
            }
        }
    }

    /**
     * 便于理解的写法
     */
    [[deprecated("已废弃")]] int hoarePartitionEasy(int start, int end, T pivot, int i, int j);

    QuickSort(Array<T> &arr, const Compare<T> &cmp)
            : ComparisonSort<T>(arr, cmp) {}

    explicit QuickSort(Array<T> &arr, bool ascending = true)
            : ComparisonSort<T>(arr, ascending) {}

    void sort() override;
};

template<class T>
int QuickSort<T>::hoarePartitionEasy(int start, int end, T pivot, int i, int j) {
    while (true) {
        for (; j >= start && this->cmp(this->arr[j], pivot) >= 0; --j);
        if (i < j) {
            this->arr[i] = this->arr[j];
        } else {
            this->arr[i] = pivot;
            return i;
        }
        i++;
        for (; i < end && this->cmp(this->arr[i], pivot) < 0; ++i);
        if (i < j) {
            this->arr[j] = this->arr[i];
        } else {
            this->arr[j] = pivot;
            return j;
        }
        j--;
    }
}

template<class T>
void QuickSort<T>::sort() {
    this->quickSort(0, this->arr.getSize());
}

#endif //ALGORITHM_QUICK_SORT_H
