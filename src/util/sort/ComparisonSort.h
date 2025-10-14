#ifndef ALGORITHM_COMPARISON_SORT_H
#define ALGORITHM_COMPARISON_SORT_H

#include "SortAlgorithm.h"
#include "../Comparator.h"



template<class T>
class ComparisonSort : public SortAlgorithm<T> {
protected:

    Compare<T> cmp;

public:
    ComparisonSort(Array<T> &arr, const Compare<T> &cmp) :
            SortAlgorithm<T>(arr), cmp(cmp) {
        if (arr.empty()) {
            throw NullPointException("arr");
        }
    }

    explicit ComparisonSort(Array<T> &arr, bool ascending = true) :
            ComparisonSort(arr, ascending ? Comparators::GREATER<T>() : Comparators::LESSER<T>()) {
    }
};


#endif //ALGORITHM_COMPARISON_SORT_H
