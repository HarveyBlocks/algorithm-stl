# Data Structures and Algorithms in C++ 🚀

This repository contains a collection of fundamental data structures and algorithms implemented in C++. It serves as a practical resource for learning, experimenting, and potentially integrating these components into larger projects. The project aims to provide efficient and well-documented implementations of common data structures and algorithms, along with demonstrations of their usage. It provides implementations of various data structures like Linked Lists, Stacks, Queues, Trees, Hash Tables, and also implements sorting and searching algorithms.

## 🚀 Key Features

- **Core Data Structures:** Implementations of essential data structures like:
    - Single and Doubly Linked Lists 🔗
    - Stacks and Queues 📊
    - Heaps ⛰️
    - Array Lists 📚
    - Hash Tables 🗄️
    - Binary Search Trees, Red-Black Trees, AVL Trees, and Treaps 🌳
    - B-Trees 🌲

- **Sorting Algorithms:** Implementations of various sorting algorithms:
    - Insertion Sort ⏱️
    - Count Sort 🔢
    - Encoding Sort 🔑
    - Radix Sort 🧮
    - Shell Sort 🐚

- **Searching Algorithms:** Implementation of Binary Search 🔍

- **Mathematical Operations:** Custom data structures for mathematical operations:
    - `Data`, `BigInteger`, and `ByteBigInteger` for handling large numbers ➕
    - Bitwise and shifting operations ⚙️

- **Demonstration and Testing:** Example code showcasing the usage of each data structure and algorithm. 🧪

- **Calculator24 Solver:** Solves the 24 game using given numbers and arithmetic operations. 🎮

## 🛠️ Tech Stack

- **Language:** C++ 💻
- **Standard Library:** STL (Standard Template Library)
- **Data Structures:** Custom implementations (e.g., `SingleLinkedList`, `HashTable`, `BTree`, `Data`, `BigInteger`)
- **Algorithms:** Custom implementations (e.g., `InsertionSort`, `RadixSort`, `EncodingSort`)
- **Build Tool:** (Assumed to be a standard C++ compiler like g++, but not explicitly specified)

## 📦 Getting Started / Setup Instructions

### Prerequisites

- A C++ compiler (e.g., g++)
- A suitable development environment (e.g., VS Code, CLion)

### Installation

1.  Clone the repository:

    ```bash
    git clone https://github.com/HarveyBlocks/algorithm-stl
    cd algorithm-stl
    ```

2.  Compile the desired source file (e.g., `src/main.cpp` or one of the demo files):

    ```bash
    g++ -o main src/main.cpp
    ```

    Or, to compile all demo files:

    ```bash
    g++ -o ContainerDemo src/ContainerDemo.cpp
    g++ -o SelectDemo src/SelectDemo.cpp
    g++ -o MathDemo src/MathDemo.cpp
    g++ -o BTreeTestDemo src/BTreeTestDemo.cpp
    g++ -o SortDemo src/SortDemo.cpp
    g++ -o CompilerTestDemo src/CompilerTestDemo.cpp
    g++ -o TreeDemo src/TreeDemo.cpp
    g++ -o StringDemo src/StringDemo.cpp
    ```

### Running Locally

1.  Execute the compiled file:

    ```bash
    ./main
    ```

    Or, if you compiled a demo file:

    ```bash
    ./ContainerDemo
    ./SelectDemo
    ./MathDemo
    ./BTreeTestDemo
    ./SortDemo
    ./CompilerTestDemo
    ./TreeDemo
    ./StringDemo
    ```

## 💻 Usage

The repository is structured into several demo files, each showcasing the usage of specific data structures or algorithms.

- `src/main.cpp`: Contains basic pointer and increment operator tests.
- `src/ContainerDemo.cpp`: Demonstrates the usage of various container data structures.
- `src/SelectDemo.cpp`: Demonstrates selection and searching algorithms.
- `src/MathDemo.cpp`: Demonstrates mathematical operations using custom data structures.
- `src/BTreeTestDemo.cpp`: Tests the functionality of the B-Tree implementation.
- `src/SortDemo.cpp`: Demonstrates and tests various sorting algorithms.
- `src/CompilerTestDemo.cpp`: Contains a (failed) attempt to parse ternary expressions.
- `src/TreeDemo.cpp`: Demonstrates and tests various binary tree implementations.
- `src/StringDemo.cpp`: Demonstrates the usage of the `String` class and related utilities.

To use a specific data structure or algorithm in your own project, simply include the corresponding header file and utilize the provided classes and functions.

## 📂 Project Structure

```
├── src/
│   ├── main.cpp
│   ├── ContainerDemo.cpp
│   ├── SelectDemo.cpp
│   ├── MathDemo.cpp
│   ├── BTreeTestDemo.cpp
│   ├── SortDemo.cpp
│   ├── CompilerTestDemo.cpp
│   ├── TreeDemo.cpp
│   ├── StringDemo.cpp
│   ├── math/
│   │   ├── Calculator.h
│   │   ├── DataBasedCalculator.h
│   │   ├── BigInteger.h
│   │   ├── ByteBigInteger.h
│   │   └── ...
│   ├── util/
│   │   ├── arithmetic/
│   │   │   ├── Calculate24.h
│   │   │   └── ArithmeticalOperation.h
│   │   ├── sort/
│   │   │   ├── InsertionSort.h
│   │   │   ├── CountSort.h
│   │   │   ├── EncodingSort.h
│   │   │   ├── RadixSort.h
│   │   │   └── ...
│   │   ├── Random.h
│   │   ├── Times.h
│   │   ├── RandomContainer.h
│   │   ├── PermutationIterator.h
│   │   └── ...
│   ├── container/
│   │   ├── Container.h
│   │   ├── sequence/
│   │   │   ├── SingleLinkedList.h
│   │   │   └── ...
│   │   └── ...
│   ├── tree/
│   │   ├── binary/
│   │   │   ├── BinarySearchTree.h
│   │   │   ├── RedBlackTree.h
│   │   │   ├── AvlTree.h
│   │   │   ├── Treap.h
│   │   │   ├── OrderStatisticTreeNode.h
│   │   │   └── OrderStatisticTree.h
│   │   └── btree/
│   │       ├── BTree.h
│   │       └── ...
│   ├── lang/
│   │   ├── String.h
│   │   ├── StringBuilder.h
│   │   ├── ColorfulString.h
│   │   ├── exception/
│   │   │   ├── IllegalArgumentException.h
│   │   │   ├── OutOfMemoryException.h
│   │   │   ├── IllegalStateException.h
│   │   │   └── DivideZeroException.h
│   │   └── ...
│   └── commons.h
├── README.md
└── ...
```

## 📸 Screenshots

(Add screenshots of the data structures and algorithms in action here)

## 🤝 Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues to suggest improvements or report bugs.

## 📝 License

This project is licensed under the [APACHE License](LICENSE).

## 📬 Contact

[HarveyBlocks] - [HarveyBlocks@outlook.com]

## 💖 Thanks Message

Thank you for checking out this repository! We hope you find it useful for learning and experimenting with data structures and algorithms in C++.
