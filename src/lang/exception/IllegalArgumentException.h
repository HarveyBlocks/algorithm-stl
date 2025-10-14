#ifndef ALGORITHM_ILLEGAL_ARGUMENT_EXCEPTION_H
#define ALGORITHM_ILLEGAL_ARGUMENT_EXCEPTION_H

#include "Exception.h"

class IllegalArgumentException :public Exception {
public:
    IllegalArgumentException(const std::string &msg, const Exception &cause) :
            Exception(msg, cause) {}

    IllegalArgumentException() :
            Exception() {}

    explicit IllegalArgumentException(const std::string &msg) :
            Exception(msg) {}

    [[nodiscard]] std::string message() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "IllegalArgumentException : \n" + this->Exception::message();
    }
};


#endif //ALGORITHM_ILLEGAL_ARGUMENT_EXCEPTION_H
