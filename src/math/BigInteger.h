/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/8/29
 *
 */
#ifndef ALGORITHM_BIGINTEGER_H
#define ALGORITHM_BIGINTEGER_H


#include "Data.h"
#include "../lang/exception/IllegalStateException.h"
#include "../lang/StringBuilder.h"
#include "../lang/exception/DivideZeroException.h"


#define BIG_INTEGER_ONE BigInteger(1)
#define BIG_INTEGER_ZERO BigInteger(0)
#define BIG_INTEGER_FULL BigInteger(-1)

/**
 * 带有符号位, 采用补码的方式表示符号<br>
 *
 * 缺点与问题, 为了提高代码的复用性, 大多数的操作的逻辑都是创建新的BigInteger表示结果<br>
 * 有时候, 例如在[++,--,+=,-=,*=,/=]的情况下, <br>
 * 由于不是对本身进行直接的操作, 而是完成操作后创建新的BigInteger然后将新的结果赋值(拷贝)给自身<br>
 * 这样会造成多次拷贝而造成效率降低<br>
 */
class BigInteger : public Comparable<const BigInteger &> {
    Data data;
public:
    explicit BigInteger(const Data &data);


    /**
     * @param value 正负无所谓,主要看二进制编码; 如果最高位是1, 就算minus
     */
    explicit BigInteger(math::number value);


    /**
     * 十进制字符串
     */
    static BigInteger phaseDecString(const String &src, int radix = 10);


    [[nodiscard]] int byteCount() const;

    [[nodiscard]] int bitCount() const;

    [[nodiscard]] bool isZero() const;

    [[nodiscard]] bool isMinus() const;

    [[nodiscard]] int isPositive() const;

    BigInteger &autoDataCast(const BigInteger &other);

    /**
     * 带符号的扩大data的size
     * @param targetByteCount
     * @return
     */
    BigInteger &grow(int targetByteCount);

    /**
     * 带符号的扩大data的size
     * @return
     */
    [[nodiscard]] Data dataAfterGrow(int targetByteCount) const;

    /**
     * 自身取补码
     */
    BigInteger &convert2Complement();


    /**
     * 创建自身对应补码, 是不考虑进位的, 即使在加一的时候进位了, 也是会忽略的
     */
    [[nodiscard]] BigInteger takeComplement() const;

    BigInteger &shrink();

    [[nodiscard]] BigInteger newShrink() const;

private:
    BigInteger &set(const Data &newData);

    void initData(math::number value, int size);

    static char number2Character(math::number value);

    static math::number character2Number(char character);

    /**
     * 去除前导0
     * @return 发生变化了就返回true
     */
    BigInteger &shrink(bool isMinus);

    /**
     * 去除前导0
     * @return 发生变化了就返回true
     */
    BigInteger &shrink(const packaging::Bit &shrinkTarget);


    [[nodiscard]] BigInteger newShrink(bool isMinus) const;

    [[nodiscard]] BigInteger newShrink(const packaging::Bit &shrinkTarget) const;

    /**
      * @return new出来的array, 去除了不必要的前导字节; 如果返回null表示可以直接使用当前的array
      */
    [[nodiscard]] Data newShrinkData(const packaging::Bit &shrinkTarget) const;

    /**
     * 就算有进位也会忽略
     * @param casted1 同长度的有符号int
     * @param casted2 同长度的有符号int
     * @return 新的值
     */
    static BigInteger add0(const BigInteger &casted1, const BigInteger &casted2);

    static BigInteger divide0(BigInteger &absDividend, BigInteger &absDivisor,
                              BigInteger &absRemainder);

public:
    /**
     * 会转换长度, 较短的变成较长的那个的长度(类似类型转换)
     * @param signedInteger1 绝对值(不考虑符号, 如果是负数, 需要在传入之前做好补码)
     * @param signedInteger2 绝对值(不考虑符号, 如果是负数, 需要在传入之前做好补码)
     * @return 新的值
     */
    static BigInteger sub(const BigInteger &signedInteger1, const BigInteger &signedInteger2);

    /**
     * 会转换长度, 较短的变成较长的那个的长度(类似类型转换)
     * @param signedInteger1 绝对值(不考虑符号, 如果是负数, 需要在传入之前做好补码)
     * @param signedInteger2 绝对值(不考虑符号, 如果是负数, 需要在传入之前做好补码)
     * @return 新的值
     */
    static BigInteger add(const BigInteger &signedInteger1, const BigInteger &signedInteger2);

    static BigInteger multiply(const BigInteger &signedInteger1, const BigInteger &signedInteger2);

    static BigInteger abs(const BigInteger &integer);

    /**
     *
     * @param dividend 被除数
     * @param divisor 除数
     * @param remainder 余数
     * @return 商
     */
    static BigInteger divide(const BigInteger &dividend, const BigInteger &divisor,
                             BigInteger &remainder);

    BigInteger &operator=(const BigInteger &other);

    // 算数运算
    BigInteger &operator+=(const BigInteger &other);

    BigInteger &operator-=(const BigInteger &other);

    BigInteger &operator++();

    BigInteger &operator--();

    BigInteger &operator*=(const BigInteger &other);

    BigInteger &operator/=(const BigInteger &other);

    BigInteger &operator%=(const BigInteger &other);

    BigInteger operator-() const;

    BigInteger operator+(const BigInteger &other) const;

    BigInteger operator-(const BigInteger &other) const;

    BigInteger operator*(const BigInteger &other) const;

    BigInteger operator/(const BigInteger &other) const;

    BigInteger operator%(const BigInteger &other) const;

    // Data有关位操作
    BigInteger operator&(const BigInteger &other) const;

    BigInteger operator|(const BigInteger &other) const;

    BigInteger operator^(const BigInteger &other) const;

    BigInteger &operator&=(const BigInteger &other);

    BigInteger &operator|=(const BigInteger &other);

    BigInteger &operator^=(const BigInteger &other);

    BigInteger operator~() const;

    // 比较运算
    static int compare(const BigInteger &self, const BigInteger &other);

    [[nodiscard]] int compareTo(const BigInteger &o) const override;


    bool operator==(const BigInteger &o) const;

    bool operator!=(const BigInteger &o) const;

    bool operator>=(const BigInteger &o) const;

    bool operator<=(const BigInteger &o) const;

    bool operator>(const BigInteger &o) const;

    bool operator<(const BigInteger &o) const;

    // 参数类型是number的情况

    BigInteger &operator=(const math::number &other);

    BigInteger &operator+=(const math::number &other);

    BigInteger &operator-=(const math::number &other);

    BigInteger &operator*=(const math::number &other);

    BigInteger &operator/=(const math::number &other);

    BigInteger &operator%=(const math::number &other);

    BigInteger operator+(const math::number &other) const;

    BigInteger operator-(const math::number &other) const;

    BigInteger operator*(const math::number &other) const;

    BigInteger operator/(const math::number &other) const;

    BigInteger operator%(const math::number &other) const;

    BigInteger operator&(const math::number &other) const;

    BigInteger operator|(const math::number &other) const;

    BigInteger operator^(const math::number &other) const;

    BigInteger &operator&=(const math::number &other);

    BigInteger &operator|=(const math::number &other);

    BigInteger &operator^=(const math::number &other);

    bool operator==(const math::number &o) const;

    bool operator!=(const math::number &o) const;

    bool operator>=(const math::number &o) const;

    bool operator<=(const math::number &o) const;

    bool operator>(const math::number &o) const;

    bool operator<(const math::number &o) const;

    // 位移
    /**
     * @return 始终满足除2^offset, 向下取, 符号不变, 正数到0为止, 负数到-1为止
     */
    BigInteger operator<<(int offset) const;

    /**
     * @return 始终满足乘2^offset, 符号不变
     */
    BigInteger operator>>(int offset) const;

    BigInteger &operator<<=(int offset);

    BigInteger &operator>>=(int offset);


    explicit operator math::number() const;

    explicit operator std::string() const;

    [[nodiscard]] String toString(int radix = 10, char separator = 0) const;

    void printMessage(const std::string &varName) const;

    friend std::ostream &operator<<(std::ostream &os, const BigInteger &obj) {
        return os << (std::string) obj.data;
    }


};


#endif //ALGORITHM_BIGINTEGER_H
