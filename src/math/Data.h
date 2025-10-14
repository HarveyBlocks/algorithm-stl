/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/8/29
 *
 */
#ifndef ALGORITHM_DATA_H
#define ALGORITHM_DATA_H

#include "../lang/Array.h"
#include "../lang/packaging/Byte.h"
#include "../util/function/function.h"
#include "../lang/Comparable.h"

#define DATA_ZERO Data(1)
#define DATA_NULL Data(0)


class Data : public Comparable<const Data &> {
private:
    Array<Byte> *byteArray;
private:
    void updateData(Array<Byte> *newData);

public:

    explicit Data(int size);

    explicit Data(int size, const Byte &initValue);

    /**
     * 深拷贝
     */
    Data(const Data &obj);

    /**
     * 深拷贝
     */
    Data &clone(Data &target) const;

    /**
     * <pre>
     * for (int i = start, j = targetStart;<br>
     *          i &lt; end && j &lt; targetEnd;<br>
     *          ++i, ++j) {<br>
     *         target.setByte(j, this->getByte(i))<br>;
     * }</pre>
     */
    Data &byteCopy(int start, int end, Data &target, int targetStart, int targetEnd) const;

    static Data &byteCopy(const Data &source, int start, int end,
                          Data &target, int targetStart, int targetEnd);

    Data &bitCopy(int start, int end, Data &target, int targetStart, int targetEnd) const;

    ~Data();


    [[nodiscard]] int bitCount() const;

    [[nodiscard]] int byteCount() const;

    /**
     * @param index 0表示最高一个字节, -1表示最后一个字节, -2表示倒数第二个字节
     */
    [[nodiscard]] Byte &getByte(int index) const;

    /**
     * @param index 0 表示最高一个字节, -1表示最后一个字节, -2表示倒数第二个字节
     */
    Data &setByte(int index, const Byte &value);

    /**
     * @param start 包含, 可以为负数
     * @param end 不包含, 从start累加1到end
     * @param value 全部设成value
     */
    Data &setByte(int start, int end, const Byte &value);

    /**
     * value全部置为0
     *
     * @param start 包含, 可以为负数
     * @param end 不包含, 从start累加1到end
     */
    Data &setBit0(int start, int end);

    /**
     * value全部置为1
     *
     * @param start 包含, 可以为负数
     * @param end 不包含, 从start累加1到end
     */
    Data &setBit1(int start, int end);

    /**
     * @param start 包含, 可以为负数
     * @param end 不包含, 从start累加1到end
     * @param value value全部置为指定值
     */
    Data &setBit(int start, int end, const packaging::Bit &value);

    Data &setBit0(int index);

    Data &setBit1(int index);

    Data &setBit(int index, packaging::Bit value);


    /**
     * @param index 0 表示最高一位, -1表示最后一位, -2表示倒数第二位
     */
    [[nodiscard]] packaging::Bit getBit(int index) const;


private:
    static int fixIndex(int size, int index);


public:
    static Data createLargerData(const Data &data1, const Data &data2);

    static Data createLargerData(int data1Size, int data2Size);

    /**
     * 深拷贝
     */
    [[nodiscard]] Data grow(int targetByteCount) const;

    /**
     * @param offset 左移1格, 长度缩短1
     * @return
     */
    [[nodiscard]] Data leftMoveByteGrow(int offset) const { // NOLINT(*-no-recursion)
        if (offset == 0) {
            return *this;
        }
        if (offset < 0) {
            return this->rightMoveByteShrink(-offset);
        }
        Data result(this->byteCount() + offset);
        this->byteCopy(0, this->byteCount(), result, 0, result.byteCount());
        return result;
    }

    /**
     *
     * @param offset 右移1格, 长度缩短一个
     * @return
     */
    [[nodiscard]] Data rightMoveByteShrink(int offset) const { // NOLINT(*-no-recursion)
        if (offset == 0) {
            return *this;
        }
        if (offset < 0) {
            return this->leftMoveByteGrow(-offset);
        }
        Data result(this->byteCount() - offset);
        this->byteCopy(0, this->byteCount(), result, 0, result.byteCount());
        return result;
    }


    /**
     * @param targetFillBit 将会充填targetByte, 组成0xff或0x00
     * @return 如果都是targetFillBit就返回count,
     * 否则返回不是targetFillBit的第一个的索引, 不会大于等于count
     */
    [[nodiscard]] int firstTargetNotByte(const packaging::Bit &targetFillBit) const;

    /**
     * @return 如果都是0就返回-1, 否则返回不是0的第一个的索引
     */
    [[nodiscard]] int firstBit(const packaging::Bit &targetBit) const;

    /**
     * 写入本类
     * @param matcher 返回true时指向insert
     */
    Data &insertIf(const Function<const Byte &, bool> &matcher, int index, const Byte &value) {
        if (matcher(this->getByte(index))) {
            return this->operator=(this->insert(index, value));
        }
        return *this;
    }

    /**
     * 多次拷贝, 非必要不要用
     * 创建一个新的Data, 然后加入元素, 然后返回
     */
    [[nodiscard]] Data insert(int index, const Byte &value) const;

    [[nodiscard]] bool isZero() const;


    std::ostream &print(std::ostream &os) const;


private:
    /**
     * 位运算
     * @param eachByteFunc 参数是从data的低位开始的, 先传送最低的一个字节
     * @return 会进行缩减(去除前置占据满字节0)
     */
    [[nodiscard]] Data
    bitOperator(const Data &other, const BiFunction<const Byte &, const Byte &, Byte> &eachByteFunc) const;

public:
    Data &operator=(const Data &other);

    Data operator&(const Data &other) const;

    Data operator|(const Data &other) const;

    Data operator^(const Data &other) const;

    Data &operator&=(const Data &other);

    Data &operator|=(const Data &other);

    Data &operator^=(const Data &other);

    Data operator~() const;

    static int compare(const Data &self, const Data &other);

    [[nodiscard]] int compareTo(const Data &o) const override;

    bool operator==(const Data &o) const;

    bool operator!=(const Data &o) const;

    bool operator>=(const Data &o) const;

    bool operator<=(const Data &o) const;

    bool operator>(const Data &o) const;

    bool operator<(const Data &o) const;

    Data operator<<(int offset) const;

    /**
     * 都是无符号位移
     */
    Data operator>>(int offset) const;

    Data &leftMoveByte(int offset, const Byte &fill = BYTE_ZERO);

    Data &rightMoveByte(int offset, const Byte &fill = BYTE_ZERO);

    /**
     * 都是无符号位移
     */
    Data &operator<<=(int offset);

    Data &operator>>=(int offset);

    friend std::ostream &operator<<(std::ostream &os, const Data &obj);

    explicit operator std::string() const;

    explicit operator math::number() const;

    void printMessage(const std::string &varName) const {
        std::cout << varName << " [value] : " << this->operator math::number() << std::endl;
        std::cout << varName << " [binary]: " << this->operator std::string() << std::endl;
    }

    /**
     * @param start 包含,可正可负
     * @param end 不包含,可正可负
     * @param step 可正可负
     * @return
     */
    [[nodiscard]] Data subDataBytes(int start, int end, int step = 1) const;
};


#endif //ALGORITHM_DATA_H
