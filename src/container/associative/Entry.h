/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/25
 *
 */
#ifndef ALGORITHM_ENTRY_H
#define ALGORITHM_ENTRY_H

#include "../Container.h"
#include "../../lang/exception/IllegalStateException.h"
#include "../../lang/HashCode.h"

template<class K, class V>
class Entry {
private:
    K *key;
    V *value;
public:
    Entry(const K &key, const V &value) : key(new K(key)), value(new V(value)) {};

    explicit Entry(const K &key) : key(new K(key)), value(nullptr) {};

    Entry(const Entry &entry) : Entry() {
        if (entry.key != nullptr) {
            this->key = new K(*(entry.key));
        }
        if (entry.value != nullptr) {
            this->value = new V(*(entry.value));
        }
    };

    Entry() : key(nullptr), value(nullptr) {};

    virtual ~Entry() {
        delete key;
        delete value;
    }

    bool keyIsNull() {
        return key == nullptr;
    }

    bool valueIsNull() {
        return value == nullptr;
    }


    K &getKey() const {
        if (key == nullptr) {
            throw NullPointException();
        }
        return *key;
    }

    V &getValue() const {
        if (value == nullptr) {
            throw NullPointException();
        }
        return *value;
    }

    void resetKey() {
        delete this->key;
        Entry::key = new K();
    }

    void resetValue() {
        delete this->value;
        Entry::value = new V();
    }

    [[nodiscard]] HashCode hashCode() const {
        if (key == nullptr) {
            throw NullPointException();
        }
        return (HashCode) (*key);
    }

    static bool equals(const K &key1, const K &key2) {
        bool equal = (key1 == key2);
        if (equal != (key2 == key1)) {
            throw IllegalStateException("Incorrect override of operator: ==");
        }
        return equal;
    }

    friend std::ostream &operator<<(std::ostream &os, const Entry<K, V> &entry) {
        K *k = entry.key;
        if (k == nullptr) {
            os << "null";
        } else {
            os << *(k);
        }
        os << ": ";
        V *v = entry.value;
        if (v == nullptr) {
            os << "null";
        } else {
            os << *(v);
        }
        return os;
    }
};


#endif //ALGORITHM_ENTRY_H
