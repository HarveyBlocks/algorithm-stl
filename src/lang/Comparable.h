#ifndef ALGORITHM_COMPARABLE_H
#define ALGORITHM_COMPARABLE_H

template<class T>
class Comparable {
public:
    /*
     * this==o?0:(this>o?1:-1)
     */
    [[nodiscard]]  virtual int compareTo(T o) const = 0;
};

template<class T>
class StrictComparable : public Comparable<T> {
public:
    virtual bool operator>(T calculator) const {
        return this->compareTo(calculator) > 0;
    }

    virtual bool operator<(T calculator) const {
        return this->compareTo(calculator) < 0;
    }

    virtual bool operator==(T calculator) const {
        return this->compareTo(calculator) == 0;
    }

    virtual bool operator!=(T calculator) const {
        return this->compareTo(calculator) != 0;
    }

    virtual bool operator>=(T calculator) const {
        return this->compareTo(calculator) >= 0;
    }

    virtual bool operator<=(T calculator) const {
        return this->compareTo(calculator) <= 0;
    }

};

#endif //ALGORITHM_COMPARABLE_H
