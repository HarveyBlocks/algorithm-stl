/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/25
 *
 */
#ifndef ALGORITHM_HASHTABLE_H
#define ALGORITHM_HASHTABLE_H

#include "AssociativeContainer.h"
#include "../../lang/Array.h"
#include "../sequence/SingleLinkedList.h"

template<class K, class V>
class HashTable : public AssociativeContainer<K, V> {
    Array<SingleLinkedList<Entry<K, V>>> *table;
    mutable int size;
private:
    static int map2Index(const HashCode &code, int tableSize) {
        return (int) (code % tableSize);
    }

public:
    explicit HashTable(int width = 10) : size(0), table(new Array<SingleLinkedList<Entry<K, V>>>(width)) {
    }

    virtual ~HashTable() {
        delete table;
    }

    int getSize() const override {
        return size;
    }

    bool empty() const override {
        return size == 0;
    }

    bool containsKey(const K &key) {
        int indexInTable = map2Index((HashCode) key, table->getSize());
        bool find = false;
        (*table)[indexInTable].forEach([&key, &find](Entry<K, V> &entry) {
            if (!entry.keyIsNull() && Entry<K, V>::equals(entry.getKey(), key)) {
                find = true;
            }
            return !find;
        });
        return find;
    }

    V &operator[](const K &key) const override {
        int indexInTable = map2Index((HashCode) key, table->getSize());
        Entry<K, V> *target;
        bool find = false;
        (*table)[indexInTable].forEach([&key, &target, &find](Entry<K, V> &entry) {
            if (!entry.keyIsNull() && Entry<K, V>::equals(entry.getKey(), key)) {
                target = &entry;
                find = true;
            }
            return !find;
        });

        if (find) {
            if (target->valueIsNull()) {
                target->resetValue();
            }
            return target->getValue();
        } else {
            // pushFront? How To?
            // 增加一个节点
            (*table)[indexInTable].pushFront(Entry<K, V>(key));
            size++;
            Entry<K, V> &newEntry = (*table)[indexInTable].front();
            if (newEntry.valueIsNull()) {
                newEntry.resetValue();
            }
            return newEntry.getValue();
        }
    }

    void put(const K &k, const V &v) {
        this->operator[](k) = v;
    }

    V get(const K &k) {
        return this->operator[](k);
    }

    void forEach(const BiFunction<K &, V &, bool> &task) const override {
        this->forEach([&task](Entry<K, V> &entry) {
            if (entry.keyIsNull() || entry.valueIsNull()) {
                return true;
            }
            return task(entry.getKey(), entry.getValue());
        });
    }

    void forEach(const Function<Entry<K, V> &, bool> &task) const {
        int tableSize = table->getSize();
        for (int i = 0; i < tableSize; ++i) {
            SingleLinkedList<Entry<K, V>> list = (*table)[i];
            list.forEach(task);
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const HashTable<K, V> &hashTable) {
        os << "{";
        int count = hashTable.getSize();
        Entry<K, V> *last = nullptr;
        hashTable.forEach([&os, &count, &last](Entry<K, V> &entry) mutable {
            if (--count == 0) {
                last = new Entry(entry);
            } else {
                os << entry << ", ";
            }
            return last == nullptr;
        });
        if (last != nullptr) {
            os << *last;
            delete last;
        }
        return os << "}";
    }

};


#endif //ALGORITHM_HASHTABLE_H
