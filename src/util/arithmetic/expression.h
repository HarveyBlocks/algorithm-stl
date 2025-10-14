/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/7/28
 *
 */
#ifndef ALGORITHM_EXPRESSION_H
#define ALGORITHM_EXPRESSION_H

#include "../../lang/exception/OutOfMemoryException.h"
#include "../../lang/exception/NullPointException.h"
#include "../../lang/exception/IllegalStateException.h"
#include "../../util/function/function.h"
#include "Number.h"

class NumberExpression;

/**
 * 算数表达式
 */
class ArithmeticExpression {
public:
    /**
     *
     * @param pResult 用于接收结果, 将对pResult指向的内存空间赋值, 赋值的内容是返回值
     */
    [[nodiscard]] virtual NumberExpression *execute(NumberExpression *pResult) const {
        throw IllegalStateException("Can't use this function directly");
    }

    [[nodiscard]] virtual std::string toString() const {
        return "()";
    }

    friend std::ostream &operator<<(std::ostream &os, const ArithmeticExpression &obj) {
        return os << obj.toString();
    }
};

/**
 * 端点
 */
class NumberExpression : public ArithmeticExpression {
private:
    Number num;

public:
    explicit NumberExpression(const Number &num = DEFAULT_NUMBER) : num(num) {}


    NumberExpression *execute(NumberExpression *pResult) const override {
        if (pResult == nullptr) {
            throw NullPointException();
        }
        *pResult = *this;
        return pResult;
    }

    [[nodiscard]] std::string toString() const override {
        return num.toString();
    }

    [[nodiscard]] Number value() const {
        return num;
    }
};
/**
 * 双目运算
 */
class BinocularOperation : public ArithmeticExpression {
private:
    const ArithmeticExpression *pre;
    const ArithmeticExpression *post;
protected:
    [[nodiscard]] std::string toString(char operatorCharacter) const {
        return "(" + pre->toString() + operatorCharacter + post->toString() + ")";
    }

    NumberExpression *execute(NumberExpression *pResult, BiFunction<Number, Number, Number> calculate) const {
        if (pResult == nullptr) {
            throw NullPointException();
        }
        NumberExpression preResult;
        NumberExpression postResult;
        Number preValue = pre->execute(&preResult)->value();
        Number postValue = post->execute(&postResult)->value();
        *pResult = NumberExpression(calculate(preValue, postValue));
        return pResult;
    }

public:
    BinocularOperation(const ArithmeticExpression *pre, const ArithmeticExpression *post) :
            pre(pre), post(post) {}
};


/**
 * 减法
 */
class Subtraction : public BinocularOperation {
public:
    Subtraction(const ArithmeticExpression *pre, const ArithmeticExpression *post) :
            BinocularOperation(pre, post) {}

    [[nodiscard]] std::string toString() const override {
        return this->BinocularOperation::toString('-');
    }

    NumberExpression *execute(NumberExpression *pResult) const override {
        return this->BinocularOperation::execute(
                pResult,
                [](Number pre, Number post) {
                    return Number(pre.get() - post.get());
                });
    }
};


/**
 * 加法
 */
class Addition : public BinocularOperation {
public:
    Addition(const ArithmeticExpression *pre, const ArithmeticExpression *post) :
            BinocularOperation(pre, post) {}

    [[nodiscard]] std::string toString() const override {
        return this->BinocularOperation::toString('+');
    }

    NumberExpression *execute(NumberExpression *pResult) const override {
        return this->BinocularOperation::execute(
                pResult,
                [](Number pre, Number post) {
                    return Number(pre.get() + post.get());
                });
    }
};

/**
 * 乘法
 */
class Multiplication : public BinocularOperation {
public:
    Multiplication(const ArithmeticExpression *pre, const ArithmeticExpression *post) :
            BinocularOperation(pre, post) {}

    [[nodiscard]] std::string toString() const override {
        return this->BinocularOperation::toString('*');
    }

    NumberExpression *execute(NumberExpression *pResult) const override {
        return this->BinocularOperation::execute(
                pResult,
                [](Number pre, Number post) {
                    return Number(pre.get() * post.get());
                });
    }
};

/**
 * 除法
 */
class Division : public BinocularOperation {
public:
    Division(const ArithmeticExpression *pre, const ArithmeticExpression *post) :
            BinocularOperation(pre, post) {}

    [[nodiscard]] std::string toString() const override {
        return this->BinocularOperation::toString('/');
    }

    NumberExpression *execute(NumberExpression *pResult) const override {
        return this->BinocularOperation::execute(
                pResult,
                [](Number pre, Number post) {
                    return Number(pre.get() / post.get());
                });
    }
};


/**
 * 取余
 */
class Mod : public BinocularOperation {
public:
    Mod(const ArithmeticExpression *pre, const ArithmeticExpression *post) :
            BinocularOperation(pre, post) {}

    [[nodiscard]] std::string toString() const override {
        return this->BinocularOperation::toString('%');
    }

    NumberExpression *execute(NumberExpression *pResult) const override {
        return this->BinocularOperation::execute(
                pResult,
                [](Number pre, Number post) {
                    return Number(pre.get() % post.get());
                });
    }
};

/**
 * 取负
 */
class Minus : public ArithmeticExpression {
private:
    const ArithmeticExpression *expression;
public:
    explicit Minus(const ArithmeticExpression *expression) : expression(expression) {}

    NumberExpression *execute(NumberExpression *pResult) const override {
        if (pResult == nullptr) {
            throw NullPointException();
        }
        NumberExpression expressionResult;
        const Number &number = expression->execute(&expressionResult)->value();
        int resultValue = -number.get();
        *pResult = NumberExpression(Number(resultValue));
        return pResult;
    }

    [[nodiscard]] std::string toString() const override {
        return "-" + expression->toString();
    }
};

NumberExpression operator-(const ArithmeticExpression &pre, const ArithmeticExpression &post) {
    NumberExpression result;
    return *(Subtraction(&pre, &post).execute(&result));
}

NumberExpression operator+(const ArithmeticExpression &pre, const ArithmeticExpression &post) {
    NumberExpression result;
    return *(Addition(&pre, &post).execute(&result));
}


NumberExpression operator*(const ArithmeticExpression &pre, const ArithmeticExpression &post) {
    NumberExpression result;
    return *(Multiplication(&pre, &post).execute(&result));
}


NumberExpression operator/(const ArithmeticExpression &pre, const ArithmeticExpression &post) {
    NumberExpression result;
    return *(Division(&pre, &post).execute(&result));
}

NumberExpression operator-(const ArithmeticExpression &expression) {
    NumberExpression result;
    return *(Minus(&expression).execute(&result));
}

#endif //ALGORITHM_EXPRESSION_H
