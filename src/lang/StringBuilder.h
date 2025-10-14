/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/25
 *
 */
#ifndef ALGORITHM_STRING_BUILDER_H
#define ALGORITHM_STRING_BUILDER_H

#include "String.h"
#include "../container/sequence/SingleLinkedList.h"

class String;

class StringBuilder {
private:
    int size;
    SingleLinkedList<String> list;
public:
    explicit StringBuilder(const String &str);

    explicit StringBuilder(const char &str);

    StringBuilder(const StringBuilder &str);

    explicit StringBuilder(const Array<char> &str);

    explicit StringBuilder();

    ~StringBuilder() = default;

    StringBuilder &append(const String &str);

    StringBuilder &append(const char &str);

    StringBuilder &append(const Array<char> &str);

    StringBuilder &append(const StringBuilder &str);

    StringBuilder &repeat(unsigned int count);

    StringBuilder &repeat(const StringBuilder &sb, unsigned int count);

    StringBuilder &pushFront(const char &c);

    StringBuilder &pushFront(const String &part);

    StringBuilder &pushFront(const Array<char> &part);

    StringBuilder &pushFront(const StringBuilder &part);

    String toString() const;

    StringBuilder &clear();

    static StringBuilder create(const String &str);

    explicit operator String() const {
        return this->toString();
    }

    friend std::ostream &operator<<(std::ostream &os, const StringBuilder &sb) {
        return os << sb.toString();
    }

    StringBuilder &operator=(const StringBuilder &sb) {
        this->clear();
        this->append(sb);
        return *this;
    }
};

StringBuilder &operator+(StringBuilder &before, const StringBuilder &after);

StringBuilder &operator+(StringBuilder &before, const String &after);

StringBuilder operator+(const String &before, const StringBuilder &after);

StringBuilder operator+(const String &before, const String &after);

StringBuilder operator*(const Array<char> &str, const unsigned int &times);

StringBuilder operator*(const String &str, const unsigned int &times);

StringBuilder &operator*(const StringBuilder &str, const unsigned int &times);


#endif //ALGORITHM_STRING_BUILDER_H
