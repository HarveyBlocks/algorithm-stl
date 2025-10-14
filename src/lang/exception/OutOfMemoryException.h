#ifndef ALGORITHM_OUT_OF_MEMORY_EXCEPTION_H
#define ALGORITHM_OUT_OF_MEMORY_EXCEPTION_H

#include <utility>

#include "Exception.h"
#include "string"



class OutOfMemoryException : public Exception {
public:
    OutOfMemoryException(const std::string &msg, const Exception &cause) : Exception(msg, cause) {}

    OutOfMemoryException() : Exception() {}

    explicit OutOfMemoryException(const std::string &msg) : Exception(msg) {}


    [[nodiscard]] std::string message() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "OutOfMemoryException : \n" + this->Exception::message();
    }
};

#endif //ALGORITHM_OUT_OF_MEMORY_EXCEPTION_H
