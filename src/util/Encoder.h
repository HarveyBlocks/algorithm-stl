#ifndef ALGORITHM_ENCODER_H
#define ALGORITHM_ENCODER_H

template<class O, class C=unsigned long long>
class Encoder {
public:
    virtual C encode(const O& obj) = 0;
};


#include "function/function.h"

template<class O, class C=unsigned long long>
using Encode = Function<const O&, C>;
#endif //ALGORITHM_ENCODER_H
