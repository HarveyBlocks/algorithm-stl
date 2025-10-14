/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/25
 *
 */
#include <fstream>
#include "lang/StringBuilder.h"
#include "iostream"
#include "util/ColorfulString.h"

using namespace std;

int colorDemo() {
    String str("aaa");
    cout << ColorfulString::painting(str);
    return 0;
}

int stringOutDemo() {
    cout << String("012345678901234567890123456789") << endl;
    cout << String("01234567890123456789012345678") << endl;
    cout << String("0123456789012345678901234567") << endl;
    cout << String("012345678901234567890123456") << endl;
    cout << String("01234567890123456789012345") << endl;
    cout << String("0123456789012345678901234") << endl;
    cout << String("012345678901234567890123") << endl;
    cout << String("01234567890123456789012") << endl;
    cout << String("0123456789012345678901") << endl;
    cout << String("012345678901234567890") << endl;
    cout << String("01234567890123456789") << endl;
    cout << String("0123456789012345678") << endl;
    cout << String("012345678901234567") << endl;
    cout << String("01234567890123456") << endl;
    cout << String("0123456789012345") << endl;
    cout << String("012345678901234") << endl;
    cout << String("01234567890123") << endl;
    cout << String("0123456789012") << endl;
    cout << String("012345678901") << endl;
    cout << String("01234567890") << endl;
    cout << String("0123456789") << endl;
    cout << String("012345678") << endl;
    cout << String("01234567") << endl;
    cout << String("0123456") << endl;
    cout << String("012345") << endl;
    cout << String("01234") << endl;
    cout << String("0123") << endl;
    cout << String("012") << endl;
    cout << String("01") << endl;
    cout << String("0") << endl;
    cout << String("") << endl;
    cout << String() << endl;
    return 0;
}

int numStringDemo() {
    String s;
    cout << "----------------------" << endl;
    cout << String::valueOf(123);
    cout << "----------------------" << endl;
    return 0;
}

int stringCompareDemo() {
    cout << (String("12") == String::valueOf(123)) << endl;
    cout << (String("12") != String::valueOf(123)) << endl;
    cout << (String("12") < String::valueOf(123)) << endl;
    cout << (String("12") > String::valueOf(123)) << endl;
    cout << (String("12") <= String::valueOf(123)) << endl;
    cout << (String("12") >= String::valueOf(123)) << endl;
    cout << (String("123") == String::valueOf(123)) << endl;
    cout << (String("123") != String::valueOf(123)) << endl;
    cout << (String("123") > String::valueOf(123)) << endl;
    cout << (String("123") < String::valueOf(123)) << endl;
    cout << (String("123") >= String::valueOf(123)) << endl;
    cout << (String("123") <= String::valueOf(123)) << endl;
    cout << (String("das") == String::valueOf(123)) << endl;
    cout << (String("das") > String::valueOf(123)) << endl;
    return 0;
}

// int stringCode = colorDemo();