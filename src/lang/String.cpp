/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/25
 *
 */
#include "String.h"

int String::strlen(const char *str, int limit) {
    for (int i = 0; i < limit; ++i) {
        if (str[i] == '\0') {
            return i;
        }
    }
    return -1;
}

String::String() : value(new Array<char>("", 0)) {}

String::String(const Array<char> &str) : value(new Array<char>(str)) {}

String::~String() {
    delete value;
}


String::String(const char *str) {
    if (str == nullptr) {
        this->value = new Array<char>("", 0);
    }
    value = new Array<char>(str, String::strlen(str));
}

String::String(const char c) : value(new Array<char>(&c, 1)) {

}

String::operator Array<char>() {
    return *this->value;
}


String::String(const String &str) {
    if (str.value == nullptr) {
        this->value = new Array<char>("", 0);
        return;
    }
    this->value = new Array<char>(*(str.value));
}

int String::getSize() const {
    return value->getSize();
}

bool String::empty() const {
    return value->empty();
}

void String::clone(String &target) const {
    String::copy(*this, target);
}

void String::copy(const String &src, String &target) {
    Array<char>::copy(*(src.value), *(target.value));
}

char &String::operator[](int index) const {
    return (*value)[index];
}

String String::subString(int start) const {
    return String((*value).subArray(start));
}

String String::subString(int start, int end, int step) const {
    return String(value->subArray(start, end, step));
}

Array<char> &String::concat(const String &before, const String &after, const String &target) {
    return Array<char>::concat(*(before.value), *(after.value), *(target.value));
}

String::String(const int allocate) : value(new Array<char>(allocate)) {}

void String::setValue(const Array<char> &newArray) {
    delete value;
    this->value = new Array<char>(newArray);
}

std::ostream &operator<<(std::ostream &os, const String &str) {
    if (str.empty()) {
        return os;
    }
    char buf[String::BUF_CAPACITY + 1];
    char *src = str.value->operator+(0);
    int size = str.getSize();
    size = size - size % (String::BUF_CAPACITY);
    int i = 0;
    for (; i < size; i += String::BUF_CAPACITY) {
        Array<char>::copy(src + i, buf, String::BUF_CAPACITY);
        buf[String::BUF_CAPACITY] = '\0';
        os << buf;
    }
    int leave = str.getSize() % (String::BUF_CAPACITY);
    Array<char>::copy(src + i, buf, leave);
    buf[leave] = '\0';
    return os << buf;
}

std::istream &operator>>(std::istream &is, String &str) {
    char buf[String::BUF_CAPACITY];
    ArrayList<char> temp;
    // 拷贝逻辑
    is.getline(buf, String::BUF_CAPACITY);
    if (is.eof()) {
        temp.concat(Array<char>(buf, String::strlen(buf)));
    }
    while (!is.eof()) {  //按行拷贝   A行
        temp.concat(Array<char>(buf, String::strlen(buf)));
        if (!is.fail()) {
            temp.add('\n');
        }
        is.clear();
        is.getline(buf, String::BUF_CAPACITY);
        if (is.eof()) { //处理最后一行；
            temp.concat(Array<char>(buf, String::strlen(buf)));
        }
    }
    str.setValue(temp.getArray());
    return is;
}

bool String::equals(const String &str) const {
    return this->operator==(str);
}

bool String::operator==(const String &str) const {
    return String::compare(*this, str) == 0;
}

bool String::operator>(const String &str) const {
    return String::compare(*this, str) > 0;
}

bool String::operator>=(const String &str) const {
    return String::compare(*this, str) >= 0;
}

bool String::operator<(const String &str) const {
    return String::compare(*this, str) < 0;
}

bool String::operator<=(const String &str) const {
    return String::compare(*this, str) <= 0;
}

bool String::operator!=(const String &str) const {
    return String::compare(*this, str) != 0;
}

int String::compare(const String &string1, const String &string2) {
    Array<char> *str1 = string1.value;
    Array<char> *str2 = string2.value;
    int len = std::min(str1->getSize(), str2->getSize());
    for (int i = 0; i < len; ++i) {
        char &c1 = (*str1)[i];
        char &c2 = (*str2)[i];
        if (c1 != c2) {
            return c1 - c2;
        }
    }
    return str1->getSize() - str2->getSize();
}

int String::compareTo(String o) const {
    return String::compare(*this, o);
}

String String::reverse() const {
    int len = this->value->getSize();
    Array<char> *srcArray = this->value;
    Array<char> reverseArray(len);
    for (int i = 0; i < len; ++i) {
        reverseArray[len - i - 1] = srcArray->operator[](i);
    }
    return String(reverseArray);
}

String::operator HashCode() const {
    // 参考Java的hashCode();
    HashCode hashCode = 0;
    int length = value->getSize() >> 1;
    for (int i = 0; i < length; i++) {
        hashCode = 31 * hashCode + (*value)[i];
    }
    return hashCode;
}

String &String::reverse() {
    this->value->reverse();
    return *this;
}

int *String::getNext(const String &pattern, int *next) {
    next[0] = -1; // 不需要定义, 随便他, 反正不会被访问到
    next[1] = 0;  // 一定是0
    int size = pattern.getSize();
    for (int i = 1, j = 0; i < size; i++) { // 注意i从1开始
        while (j > 0 && pattern[i] != pattern[j]) { // 前后缀不相同了
            j = next[j]; // 向前回退
            // 前后缀不相同了, 需要依据前缀表后退
            // 一直不同就一直后退
        }
        if (pattern[i] == pattern[j]) { // 找到相同的前后缀
            j++;
        }
        next[i + 1] = j /*- 1*/; // 将j（前缀的长度）赋给next[i+1], 就是next后移一位
    }
    return next;
}

int String::getFirst(const String &src, int begin, int end, const String &pattern, const int *next) {
    for (int i = begin, j = 0; i < end; i++) {
        while (j > 0 && src[i] != pattern[j]) {
            j = next[j];
            // 前后缀不相同了, 需要依据前缀表后退
            // 一直不同就一直后退
        }
        if (src[i] == pattern[j]) {
            // 找到相同的前后缀
            j++;
        }
        if (j == pattern.getSize()) {
            // 此时匹配, 由于被匹配, 此时j指向pattern最后的下一个
            return i - j + 1; // 找重复字符串也可以这里改变-> 不return而是count++
        }
    }
    return -1;
}

int String::getFirstIndex(const String &src, const String &pattern, int begin, int end) {
    int next[pattern.getSize()];
    getNext(pattern, next);
    if (end < 0) {
        // 自动调整
        end = src.getSize();
    }
    return getFirst(src, begin, end, pattern, next);
}


int String::getFirstIndex(const String &pattern, int begin, int end) const {
    return String::getFirstIndex(*this, pattern, begin, end);
}

bool String::exist(const String &pattern, int begin, int end) const {
    return getFirstIndex(pattern, begin, end) >= 0;
}

char *String::operator+(int offset) const {
    return &this->operator[](offset);
}

String String::trim() const {
    int len = this->value->getSize();
    int start = 0;
    for (; start < len; ++start) {
        if (!isSpace(this->at(start))) {
            break;
        }
    }
    int end = len - 1;
    for (; end > 0 && end > start; --end) {
        if (!isSpace(this->at(end))) {
            break;
        }
    }
    return this->subString(start, end + 1);
}

bool String::isSpace(char c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

String &String::operator=(const String &s) {

    delete value;
    this->value = new Array<char>(*(s.value));
    return *this;
}


