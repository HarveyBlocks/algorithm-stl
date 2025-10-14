/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/23
 *
 */
#ifndef ALGORITHM_PRIORITY_QUEUE_H
#define ALGORITHM_PRIORITY_QUEUE_H


#include "../Heap.h"
#include "../../util/Arrays.h"

template<class T>
class PriorityQueue {
private:
    Heap<T> heap;

    void increase(int index, T value) {
        if (this->cmp(value, this->arr[index]) < 0) {
            throw IllegalArgumentException("New priority is smaller than current key");
        }
        this->arr[index] = value;
        while (index > 0 && this->cmp(this->arr[index], this->arr[Heap<T>::parent(index)]) > 0) {
            // 如果当前节点和它爹倒反天罡了, 就换爹
            this->arr.elementSwap(index, Heap<T>::parent(index));
            index = Heap<T>::parent(index);
        }
    }


public:
    PriorityQueue(int allocate, const Compare<T> &cmp) : heap(Array<T>(allocate), cmp) {
        heap.build();
        heap.heapSize = 0;
    };

    void increase(T value) {
        int index = Arrays::binarySearch(heap.arr, value);
        if (index < 0) {
            // 没有!
            insertPrioriy(-index - 1, value);
        } else {
            increasePriority(index, value);
        }
    }

    void insert(int index, T value) {
        if (heap.heapSize > heap.allocate()) {
            throw IndexOutOfBoundException();
        }
        heap.heapSize++;
        int length = heap.heapSize;
        for (int j = length - 1; j > index; --j) {
            heap[j] = heap[j - 1];
        }
        heap[index] = value;
    }

    T front() {
        return heap[0];
    }

    T pop() {
        if (heap.heapSize <= 0) {
            throw IndexOutOfBoundException();
        }
        int size = heap.heapSize--;
        T front = this->front();
        for (int j = size; j > size; --j) {
            heap[j - 1] = heap[j];
        }
        return front;
    }
};


#endif //ALGORITHM_PRIORITY_QUEUE_H
