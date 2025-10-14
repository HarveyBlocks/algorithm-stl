#ifndef ALGORITHM_DECODER_H
#define ALGORITHM_DECODER_H

template<class O, class C=unsigned long long>
class Decoder {
public:
    virtual O decode(C code) = 0;
};

#include "function/function.h"

template<class O, class C=unsigned long long>
using Decode = Function<O, C>;


#endif //ALGORITHM_DECODER_H
