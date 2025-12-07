//
// Created by Lenovo on 2025/12/2.
//

#include "Objects.h"

void Objects::requireNonNull(void *p, const std::string &msg) {
    if (p == nullptr) {
        throw IllegalArgumentException(msg);
    }
}

void Objects::requireTrue(bool condition, const std::string &msg) {
    if (!condition) {
        throw IllegalArgumentException(msg);
    }
}

void Objects::checkNonNull(void *p, const std::string &msg) {
    if (p == nullptr) {
        throw IllegalStateException(msg);
    }
}

void Objects::checkTrue(bool condition, const std::string &msg) {
    if (!condition) {
        throw IllegalStateException(msg);
    }
}

void Objects::checkFalse(bool condition, const std::string &msg) {
    if (condition) {
        throw IllegalStateException(msg);
    }
}
