/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/24
 *
 */
#ifndef ALGORITHM_UNAUTHORIZED_EXCEPTION_H
#define ALGORITHM_UNAUTHORIZED_EXCEPTION_H


#include "Exception.h"

class UnauthorizedException : public Exception {
public:
    UnauthorizedException(const std::string &msg, const Exception &cause) : Exception(msg, cause) {

    }

    UnauthorizedException() : Exception() {

    }

    explicit UnauthorizedException(const std::string &msg) : Exception(msg) {

    }

    [[nodiscard]] std::string message() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "UnauthorizedException : \n" + this->Exception::message();
    }
};

#endif //ALGORITHM_UNAUTHORIZED_EXCEPTION_H
