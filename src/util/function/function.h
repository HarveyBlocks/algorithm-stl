#ifndef ALGORITHM_FUNCTION_H
#define ALGORITHM_FUNCTION_H

#include <functional>

template<class T>
using Consumer = std::function<void(T)>;
template<class T, class U>
using BiConsumer = std::function<void(T, U)>;
template<class R>
using Producer = std::function<R()>;
template<class P, class R>
using Function = std::function<R(P)>;
template<class P, class Q, class R>
using BiFunction = std::function<R(P, Q)>;
template<class T>
using BinaryOperator = BiFunction<T, T, T>;


#endif //ALGORITHM_FUNCTION_H
