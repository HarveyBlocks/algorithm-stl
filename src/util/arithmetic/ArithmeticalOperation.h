/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/7/28
 *
 */
#ifndef ALGORITHM_ARITHMETICAL_OPERATION_H
#define ALGORITHM_ARITHMETICAL_OPERATION_H

#include "string"
#include "cfloat"

/**
 * 算数操作
 */
class ArithmeticalOperation {
private:
    ArithmeticalOperation() = default;

public:
    static double minus(double a, double b);

    static double minusMinus(double a, double b);

    static double plus(double a, double b);

    static double divide(double a, double b);

    static double minusDivide(double a, double b);

    static double multiply(double a, double b);

    constexpr static double (*CALCULATE_FUNCTION_ARRAY[6])(double, double) = {
            ArithmeticalOperation::minus,
            ArithmeticalOperation::plus,
            ArithmeticalOperation::divide,
            ArithmeticalOperation::multiply,
            ArithmeticalOperation::minusMinus,
            ArithmeticalOperation::minusDivide
    };

    static char map2Char(int index);

    static std::string map2Expr(int a, int b, char operatorCharacter);

    static std::string map2Expr(const std::string &a, int b, char operatorCharacter);

    static std::string map2Expr(int a, const std::string &b, char operatorCharacter) {
        return map2Expr(std::to_string(a), b, operatorCharacter);
    }

    static std::string map2Expr(const std::string &a, const std::string &b, char operatorCharacter);
};

inline double ArithmeticalOperation::minus(double a, double b) {
    return a - b;
}

inline double ArithmeticalOperation::minusMinus(double a, double b) {
    return b - a;
}

inline double ArithmeticalOperation::plus(double a, double b) {
    return a + b;
}

inline double ArithmeticalOperation::divide(double a, double b) {
    if (b == 0) {
        return DBL_MAX;
    }
    return a / b;
}

inline double ArithmeticalOperation::minusDivide(double a, double b) {
    if (a == 0) {
        return DBL_MAX;
    }
    return b / a;
}

inline double ArithmeticalOperation::multiply(double a, double b) {
    return a * b;
}


inline char ArithmeticalOperation::map2Char(int index) {
    double (*pFunction)(double, double) = CALCULATE_FUNCTION_ARRAY[index];
    if (pFunction == minus) {
        return '-';
    }
    if (pFunction == plus) {
        return '+';
    }
    if (pFunction == multiply) {
        return '*';
    }
    if (pFunction == divide) {
        return '/';
    }
    if (pFunction == minusDivide) {
        return '\\';
    }
    if (pFunction == minusMinus) {
        return '|';
    }
    throw IllegalArgumentException("Unknown");
}


inline std::string ArithmeticalOperation::map2Expr(int a, int b, char operatorCharacter) {
    return map2Expr(std::to_string(a),std:: to_string(b), operatorCharacter);
}

inline std::string ArithmeticalOperation::map2Expr(const std::string &a, int b, char operatorCharacter) {
    return map2Expr(a, std::to_string(b), operatorCharacter);
}

inline std::string ArithmeticalOperation::map2Expr(const std::string &a, const std::string &b, char operatorCharacter) {
    if (operatorCharacter == '|') {
        return "(" + (b) + "-" + (a) + ")";
    }
    if (operatorCharacter == '\\') {
        return "(" + (b) + "/" + (a) + ")";
    }
    return "(" + (a) + operatorCharacter + (b) + ")";
}


#endif //ALGORITHM_ARITHMETICAL_OPERATION_H
