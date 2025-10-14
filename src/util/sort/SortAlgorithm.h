#ifndef ALGORITHM_SORT_ALGORITHM_H
#define ALGORITHM_SORT_ALGORITHM_H


#include "../../lang/Array.h"
#include "../../lang/exception/NullPointException.h"
#include "iostream"

template<class T>
class SortAlgorithm {
private:
    mutable int count = 0;
protected:
    Array<T> &arr;

    void incr() const {
        this->count++;
    }

    void reset() const {
        this->count = 0;
    }

    void showCount(std::ostream& os) const {
        os << "O: " << count << "/" << this->arr.getSize() << std::endl;
    }

public:
    explicit SortAlgorithm(Array<T> &arr) :
            arr(arr) {
        if (arr.empty()) {
            throw NullPointException("arr");
        }
    }


    virtual void sort() = 0;

};


#endif //ALGORITHM_SORT_ALGORITHM_H
