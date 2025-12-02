/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/8/29
 *
 */
#ifndef ALGORITHM_BASE_OBJECT_H
#define ALGORITHM_BASE_OBJECT_H

#include <iostream>

class BaseObject {
    int hashCode() const {
        return 0;
    }

    std::ostream &print(std::ostream &os) const {
        return os << typeid(*this).name() << "@" << this->hashCode();
    }
};


#endif //ALGORITHM_BASEOBJECT_H
