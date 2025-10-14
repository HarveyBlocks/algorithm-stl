/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/22
 *
 */
#include "container/sequence/Stack.h"
#include "container/sequence/Queue.h"
#include "container/Heap.h"
#include "container/sequence/ArrayList.h"
#include "util/Random.h"
#include "container/sequence/SingleLinkedList.h"
#include "container/sequence/DoublyLinkedList.h"
#include "container/associative/HashTable.h"

int StackDemo();

int QueueDemo();

int ArrayDemo();

int HeapDemo();

int ArrayListDemo();

int BigArrayListDemo();

int SingleLinkedListDemo();

int DoublyLinkedListDemo();

int HashTableDemo();

//int containerExitCode = ArrayDemo();

int HashTableDemo() {
    HashTable<long, int> table;
    Entry<long, int> entry;
    std::cout << entry << std::endl;
    std::cout << table << std::endl;
    table[1] = 2;
    std::cout << table[1] << std::endl;
    std::cout << table << std::endl;
    table[1] = 3;
    std::cout << table[1] << std::endl;
    std::cout << table.getSize() << std::endl;
    std::cout << table << std::endl;
    std::cout << (table.containsKey(12) ? "true" : "false") << std::endl;
    std::cout << (table.containsKey(11) ? "true" : "false") << std::endl;
    std::cout << (table.containsKey(10) ? "true" : "false") << std::endl;
    std::cout << (table.containsKey(9) ? "true" : "false") << std::endl;
    std::cout << (table.containsKey(13) ? "true" : "false") << std::endl;
    std::cout << (table.containsKey(1) ? "true" : "false") << std::endl;
    std::cout << table << std::endl;
    return 0;
}

int DoublyLinkedListDemo() {
    DoublyLinkedList<int> list;
    std::cout << list << std::endl;
    list.pushFront(1);
    std::cout << list << std::endl;
    list.pushFront(2);
    std::cout << list << std::endl;
    list.pushFront(3);
    std::cout << list << std::endl;
    list.pushFront(4);
    std::cout << list << std::endl;
    list.pushBack(10);
    std::cout << list << std::endl;

    list.pushBack(11);
    std::cout << list << std::endl;

    list.pushBack(12);
    std::cout << list << std::endl;

    list.pushBack(13);
    std::cout << list << std::endl;

    list.popFront();
    std::cout << list << std::endl;
    list.popBack();
    std::cout << list << std::endl;
    DoublyLinkedList<int> copy(list);
    std::cout << list << std::endl;
    std::cout << copy << std::endl;


    copy.popFront();
    std::cout << copy << std::endl;
    copy.popBack();
    std::cout << copy << std::endl;
    copy.popFront();
    std::cout << copy << std::endl;
    copy.popFront();
    std::cout << copy << std::endl;
    copy.popFront();
    std::cout << copy << std::endl;


    list.popBack();
    std::cout << list << std::endl;
    list.popFront();
    std::cout << list << std::endl;
    list.popBack();
    std::cout << list << std::endl;
    list.popFront();
    std::cout << list << std::endl;
    list.popFront();
    std::cout << list << std::endl;


    list.pushFront(12);
    std::cout << list << std::endl;
    list.pushFront(2);
    std::cout << list << std::endl;
    list.pushFront(3);
    std::cout << list << std::endl;
    list.pushFront(4);
    std::cout << list << std::endl;
    list.pushBack(10);
    std::cout << list << std::endl;


    list.clear();
    std::cout << list << std::endl;
    list.pushFront(12);
    std::cout << list << std::endl;
    list.pushFront(2);
    std::cout << list << std::endl;
    list.pushFront(3);
    std::cout << list << std::endl;
    list.pushFront(4);
    std::cout << list << std::endl;
    list.pushBack(10);
    std::cout << list << std::endl;
    return 0;
}

int SingleLinkedListDemo() {
    SingleLinkedList<int> list;
    std::cout << list << std::endl;
    list.insert(0, 1);
    std::cout << list << std::endl;
    list.insert(0, 2);
    std::cout << list << std::endl;
    list.insert(0, 3);
    std::cout << list << std::endl;
    list.insert(0, 4);
    std::cout << list << std::endl;
    list.insert(3, 5);
    std::cout << list << std::endl;
    list.insert(5, 6);
    std::cout << list << std::endl;
    list.remove(0);
    std::cout << list << std::endl;
    list.remove(3);
    std::cout << list << std::endl;
    /*list.remove(4);
    std::cout << list << std::endl;
    list.remove(4);
    std::cout << list << std::endl;*/
    list.remove(3);
    std::cout << list << std::endl;
    list.remove(0);
    std::cout << list << std::endl;
    list.remove(0);
    std::cout << list << std::endl;
    list.remove(0);
    std::cout << list << std::endl;
    Random::resetSeed();
    for (int i = 0; i < 20; ++i) {
        list.pushBack(Random::unsignedByte() % 3);
        std::cout << list << std::endl;
    }
    std::cout << list << std::endl;
    list.removeElement(2);
    std::cout << list << std::endl;
    return 0;
}

int BigArrayListDemo() {
    ArrayList<int> list;
    for (int i = 0; i < 2; i++) {
        try {
            list.add(0);
        } catch (const Exception &e) {
            std::cout << e.message() << std::endl;
        }
    }
    for (int i = 0; i < INT_MAX; i++) {
        try {
            list.concat(list);
        } catch (const Exception &e) {
            std::cout << e.message() << std::endl;
            break;
        }
    }
    return 0;
}

int ArrayListDemo() {
    ArrayList<int> list;
    std::cout << list << std::endl;
    list.add(1);
    std::cout << list << std::endl;
    Array<int> temp(100, 0);
    for (int i = 0; i < 20; ++i) {
        int element = Random::unsignedByte() % 16;
        temp[i] = element;
        list.add(element);
    }
    std::cout << temp << std::endl;
    std::cout << list << std::endl;
    list.insert(13, 5);
    std::cout << list << std::endl;
    list.insert(13, 5);
    std::cout << list << std::endl;
    list.insert(13, 5);
    std::cout << list << std::endl;
    list.insert(13, 5);
    std::cout << list << std::endl;
    list.removeLast();
    std::cout << list << std::endl;
    list.remove(1);
    std::cout << list << std::endl;
    list.removeElement(5);
    std::cout << list << std::endl;
    list.clear();
    std::cout << list << std::endl;
    for (int i = 0; i < 50; ++i) {
        list.add(10);
    }
    std::cout << list << std::endl;
    for (int i = 0; i < 20; ++i) {
        list.add(5);
    }
    std::cout << list << std::endl;
    for (int i = 0; i < 50; ++i) {
        list.add(10);
    }
    std::cout << list << std::endl;
    list.removeElement(10);
    std::cout << list << std::endl;
    std::cout << list.getCapacity() << std::endl;
    list.shrinkArray();
    std::cout << list.getCapacity() << std::endl;
    list.update(3, 3);
    std::cout << list << std::endl;
    return 0;
}

int HeapDemo() {
    Array<int> arr(12);
    Compare<int> function1 = Comparators::GREATER<int>();
    Heap<int> heap(arr, function1);
    std::cout << heap << std::endl;
    heap.sort();
    std::cout << heap << std::endl;
    return 0;
}

int QueueDemo() {
    Queue<int> queue;
    /*int top = queue.pop();
    std::cout << top << std::endl;*/
    queue.push(12);
    queue.push(12);
    queue.push(13);
    queue.push(15);
    queue.push(14);
    std::cout << queue.front() << std::endl;
    std::cout << queue.pop() << std::endl;
    std::cout << queue.front() << std::endl;
    std::cout << queue.front() << std::endl;
    std::cout << queue.pop() << std::endl;
    std::cout << queue.pop() << std::endl;
    std::cout << queue.pop() << std::endl;
    Queue<int> q = queue;
    std::cout << q.pop() << std::endl;
    queue.push(15);
    std::cout << queue.pop() << std::endl;
    std::cout << queue.pop() << std::endl;
    try {
        std::cout << q.pop() << std::endl;
    } catch (const Exception &e) {
        std::cout << e.message() << std::endl;
    }
    return 0;
}

int StackDemo() {
    Stack<int> stack;
    /*int top = stack.pop();
    std::cout << top << std::endl;*/
    stack.push(12);
    stack.push(12);
    stack.push(13);
    stack.push(15);
    stack.push(14);
    std::cout << stack.top() << std::endl;
    std::cout << stack.pop() << std::endl;
    std::cout << stack.top() << std::endl;
    std::cout << stack.top() << std::endl;
    std::cout << stack.pop() << std::endl;
    std::cout << stack.pop() << std::endl;
    std::cout << stack.pop() << std::endl;
    Stack<int> s = stack;
    std::cout << s.pop() << std::endl;
    stack.push(14);
    std::cout << stack.pop() << std::endl;
    std::cout << stack.pop() << std::endl;
    try {
        std::cout << s.pop() << std::endl;
    } catch (const Exception &e) {
        std::cout << e.message() << std::endl;
    }
    return 0;
}

int ArrayDemo() {
    Array<double> array(6, 1.2);
    std::cout << array << std::endl;
    const Array<double> &arrayCopy(array);
    std::cout << array << std::endl;
    std::cout << arrayCopy << std::endl;
    arrayCopy[3] = 12;
    std::cout << array << std::endl;
    std::cout << arrayCopy << std::endl;
    std::cout << array.reverse() << std::endl;
    std::cout << array << std::endl;
    return 0;
}