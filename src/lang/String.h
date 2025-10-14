/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/25
 *
 */
#ifndef ALGORITHM_STRING_H
#define ALGORITHM_STRING_H

#include <sstream>
#include "../container/sequence/ArrayList.h"
#include "Comparable.h"
#include "HashCode.h"


class String : public Comparable<String>, public SequentialAccessibleContainer<char> {

private:
    Array<char> *value;

    void setValue(const Array<char> &newArray);

    static int *getNext(const String &pattern, int *next);

    static int getFirst(const String &src, int begin, int len, const String &pattern, const int *next);

public:
    static int getFirstIndex(const String &src, const String &pattern, int begin = 0, int end = -1);

    [[nodiscard]] int getFirstIndex(const String &pattern, int begin = 0, int end = -1) const;

    [[nodiscard]] bool exist(const String &pattern, int begin = 0, int end = -1) const;

    static int strlen(const char *str, int limit = 1024);

    String();

    explicit String(const Array<char> &str);

    explicit String(int allocate);

    ~String();

    explicit String(const char *str);

    explicit String(char c);

    explicit operator Array<char>();

    String(const String &str);;

    [[nodiscard]] int getSize() const override;

    [[nodiscard]] bool empty() const override;


    void clone(String &target) const;

    static void copy(const String &src, String &target);

    char &operator[](int index) const override;

    [[nodiscard]] String subString(int start) const;

    [[nodiscard]] String subString(int start, int end, int step = 1) const;

    static Array<char> &concat(const String &before, const String &after, const String &target);

    static const int BUF_CAPACITY = 127;

    friend std::ostream &operator<<(std::ostream &os, const String &str);

    friend std::istream &operator>>(std::istream &is, String &str);

    [[nodiscard]] int compareTo(String o) const override;

    char *operator+(int offset) const override;

    template<class T>
    static String valueOf(const T &value) {
        std::stringstream ss;
        ss << value;
        String result;
        ss >> result;
        return result;
    }

    using std_ios_base = std::ios_base &(*)(std::ios_base &);

    template<class T>
    static String valueOf(const T &number, std_ios_base base) {
        std::stringstream ss;
        ss << base << number;
        String result;
        ss >> result;
        return result;
    }

    [[nodiscard]] bool equals(const String &str) const;

    bool operator==(const String &str) const;

    bool operator>(const String &str) const;

    bool operator>=(const String &str) const;

    bool operator<(const String &str) const;

    bool operator<=(const String &str) const;

    bool operator!=(const String &str) const;

    String &reverse();

    [[nodiscard]] String reverse() const;

    static int compare(const String &string1, const String &string2);

    explicit operator HashCode() const;

    [[nodiscard]] String trim() const;

    static bool isSpace(char c);

    String &operator=(const String &s);
};


#endif //ALGORITHM_STRING_H
