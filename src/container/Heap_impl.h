/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/24
 *
 */
#ifndef ALGORITHM_HEAP_IMPL_H
#define ALGORITHM_HEAP_IMPL_H

#include "Heap.h"

template<class T>
Heap<T>::operator Array<T>() {
    return this->arr;
}

template<class T>
T *Heap<T>::operator+(int offset) const {
    return arr.operator+(offset);
}

template<class T>
int Heap<T>::getSize() const {
    return this->heapSize;
}

template<class T>
int Heap<T>::allocate() const {
    return this->arr.getSize();
}

template<class T>
bool Heap<T>::empty() const {
    return arr.empty();
}

template<class T>
Heap<T>::Heap(const Array<T> &arr, const Compare<T> &cmp) :
        arr(arr),
        heapSize(arr.getSize()),
        cmp(cmp) {
    this->build();
}

template<class T>
T Heap<T>::extractFront() {
    if (this->heapSize < 0) {
        throw Exception("Heap underflow");
    }
    if (this->heapSize == 0) {
        throw Exception("Heap is Empty");
    }
    T front = this->arr[0];
    this->arr.elementSwap(0, this->heapSize - 1);
    this->heapSize--;
    this->heapify(0);
    return front;
}


template<class T>
void Heap<T>::heapify(int parentIndex) {
    int leftIndex = Heap::left(parentIndex);
    int rightIndex = Heap::right(parentIndex);
    int largest = parentIndex;
    if (rightIndex < this->heapSize && this->cmp(arr[rightIndex], arr[largest]) > 0) {
        largest = rightIndex;
    }
    if (leftIndex < this->heapSize && this->cmp(arr[leftIndex], arr[largest]) > 0) {
        largest = leftIndex;
    }
    if (largest != parentIndex) {
        this->arr.elementSwap(largest, parentIndex);
        this->heapify(largest);
    }
}


template<class T>
void Heap<T>::build() {
    heapSize = this->arr.getSize();
    int noLeafNum = (heapSize >> 1) - 1;
    for (int i = noLeafNum; i >= 0; --i) {
        heapify(i);
    }
}

template<class T>
Array<T> Heap<T>::sort() {
    while (this->heapSize > 0) {
        extractFront();
    }
    return this->arr;
}

#endif //ALGORITHM_HEAP_IMPL_H
