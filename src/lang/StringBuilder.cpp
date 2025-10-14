/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/25
 *
 */
#include "StringBuilder.h"


StringBuilder StringBuilder::create(const String &str) {
    return StringBuilder(str);
}


String StringBuilder::toString() const {
    Array<char> result(size);
    for (int i = 0; i < size;) {
        const String part = list.front();
        list.popFront();
        list.pushBack(part);
        int partSize = part.getSize();
        for (int j = 0; j < partSize; ++j, ++i) {
            result[i] = part[j];
        }
    }
    return String(result);
}

StringBuilder &StringBuilder::repeat(unsigned int count) {
    const StringBuilder part = *this;
    this->clear();
    while (count-- > 0) {
        this->append(part);
    }
    return *(this);
}

StringBuilder &StringBuilder::repeat(const StringBuilder &sb, unsigned int count) {
    StringBuilder temp(sb);
    this->append(temp.repeat(count));
    return *this;
}

StringBuilder &StringBuilder::append(const StringBuilder &str) {
    int queSize = str.list.getSize();
    for (int i = 0; i < queSize; ++i) {
        const String part = str.list.front();
        str.list.popFront();
        str.list.pushBack(part);
        list.pushBack(part);
    }
    this->size += str.size;
    return *(this);
}

StringBuilder &StringBuilder::append(const Array<char> &str) {
    return this->append(StringBuilder(str));
}

StringBuilder &StringBuilder::append(const char &c) {
    return this->append(StringBuilder(c));
}

StringBuilder &StringBuilder::append(const String &str) {
    return this->append(StringBuilder(str));
}

StringBuilder &StringBuilder::pushFront(const StringBuilder &part) {
    this->operator=(StringBuilder(part).append(*this));
    return *(this);
}

StringBuilder &StringBuilder::pushFront(const Array<char> &part) {
    return this->pushFront(StringBuilder(part));
}

StringBuilder &StringBuilder::pushFront(const char &c) {
    return this->pushFront(StringBuilder(c));
}

StringBuilder &StringBuilder::pushFront(const String &part) {
    return this->pushFront(StringBuilder(part));
}


StringBuilder::StringBuilder(const Array<char> &str) : StringBuilder() {
    list.pushBack(String(str));
    size += str.getSize();
}

StringBuilder::StringBuilder(const String &str) : StringBuilder() {
    list.pushBack(str);
    size += str.getSize();
}

StringBuilder::StringBuilder(const char &c) : StringBuilder() {
    list.pushBack(String(c));
    size++;
}

StringBuilder::StringBuilder(const StringBuilder &str) : StringBuilder() {
    this->operator=(str);
}

StringBuilder::StringBuilder() : size(0) {}

StringBuilder &StringBuilder::clear() {
    list.clear();
    this->size = 0;
    return *(this);
}


StringBuilder &operator*(const StringBuilder &str, const unsigned int &times) {
    return StringBuilder(str).repeat(times);
}

StringBuilder operator*(const String &str, const unsigned int &times) {
    return StringBuilder(str).repeat(times);
}

StringBuilder operator*(const Array<char> &str, const unsigned int &times) {
    return StringBuilder(str).repeat(times);
}

StringBuilder operator+(const String &before, const StringBuilder &after) {
    return StringBuilder(before).append(after);
}

StringBuilder operator+(const String &before, const String &after) {
    return StringBuilder(before).append(after);
}

StringBuilder &operator+(StringBuilder &before, const StringBuilder &after) {
    return before.append(after);
}

StringBuilder &operator+(StringBuilder &before, const String &after) {
    return before.append(after);
}

