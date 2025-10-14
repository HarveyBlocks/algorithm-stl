/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/24
 *
 */
#ifndef ALGORITHM_OVERFLOW_EXCEPTION_H
#define ALGORITHM_OVERFLOW_EXCEPTION_H


#include "Exception.h"

class OverflowException : public Exception {
public:
    OverflowException(const std::string &msg, const Exception &cause) :
            Exception(msg, cause) {}

    OverflowException() :
            Exception() {}

    explicit OverflowException(const std::string &msg) :
            Exception(msg) {}

    [[nodiscard]] std::string message() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "OverflowException : \n" + this->Exception::message();
    }
};


#endif //ALGORITHM_OVERFLOW_EXCEPTION_H
