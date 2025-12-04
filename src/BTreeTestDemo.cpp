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
    int cnt = 1000;
    ofstream os("../data.txt");
    while (cnt-- > 0) {
        size_t size = Random::unsignedInt() % 10000 + 50;
        vector<int> datas(size);
        for (int i = 0; i < size; ++i) {
            datas[i] = Random::signedInt(-1000, 1000);
        }
        BTree<int, Greater<int>> bTree(int(Random::unsignedInt() % 20 + 3));
        buildBTree(bTree, datas);
        if (cnt % 100 == 0) {
            std::cout << "ping..." << std::endl;
            bTree.showBTree(os);
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
//    ofstream os("../data.txt");
    size_t size = 1000000;
    Random::resetSeed();
    vector<int> datas(size);
    for (int i = 0; i < size; ++i) {
        datas[i] = Random::signedInt(-10000, 10000);
    }
    BTree<int, Greater<int>> bTree(20);
    buildBTree(bTree, datas);
    std::cout << "ping..." << std::endl;
    // bTree.showBTree(os);
//    os.close();
    std::cout << bTree.calRate() << std::endl;
    std::cout << "pong..." << std::endl;
    Random::shuffle(datas);
    for (const auto &item: datas) {
        IntBTreeTrace trace = bTree.search(item);
        bTree.remove(trace);
    }
    return 0;
}

int btreeDemo() {

    return 0;
}

// TODO 优化思路
//  1. B*Tree, 插入时不分裂, 转移到兄弟, 兄弟也满了才分裂
//  2. 对数据进行批量插入的优化, 批量插入的数据排序后再插入(Bulk)
//  3. 检测(目标填充率-How To Get?)到比较稀疏, 就触发合并
int BTreeTestDemoCode = btreeDemo();