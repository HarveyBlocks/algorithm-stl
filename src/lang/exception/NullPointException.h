#ifndef ALGORITHM_NULL_POINT_EXCEPTION_H
#define ALGORITHM_NULL_POINT_EXCEPTION_H

#include <utility>

#include "Exception.h"
#include "string"

class NullPointException : public Exception {
public:
    NullPointException(const std::string &msg, const Exception &cause) : Exception(msg, cause) {

    }

    NullPointException() : Exception("null") {

    }

    explicit NullPointException(const  std::string &msg) : Exception(msg) {

    }


    [[nodiscard]]  std::string message() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "NullPointException : \n" + this->Exception::message();
    }
};

#endif //ALGORITHM_NULL_POINT_EXCEPTION_H
