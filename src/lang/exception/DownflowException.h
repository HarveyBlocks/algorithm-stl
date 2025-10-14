#ifndef ALGORITHM_DOWNFLOW_EXCEPTION_H
#define ALGORITHM_DOWNFLOW_EXCEPTION_H

#include "Exception.h"

class DownflowException :public Exception {
public:
    DownflowException(const std::string &msg, const Exception &cause) :
            Exception(msg, cause) {}

    DownflowException() :
            Exception() {}

    explicit DownflowException(const std::string &msg) :
            Exception(msg) {}


    [[nodiscard]] std::string message() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return "DownflowException : \n" + this->Exception::message();
    }
};


#endif //ALGORITHM_DOWNFLOW_EXCEPTION_H
