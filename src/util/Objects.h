//
// Created by Lenovo on 2025/12/2.
//

#ifndef ALGORITHM_OBJECTS_H
#define ALGORITHM_OBJECTS_H

#include <string>
#include "../lang/exception/NullPointException.h"
#include "../lang/exception/IllegalStateException.h"
#include "../lang/exception/IllegalArgumentException.h"

class Objects {
private:
    Objects() {}

public:
    static void requireNonNull(void *p, const std::string &msg);

    static void requireTrue(bool condition, const std::string &msg);

    static void checkNonNull(void *p, const std::string &msg);

    static void checkTrue(bool condition, const std::string &msg);

    static void checkFalse(bool condition, const std::string &msg);
};


#endif //ALGORITHM_OBJECTS_H
