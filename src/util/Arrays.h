#ifndef ALGORITHM_ARRAYS_H
#define ALGORITHM_ARRAYS_H

#include "../lang/Array.h"
#include "../util/sort/QuickSort.h"
#include "../lang/exception/IllegalArgumentException.h"


class Arrays {
private:
    Arrays() {}

    template<class T>
    static T randomSelect(Array<T> &arr, int start, int end, int level);

public:
    template<class T>
    static int binarySearch(const Array<T> &arr, T key, Compare<T> compare, bool ascending = true) {
        return binarySearch(arr, key, compare, 0, arr.getSize() - 1, 1, ascending);
    }

    /**
     * @param low 索引, 包含
     * @param high 索引, 包含
     */
    template<class T>
    static int binarySearch(const Array<T> &arr, T key, Compare<T> compare,
                            int low, int high, int step = 1,
                            bool ascending = true) {
        if (step < 0) {
            throw IllegalArgumentException();
        }
        unsigned int num = (high - low) / step;
        if (high - low != num * step) {
            throw IllegalArgumentException();
        }
        int weight = ascending ? 1 : -1;
        while (low <= high) {

            num = (high - low) / step;
            int mid = (int) (low + (num >> 1) * step); // TODO 0

            long midVal = arr[mid];
            int cmpResult = compare(midVal, key) * weight;
            if (cmpResult < 0) {
                low = mid + step; // TODO 1
            } else if (cmpResult > 0) {
                high = mid - step; // TODO 1
            } else {
                return (int) mid; // key found
            }
        }
        return -(low + 1);  // key not found.
    }

    template<class T>
    static bool checkSorted(const Array<T> &arr, Compare<T> compare, bool ascending = true) {
        return checkSorted(arr, compare, 0, arr.getSize() - 1, 1, ascending);
    }

    /**
     * @param low 索引, 包含
     * @param high 索引, 包含
     */
    template<class T>
    static bool checkSorted(const Array<T> &arr, Compare<T> compare,
                            int low, int high, int step = 1,
                            bool ascending = true) {
        if (step < 0) {
            throw IllegalArgumentException();
        }
        unsigned int num = (high - low) / step;
        if (high - low != num * step) {
            throw IllegalArgumentException();
        }
        int wight = ascending ? 1 : -1;
        bool sorted = true;
        for (int i = low; sorted && i < high; i += step) {
            int cmp = compare(arr[i], arr[i + step]) * wight;
            if (cmp > 0) {
                sorted = false;
            }
        }
        return sorted;
    }

    template<class T>
    static bool same(const Array<T> &arr1, const Array<T> &arr2);

    template<class T>
    static T tail(Array<T> &arr, int level);

    /**
     * 因为会对数组内容发生改变, 所以得先拷贝一遍(悲)
     */
    template<class T>
    static T head(Array<T> &arr, int level);
};

template<class T>
bool Arrays::same(const Array<T> &arr1, const Array<T> &arr2) {
    if (arr1.getSize() != arr2.getSize()) {
        return false;
    }
    for (int i = 0; i < arr1.getSize(); ++i) {
        if ((arr1[i] - arr2[i]) != 0) {
            return false;
        }
    }
    return true;
}

template<class T>
T Arrays::head(Array<T> &arr, int level) {
    return Arrays::tail(arr, arr.getSize() - level + 1);
}

template<class T>
T Arrays::tail(Array<T> &arr, const int level) {
    // level = 1表示smallest, index = 0
    if (level <= 0 || level > arr.getSize()) {
        throw IllegalArgumentException();
    }
    return Arrays::randomSelect(arr, 0, arr.getSize(), level - 1);
}


template<class T>
T Arrays::randomSelect(Array<T> &arr, int start, int end, int level) {
    if (start == end) {
        return arr[start];
    }
    int mid = QuickSort<T>(arr).randomPartition(start, end);
    int count = mid /* - start + 1*/;
    if (level == count) {
        return arr[mid];
    } else if (level < count) {
        return Arrays::randomSelect(arr, start, mid, level);
    } else {
        return Arrays::randomSelect(arr, mid + 1, end, level);
    }
}

#include "function/function.h"

class ArrayInitializer {
public:
    template<class T>
    static void init(const Array<T> &test, Producer<T> producer) {
        for (int j = 0; j < test.getSize(); ++j) {
            test[j] = producer();
        }
    }

    static void init(const Array<double> &test) {
        for (int j = 0; j < test.getSize(); ++j) {
            test[j] = Random::random();
        }
    }
};

#endif //ALGORITHM_ARRAYS_H
