#ifndef ALGORITHM_HEAP_H
#define ALGORITHM_HEAP_H

#include "../lang/exception/IllegalArgumentException.h"
#include "../util/Comparator.h"
#include "../lang/Array.h"
#include "../lang/exception/UnauthorizedException.h"


template<class T>
class PriorityQueue;

template<class T>
class Heap :public SequentialAccessibleContainer<T> {
private:
    friend class PriorityQueue<T>;

    Array<T> arr;

    int heapSize;

    Compare<T> cmp;


    static int parent(int child) {
        return (child - 1) >> 1;
    }

    static int left(int parent) {
        return (parent << 1) + 1;
    }

    static int right(int parent) {
        return (parent << 1) + 2;
    }

    void heapify(int parentIndex);

    void build();

public:
    T &operator[](int index) const override {
        throw UnauthorizedException();
    }

    T *operator+(int offset) const override;

    [[nodiscard]] int getSize() const override;

    [[nodiscard]] bool empty() const override;

    [[nodiscard]] int allocate() const;

    Heap(const Array<T> &arr, const Compare<T> &cmp);


    T extractFront();

    Array<T> sort();

    friend std::ostream &operator<<(std::ostream &os, const Heap<T> &heap) {
        return os << heap.arr;
    }

    explicit operator Array<T>();
};

#include "Heap_impl.h"

#endif //ALGORITHM_HEAP_H
