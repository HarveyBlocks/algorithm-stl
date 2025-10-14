#ifndef ALGORITHM_EXCEPTION_H
#define ALGORITHM_EXCEPTION_H

#include "string"

class Exception :  std::exception {
private:
    std::string msg;
    Exception *exception = nullptr;

    Exception(const Exception &cause) = default;

    [[nodiscard]] const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return exception::what();
    }

public:
    explicit Exception(const  std::string &msg, const Exception &cause) : msg(msg + "\n"), exception(new Exception(cause)) {

    }

    explicit Exception(const  std::string &msg) : msg(msg + "\n"), exception(nullptr) {

    }


    explicit Exception() = default;

    [[nodiscard]] virtual  std::string message() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
        std::string str = "Exception : " + msg + "\n";
        if (exception != nullptr) {
            str += exception->message();
        }
        return str;
    }

    virtual ~Exception() _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
        delete exception;
    }
};

#endif //EXPERIMENT4_EXCEPTION_H
