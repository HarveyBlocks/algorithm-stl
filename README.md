# algorithm-stl

## Project structure

```

ALGORITHM
|   .gitignore
|   CMakeLists.txt
|   data.txt
|   dir-tree.txt
|   mktree.bat
|   README.md
|   
\---src
    |   BTreeTestDemo.cpp
    |   CompilerTestDemo.cpp
    |   ContainerDemo.cpp
    |   main.cpp
    |   MathDemo.cpp
    |   SelectDemo.cpp
    |   SortDemo.cpp
    |   StringDemo.cpp
    |   TreeDemo.cpp
    |   
    +---compiler
    |   \---analysis
    |           TernaryExpressionPhaserByTree.cpp
    |           TernaryExpressionPhaserByTree.h
    |           
    +---container
    |   |   Container.h
    |   |   Heap.h
    |   |   Heap_impl.h
    |   |   
    |   +---associative
    |   |       AssociativeContainer.h
    |   |       Entry.h
    |   |       HashTable.h
    |   |       
    |   \---sequence
    |       |   ArrayList.h
    |       |   DoublyLinkedList.h
    |       |   LinkedList.h
    |       |   PriorityQueue.h
    |       |   Queue.h
    |       |   QueueLinkedList.h
    |       |   QueueLinkedNode.h
    |       |   SequentialAccessibleContainer.h
    |       |   SingleLinkedList.h
    |       |   Stack.h
    |       |   StackLinkedList.h
    |       |   StackLinkedNode.h
    |       |   
    |       \---impl
    |               ArrayList_impl.h
    |               DoublyLinkedList_impl.h
    |               QueueLinkedList_impl.h
    |               Queue_impl.h
    |               StackLinkedList_impl.h
    |               Stack_impl.h
    |               
    +---lang
    |   |   Array.h
    |   |   Array_impl.h
    |   |   BaseObject.cpp
    |   |   BaseObject.h
    |   |   Comparable.h
    |   |   HashCode.h
    |   |   Runnable.h
    |   |   String.cpp
    |   |   String.h
    |   |   StringBuilder.cpp
    |   |   StringBuilder.h
    |   |   Task.h
    |   |   UInt128.cpp
    |   |   UInt128.h
    |   |   
    |   +---exception
    |   |       DivideZeroException.h
    |   |       DownflowException.h
    |   |       Exception.h
    |   |       IllegalArgumentException.h
    |   |       IllegalStateException.h
    |   |       IndexOutOfBoundException.h
    |   |       NullPointException.h
    |   |       OutOfMemoryException.h
    |   |       OverflowException.h
    |   |       UnauthorizedException.h
    |   |       
    |   \---packaging
    |           Byte.cpp
    |           Byte.h
    |           Integer.cpp
    |           Integer.h
    |           
    +---math
    |       AbstractCalculator.h
    |       BigInteger.cpp
    |       BigInteger.h
    |       ByteBigInteger.cpp
    |       ByteBigInteger.h
    |       ByteCalculator.cpp
    |       ByteCalculator.h
    |       Calculator.h
    |       commons.h
    |       Data.cpp
    |       Data.h
    |       DataBasedCalculator.h
    |       MathComparable.h
    |       ShortByteDivider.cpp
    |       ShortByteDivider.h
    |       
    +---objects
    |       BytesObject.h
    |       MetaField.h
    |       MetaObject.h
    |       
    +---tree
    |   |   Trie.cpp
    |   |   Trie.h
    |   |   
    |   +---binary
    |   |   |   AvlTree.h
    |   |   |   BinaryBalanceSearchTree.h
    |   |   |   BinarySearchTree.h
    |   |   |   BinaryTree.h
    |   |   |   BinaryTreeNode.h
    |   |   |   OrderStatisticTree.h
    |   |   |   OrderStatisticTreeNode.h
    |   |   |   RedBlackTree.h
    |   |   |   RedBlackTreeNode.h
    |   |   |   TraversalOrder.h
    |   |   |   TraversalOrderNode.h
    |   |   |   Treap.h
    |   |   |   TreapNode.h
    |   |   |   
    |   |   \---impl
    |   |           BinaryBalanceSearchTree_impl.h
    |   |           BinarySearchTree_impl.h
    |   |           BinaryTreeNode_impl.h
    |   |           BinaryTree_impl.h
    |   |           RedBlackTreeNode_impl.h
    |   |           RedBlackTree_impl.h
    |   |           TraversalOrderNode_impl.h
    |   |           TraversalOrder_impl.h
    |   |           
    |   \---btree
    |       |   BTree.h
    |       |   BTreeData.h
    |       |   BTreeDeclarations.h
    |       |   BTreeElement.h
    |       |   BTreeNode.h
    |       |   BTreeReference.h
    |       |   InsertGroup.h
    |       |   
    |       +---bulk
    |       |       BulkSource.h
    |       |       BulkSource_impl.h
    |       |       NodeSplitPolicyFactory.cpp
    |       |       NodeSplitPolicyFactory.h
    |       |       RootSplitPolicyFactory.cpp
    |       |       RootSplitPolicyFactory.h
    |       |       SplitPolicy.cpp
    |       |       SplitPolicy.h
    |       |       SplitPolicyFactory.cpp
    |       |       SplitPolicyFactory.h
    |       |       
    |       \---impl
    |               BTreeElement_impl.h
    |               BTreeNode_impl.h
    |               BTreeReference_impl.h
    |               BTree_impl.h
    |               
    \---util
        |   Arrays.h
        |   Color.h
        |   ColorfulString.cpp
        |   ColorfulString.h
        |   Comparator.h
        |   Decoder.h
        |   Encoder.h
        |   Objects.cpp
        |   Objects.h
        |   PermutationIterator.cpp
        |   PermutationIterator.h
        |   Random.cpp
        |   Random.h
        |   RandomContainer.h
        |   Reference.h
        |   Times.cpp
        |   Times.h
        |   type.h
        |   
        +---arithmetic
        |       ArithmeticalOperation.h
        |       Calculate24.cpp
        |       Calculate24.h
        |       expression.h
        |       Number.cpp
        |       Number.h
        |       
        +---function
        |       function.h
        |       
        \---sort
                BucketSort.h
                ComparisonSort.h
                CountSort.h
                EncodingSort.h
                InsertionSort.h
                MergeSort.h
                QuickSort.h
                RadixSort.h
                SelectionSort.h
                SortAlgorithm.h
                
```

## Basic class

### Array

### String & StringBuilder

### Exceptions

## BigInteger

## Sort Algorithm

## Container-Sequential

### ArrayList

### LinkedList

### DoubleLinkedList

### Queue

based on LinkedList

### Stack

based on LinkedList

### HashTable

### Heap

## Container-Tree

### Binary Tree and Search Binary Tree

### AVL Tree

### Black-Red Tree

### Traversal

### BTree

### BTree & B*BTree

### Bulk on BTree

### Trie

## Game of Calculate 24

## Utils

### Random

### Reference

### functional

### Comparator

### Types

### Objects





