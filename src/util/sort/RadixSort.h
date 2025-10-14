#ifndef ALGORITHM_RADIX_SORT_H
#define ALGORITHM_RADIX_SORT_H

#include "SortAlgorithm.h"
#include "CountSort.h"
#include "../Arrays.h"
#include "../../lang/exception/IllegalArgumentException.h"

//template<class T>
class RadixSort :public SortAlgorithm<unsigned int> {
private:
    static const int MAX_BYTE = 256;

    static unsigned char catchByte(unsigned int ele, unsigned int byteIndex) {
        return (unsigned char) ((ele >> (byteIndex * 8U)) & 0xffU);
    }

public:
    explicit RadixSort(Array<unsigned int> &arr) : SortAlgorithm<unsigned int>(arr) {}

    /**
     * @example
     * sortByLabel(4,0)-><p>
     * label = 0xff_ff_ff_ff<p>
     *          3   2   1   0<p>
     * sorted by element&label
     */
    void sortByLabel(int startByteIndex, int endByteIndex) {
        if (startByteIndex <= endByteIndex || startByteIndex < 0 || endByteIndex < 0) {
            throw IllegalArgumentException(
                    "startByteIndex=" + std::to_string(startByteIndex)
                    + " & endByteIndex=" + std::to_string(endByteIndex));
        }
        int scope = MAX_BYTE;
        int len = this->arr.getSize();
        int indexLib_[scope];
        Array<int> indexLib(indexLib_, scope);
        for (int x = endByteIndex; x < startByteIndex; ++x) {
            /*for (int i = 0; i < scope; ++i) {
                indexLib[i] = 0;
            }*/
            indexLib.reset(0);
            for (int i = 0; i < len; ++i) {
                indexLib[catchByte(this->arr[i], x)]++; // 统计数量
            }
            // indexLib[0]--;
            for (int i = 1; i < scope; ++i) {
                indexLib[i] += indexLib[i - 1];
            }
            unsigned int result_[len];
            Array<unsigned int> result(result_, len);
            for (int i = len - 1; i >= 0; --i) {
                unsigned int element = this->arr[i]; // 210ms
                result[--indexLib[catchByte(element, x)]] = element; // 530ms
            } // 740ms
            Array<unsigned int>::copy(result, arr); // 200ms
        }
    }

    void sort() override {
        sortByLabel(4, 0);
    }
};


#endif //ALGORITHM_RADIX_SORT_H
