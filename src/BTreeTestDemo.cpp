#define DEBUG

#include <fstream>
#include "tree/BTree.h"
#include "./util/Random.h"

using namespace std;

using IntBTreeTrace = BTreeTrace<int, Greater<int>>;
using IntBTree = BTree<int, Greater<int>>;

IntBTree &buildBTree(IntBTree &bTree, const std::vector<int> &src) {
    for (const auto &item: src) {
        bTree.insert(item);
    }
    return bTree;
}

void showDatas(const vector<int> &data, ostream &os) {
    os << "[";
    for (int i = 0; i < data.size(); ++i) {
        os << data[i] << ",]"[i == data.size() - 1];
    }
    os << std::endl;
}

int btreeDemoLoop() {
    std::cout << "loop" << std::endl;
    int cnt = 1000;
    // ofstream os("../data.txt");
    while (cnt-- > 0) {
        size_t size = Random::unsignedInt() % 10000 + 50;
        vector<int> datas(size);
        for (int i = 0; i < size; ++i) {
            datas[i] = Random::signedInt(-1000, 1000);
        }
        BTree<int, Greater<int>> bTree(int(Random::unsignedInt() % 20 + 3));
        buildBTree(bTree, datas);
        if (cnt % 100 == 0) {
            std::cout << "ping..." << bTree.calRate() << std::endl;
        }
        Random::shuffle(datas);
        for (const auto &item: datas) {
            IntBTreeTrace trace = bTree.search(item);
            bTree.remove(trace);
        }
    }
    return 0;
}


int bigDataBtreeDemo() {
    std::cout << "big data" << std::endl;
//    ofstream os("../data.txt");
    size_t size = 10000000;
    Random::resetSeed();
    vector<int> datas(size);
    for (int i = 0; i < size; ++i) {
        datas[i] = Random::signedInt(-10000, 10000);
    }
    BTree<int, Greater<int>> bTree(20);
    buildBTree(bTree, datas);
    Random::shuffle(datas);
    for (int i = 0; i < datas.size(); ++i) {
        IntBTreeTrace trace = bTree.search(datas[i]);
        bTree.remove(trace);
        if (i % 1000000 == 0) {
            std::cout << "ping..." << bTree.calRate() << std::endl;
        }
    }
    return 0;
}


int btreeDemo() {
    // 2 8 12 18 30 24 6 5 4 1 3
    IntBTree bTree(4);
    const vector<int> &src{
            2, 8, 12, 18, 30, 24, 6, 5, 4, 1, 3, 46, 73, 45, 39, 2, 6, 83, 55, 89, 21, 37, 4, 64, 100, 66, 14, 43, 34,
            87, 20, 8, 91, 86, 74, 29, 69, 65, 11, 85, 63, 30, 62, 44, 77, 16, 28, 90, 17, 81, 68, 9, 75, 79, 35, 19,
            31, 10, 67, 51, 40, 58, 94, 72, 12, 42, 18, 1, 24, 49, 76, 32, 7, 96, 56, 48, 27, 97, 88, 23, 0, 99, 78, 59,
            50, 22, 53, 26, 36, 93, 61, 70, 54, 60, 92, 95, 57, 82, 84, 15, 47, 38, 33, 3, 98, 13, 5, 71, 80, 52, 25
    };
    ofstream os("../data.txt");
    buildBTree(bTree, src);
    bTree.showBTree(os);
    return 0;
}


// 一. 优化思路
//  序号 策略                                                          效果(目标填充率)
//  0. 普通的B+Tree                                                      55%-65%
//  1. B*Tree, 插入时不分裂, 转移到兄弟, 兄弟也满了才分裂                    75%-85%
// TODO
//  2. 对数据进行批量插入的优化, 批量插入的数据排序后再插入(Bulk)
//  3. 检测(How To Get?)到比较稀疏, 就触发合并什么的
// 二. 序列化
//  T* 要搞成T, 但是这样又...因为要转化...导致大量的IO, 很复杂!
//  考虑使用某种"代理"呢? 就是内存中的BTree结构使用的是代理T,
// 三. IO
int BTreeTestDemoCode = /*btreeDemo() &&*/ btreeDemoLoop() | bigDataBtreeDemo();