#ifndef ALGORITHM_COMPARATOR_H
#define ALGORITHM_COMPARATOR_H

#include <functional>

template<class T>
using Compare = std::function<int(const T &, const T &)>;

template<class T>
class Comparator {
public:
    /**
    * o1==o2?0:(o1>o2?1:-1)
    **/
    virtual int compare(const T &o1, const T &o2) const = 0;

    int operator()(const T &o1, const T &o2) const {
        return compare(o1, o2);
    }

    static int compareInt(int o1, int o2) {
        return o1 == o2 ? 0 : (o1 > o2 ? 1 : -1);
    }
};


class Comparators {
public:
    template<class T>
    static Compare<T> GREATER();

    template<class T>
    static Compare<T> LESSER();

    template<class T>
    static Compare<T> STRICT_GREATER();

    template<class T>
    static Compare<T> STRICT_LESSER();
};

template<class T>
Compare<T> Comparators::GREATER() {
    return [](const T &a, const T &b) {
        return a - b;
    };
}

template<class T>
Compare<T> Comparators::LESSER() {
    return [](const T &a, const T &b) { return b - a; };
}

template<class T>
Compare<T> Comparators::STRICT_GREATER() {
    return [](const T &a, const T &b) {
        return (a == b ? 0 : (a > b ? 1 : -1));
    };
}

template<class T>
Compare<T> Comparators::STRICT_LESSER() {
    return [](const T &a, const T &b) {
        return -(a == b ? 0 : (a > b ? 1 : -1));
    };
}

template<class T>
class ComparatorImpl : public Comparator<T> {
private:
    Compare<int> cmp;
public:
    explicit ComparatorImpl(const Compare<T> &cmp) : cmp(cmp) {}

    int compare(const T &o1, const T &o2) const override {
        return cmp(o1, o2);
    }
};

template<class T>
class Greater : public ComparatorImpl<T> {
public:
    Greater() : ComparatorImpl<T>(Comparators::GREATER<T>()) {}
};

template<class T>
class Lesser : public ComparatorImpl<T> {
public:
    Lesser() : ComparatorImpl<T>(Comparators::LESSER<T>()) {}
};


#endif //ALGORITHM_COMPARATOR_H
