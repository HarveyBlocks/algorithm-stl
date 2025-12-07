#include "tree/binary/BinarySearchTree.h"
#include "tree/binary/RedBlackTree.h"
#include "util/Random.h"
#include "tree/binary/AvlTree.h"
#include "tree/binary/Treap.h"
#include "util/sort/InsertionSort.h"
#include "tree/binary/OrderStatisticTreeNode.h"
#include "tree/binary/OrderStatisticTree.h"


int rbTreeDemo(bool show = false);

int treeDemo(bool show = false);

int avlTreeDemo(bool show = false);

int loopTreeDemo();

int treapDemo(bool show = false);

int loopTreeDemo() {
    Random::resetSeed();
    int count = 1000000;
    while (count-- > 0) {
        rbTreeDemo();
        if (count % 10000 == 0) {
            rbTreeDemo(true);
            std::cout << std::flush;
        }
    }
    return 0;
}

int depthTreeDemo(bool show = false) {
    Random::resetSeed();
    BinarySearchTree<int> tree;
    for (int i = 0; i < 32; ++i) {
        int value = Random::unsignedByte() % 10;
        if (show) std::cout << value << " ";
        tree.insert(value);
    }
    if (show) std::cout << "\n";
    if (show) BinaryTree<int>::printTree(std::cout, tree);
    if (show)
        std::cout << "max depth: " << BinaryTree<int>::maxDepth(tree.getRoot())
                  << ", min depth: " << BinaryTree<int>::minDepth(tree.getRoot());
    return 0;
}


int treeDemo(bool show) {
    BinarySearchTree<int> tree;
    for (int i = 0; i < 32; ++i) {
        int value = Random::unsignedByte() % 10;
        if (show) std::cout << value << " ";
        tree.insert(value);
    }
    if (show) std::cout << "\n";
    if (show) std::cout << tree << "\n";
    while (!tree.empty()) {
        unsigned char value = Random::unsignedByte() % 10;
        if (tree.remove(value)) {
            if (show) std::cout << int(value) << ": " << tree << '\n';
        }
    }
    return 0;
}


int avlTreeDemo(bool show) {
    AvlTree<int> tree;
    try {
        for (int i = 0; i < 44; ++i) {
            int value = Random::unsignedByte() % 10;
            if (show) std::cout << value << " ";
            tree.insert(value);
        }
    } catch (const Exception &e) {
        std::cout << e.message();
        tree.print(std::cout);
        return -1;
    }
    if (show) std::cout << "\n";
    if (show) tree.print(std::cout);
    if (show) {
        BiConsumer<std::ostream &, BinaryTreeNode<int> *> printer =
                [](std::ostream &os, BinaryTreeNode<int> *node) {
                    os << *node;
                };
        BinaryTree<int>::printNode(std::cout, tree.getRoot(), 1, printer);
    }
    try {
        while (!tree.empty()) {
            unsigned char value = Random::unsignedByte() % 10;
            if (tree.remove(value)) {
                if (show) std::cout << int(value) << ": " << tree << '\n';
            }
        }
    } catch (const Exception &e) {
        std::cout << e.message() << std::endl;
        tree.print(std::cout);
        std::cout << std::flush;
        return -1;
    }
    return 0;
}

int rbTreeDemo(bool show) {
    RedBlackTree<int> tree;
    try {
        for (int i = 0; i < 100; ++i) {
            int value = Random::unsignedByte() % 100;
            if (show) std::cout << value << " ";
            tree.insert(value);
            // if (show) tree.printWithColor(cout);
        }
    } catch (const Exception &e) {
        std::cout << e.message() << std::endl;
        tree.printWithColor(std::cout);
        std::cout << std::flush;
        return -1;
    }
    if (show) std::cout << "\n" << tree << " \n";
    // if (show) tree.printWithColor(cout);
    try {
        while (!tree.empty()) {
            unsigned char value = Random::unsignedByte() % 100;
            if (tree.remove(value)) {
                if (show) std::cout << int(value) << ": " << tree << '\n';
                //  if (show) tree.printWithColor(cout);
            }
        }
    } catch (const Exception &e) {
        std::cout << e.message() << std::endl;
        tree.printWithColor(std::cout);
        std::cout << std::flush;
        return -1;
    }
    return 0;
}

int treapDemo(bool show) {
    Treap<int> treap;
    try {
        Array<int> src(20);
        for (int i = 0; i < 20; ++i) {
            src[i] = Random::unsignedByte() % 10;
        }
        InsertionSort(src).sort();
        std::cout << src << std::endl;
        for (int i = 0; i < 20; ++i) {
            int value = src[i];
            if (show) std::cout << value << " ";
            treap.insert(value);
            treap.printPriority(std::cout);
            std::cout << treap << std::flush;
        }
    } catch (const Exception &e) {
        std::cout << e.message() << std::endl;
        treap.printPriority(std::cout);
        std::cout << treap << std::flush;
        return -1;
    }
    return 0;
}

int orderStaticDemo(bool show = false) {
    OrderStatisticTree<int> tree;
    try {
        for (int i = 0; i < 100; ++i) {
            int value = Random::unsignedByte() % 100;
            if (show) std::cout << value << " ";
            tree.insert(value);
            // if (show) tree.printWithColor(cout);
        }
    } catch (const Exception &e) {
        std::cout << e.message() << std::endl;
        tree.printWithColor(std::cout);
        std::cout << std::flush;
        return -1;
    }
    std::cout << std::endl;
    if (show) std::cout << tree << std::endl;
    for (int i = 0; i < 100; ++i) {
        int *value = tree.head(i);
        if (value == nullptr) {
            std::cout << "null" << ",";
        } else {
            std::cout << *value << ",";
        }
    }
    std::cout << std::endl;
    return 0;
}

//int treeCode = orderStaticDemo(true);