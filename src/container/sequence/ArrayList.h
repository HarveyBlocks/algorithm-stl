/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/24
 *
 */
#ifndef ALGORITHM_ARRAYLIST_H
#define ALGORITHM_ARRAYLIST_H

#include "SequentialAccessibleContainer.h"
#include "../../lang/Array.h"
#include "../../lang/exception/OverflowException.h"

template<class T>
class ArrayList : public SequentialAccessibleContainer<T> {
private:
    Array<T> *array;
    int capacity;
    int size;
    static const int CAPACITY_MAX = (INT_MAX >> 1) + (INT_MAX >> 2);
    static const int DEFAULT_INIT_CAPACITY = 10;

    bool grow0(int newCapacity);

    /**
     * 在添加数据之前做
     * @param addNum
     * @return 应该扩容但扩容失败的情况
     */
    bool grow(int addNum);

    void shrink0(int newCapacity);

    /**
     * 在删除数据之后做
     * @return
     */
    void shrink();

public:
    explicit ArrayList(int allocate = DEFAULT_INIT_CAPACITY);

    Array<T> getArray() const;

    [[nodiscard]] int getSize() const override;

    [[nodiscard]] int getCapacity() const;

    [[nodiscard]] bool empty() const override;

    T &operator[](int index) const override;

    T *operator+(int offset) const override;

    ArrayList<T> &update(int index, const T &element);

    ArrayList<T> &insert(int index, const T &element);

    ArrayList<T> &add(const T &element);

    ArrayList<T> &concat(const ArrayList<T> &list);

    ArrayList<T> &concat(const Array<T> &array);

    ArrayList<T> &removeLast();

    ArrayList<T> &remove(int index);

    ArrayList<T> &removeElement(const T &element);

    void clear();

    void shrinkArray();

    virtual ~ArrayList();

    friend std::ostream &operator<<(std::ostream &os, const ArrayList<T> &obj) {
        os << obj.size << sizeof(T);
        for (int i = 0; i < obj.size; ++i) {
            os << obj[i];
        }
        return os;
    }

    std::ostream &print(std::ostream &os) {
        os << "[";
        for (int i = 0; i < this->size - 1; ++i) {
            this->operator[](i).print(os) << ", ";
        }
        if (this->size > 0) {
            this->operator[](this->size - 1).print(os);
        }
        return os << "]";
    }
};

#include "impl/ArrayList_impl.h"

#endif //ALGORITHM_ARRAYLIST_H
