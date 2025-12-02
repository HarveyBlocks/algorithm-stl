
#include "container/sequence/SingleLinkedList.h"
#include "container/associative/HashTable.h"


void test1(int a1, int a2) {
    std::cout << "a1=" << a1 << ",a2=" << a2 << std::endl; // 110
    std::cout << "a1+++a2 => " << (a1++ + a2) << std::endl; // 110
    std::cout << "a1=" << a1 << ",a2=" << a2 << std::endl; // 110
}

void test2(int a1, int a2) {
    std::cout << "a1=" << a1 << ",a2=" << a2 << std::endl; // 110
    std::cout << "a1+ ++a2 => " << (a1 + ++a2) << std::endl; // 110
    std::cout << "a1=" << a1 << ",a2=" << a2 << std::endl; // 110
}

void test3(int a1, int a2) {
    std::cout << "a1=" << a1 << ",a2=" << a2 << std::endl; // 110
    std::cout << "a1++ +a2 => " << (a1++ + a2) << std::endl; // 110
    std::cout << "a1=" << a1 << ",a2=" << a2 << std::endl; // 110
}

void test4(int a1, int a2) {
    std::cout << "a1=" << a1 << ",a2=" << a2 << std::endl; // 110
    std::cout << "a1+ + +a2 => " << (a1 + + +a2) << std::endl; // 110
    std::cout << "a1=" << a1 << ",a2=" << a2 << std::endl; // 110
}


int main() {
    int x = 2, y = 3;
    const int *p1 = &x; // 指向的内容是常量, 指针本身不是常量
    int *const p2 = &x; // 指针本身是常量, 指针指向的对象不是常量
    return 0;
}