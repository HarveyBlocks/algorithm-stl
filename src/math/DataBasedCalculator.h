/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/9/1
 *
 */
#ifndef ALGORITHM_DATA_BASED_CALCULATOR_H
#define ALGORITHM_DATA_BASED_CALCULATOR_H


#include "AbstractCalculator.h"
#include "Data.h"

template<typename T>
class DataBasedCalculator : public AbstractCalculator<T> {
protected:
    Data data;

    /**
     * 舒张Data
     */
    virtual T &shrink() {
        this->data = newShrinkData();
        return this->getThis();
    }

    /**
     * 舒张Data
     */
    [[nodiscard]] T newShrink() const {
        return T(newShrinkData());
    }

    [[nodiscard]] virtual Data newShrinkData() const = 0;

    /**
     * 舒张Data, 补全高位
     */
    virtual T &grow(int targetCount) {
        this->data = newGrowData(targetCount);
        return this->getThis();
    }

    /**
     * 舒张Data, 补全高位
     */
    [[nodiscard]] T newGrow(int targetCount) const {
        return T(newGrowData());
    }

    [[nodiscard]] virtual Data newGrowData(int targetCount) const = 0;

    /**
     * 先shrink, 再高位对齐
     */
    static int autoCast(T &num1Copy, T &num2Copy) {
        num1Copy.shrink();
        num2Copy.shrink();
        int maxCount = std::max(num1Copy.byteCount(), num2Copy.byteCount());
        num1Copy.grow(maxCount);
        num2Copy.grow(maxCount);
        return maxCount;
    }

public:
    /**
     * @param number 只分配空间
     */
    explicit DataBasedCalculator(const math::number &number = 0);

    explicit DataBasedCalculator(const Data &data);

    DataBasedCalculator(const DataBasedCalculator &obj);

    explicit operator std::string() const;

    [[nodiscard]] int byteCount() const;

    virtual void initData(const math::number &number) = 0;

    void printMessage(const std::string &varName) const {
        std::cout << varName << " value: " << this->operator math::number() << std::endl;
        std::cout << varName << " binary: " << this->operator std::string() << std::endl;
    }

};

template<typename T>
int DataBasedCalculator<T>::byteCount() const {
    return this->data.byteCount();
}

template<typename T>
DataBasedCalculator<T>::operator std::string() const {
    return (std::string) this->data;
}


template<typename T>
DataBasedCalculator<T>::DataBasedCalculator(const math::number &number) :
        AbstractCalculator<T>(number), data(sizeof(math::number)) {}

template<typename T>
DataBasedCalculator<T>::DataBasedCalculator(const DataBasedCalculator &obj) : data(obj.data) {}

template<typename T>
DataBasedCalculator<T>::DataBasedCalculator(const Data &data) : data(data) {}


#endif //ALGORITHM_DATA_BASED_CALCULATOR_H
