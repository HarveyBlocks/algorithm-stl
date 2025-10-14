#ifndef ALGORITHM_INDEX_OUT_OF_BOUND_EXCEPTION_H
#define ALGORITHM_INDEX_OUT_OF_BOUND_EXCEPTION_H

#include "Exception.h"


class IndexOutOfBoundException : public Exception {
public:
    IndexOutOfBoundException(const std::string &msg, const Exception &cause) :
            Exception(msg, cause) {}

    IndexOutOfBoundException() :
            Exception() {}

    explicit IndexOutOfBoundException(const std::string &msg) :
            Exception(msg) {}

    [[nodiscard]] std::string message() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "IndexOutOfBoundException : \n" + this->Exception::message();
    }
};


#endif //ALGORITHM_INDEX_OUT_OF_BOUND_EXCEPTION_H
