#ifndef ALGORITHM_ILLEGAL_STATE_EXCEPTION_H
#define ALGORITHM_ILLEGAL_STATE_EXCEPTION_H

#include "Exception.h"
class IllegalStateException : public Exception {
public:
    IllegalStateException(const std::string &msg, const Exception &cause) :
            Exception(msg, cause) {}

    IllegalStateException() :
            Exception() {}

    explicit IllegalStateException(const std::string &msg) :
            Exception(msg) {}


    [[nodiscard]] std::string message() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "IllegalStateException : \n" + this->Exception::message();
    }
};




#endif //ALGORITHM_ILLEGAL_STATE_EXCEPTION_H
