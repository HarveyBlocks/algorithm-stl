/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/9/1
 *
 */
#ifndef ALGORITHM_DIVIDE_ZERO_EXCEPTION_H
#define ALGORITHM_DIVIDE_ZERO_EXCEPTION_H

#include "Exception.h"

class DivideZeroException : public Exception {
public:
    DivideZeroException(const std::string &msg, const Exception &cause) :
            Exception(msg, cause) {}

    DivideZeroException() :
            Exception() {}

    explicit DivideZeroException(const std::string &msg) :
            Exception(msg) {}


    [[nodiscard]] std::string message() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "DivideZeroException : \n" + this->Exception::message();
    }
};


#endif //ALGORITHM_DIVIDE_ZERO_EXCEPTION_H
