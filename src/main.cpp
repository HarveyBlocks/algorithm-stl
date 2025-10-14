
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
    std::string str;
    std::cin >> str;
    std::cout << "Hello World: " << str << std::endl;
    /*std::cout << "=====================" << std::endl;
    test1(10, 100);
    std::cout << "=====================" << std::endl;
    test2(10, 100);
    std::cout << "=====================" << std::endl;
    test3(10, 100);
    std::cout << "=====================" << std::endl;
    test4(10, 100);*/
    return 0;
}