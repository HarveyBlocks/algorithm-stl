#define DEBUG


#define BULK // or BULK

#include <fstream>
#include "tree/btree/BTree.h"
#include "./util/Random.h"

namespace harvey::algorithm::tree::btree {
    using IntBTreeTrace = BTreeTrace<int, Greater<int>>;
    using IntBTree = BTree<int, Greater<int>>;
}

#ifdef BTREE_BASE
namespace harvey::algorithm::tree::btree {


    IntBTree &buildBTree(IntBTree &bTree, const std::vector<int> &src) {
        for (const auto &item: src) {
            bTree.insert(item);
        }
        return bTree;
    }

    void showDatas(const std::vector<int> &data, std::ostream &os) {
        os << "[";
        for (int i = 0; i < data.size(); ++i) {
            os << data[i] << ",]"[i == data.size() - 1];
        }
        os << std::endl;
    }

    bool btreeDemoLoop() {
        std::cout << "loop" << std::endl;
        int cnt = 1000;
        // ofstream os("../data.txt");
        while (cnt-- > 0) {
            size_t size = Random::unsignedInt() % 10000 + 50;
            std::vector<int> datas(size);
            for (int i = 0; i < size; ++i) {
                datas[i] = Random::signedInt(-1000, 1000);
            }
            BTree<int, Greater<int>> bTree(int(Random::unsignedInt() % 20 + 3));
            buildBTree(bTree, datas);
            if (cnt % 100 == 0) {
                std::cout << "ping..." << bTree.calRate() << std::endl;
                // 这一次就使用clear进行测试吧
                bTree.clear();
                // return false;
            } else {
                Random::shuffle(datas);
                for (const auto &item: datas) {
                    IntBTreeTrace trace = bTree.search(item);
                    bTree.remove(trace);
                }
            }
            if (!bTree.empty()) {
                throw IllegalStateException("should be empty");
            }
        }
        return true;
    }


    bool bigDataBtreeDemo() {
        std::cout << "big data" << std::endl;
//    ofstream os("../data.txt");
        size_t size = 10000000;
        Random::resetSeed();
        std::vector<int> datas(size);
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
        return true;
    }


    int btreeDemo() {
        // 2 8 12 18 30 24 6 5 4 1 3
        IntBTree bTree(4);
        const std::vector<int> &src{
                2, 8, 12, 18, 30, 24, 6, 5, 4, 1, 3, 46, 73, 45, 39, 2, 6, 83, 55, 89, 21, 37, 4, 64, 100, 66, 14, 43,
                34,
                87, 20, 8, 91, 86, 74, 29, 69, 65, 11, 85, 63, 30, 62, 44, 77, 16, 28, 90, 17, 81, 68, 9, 75, 79, 35,
                19,
                31, 10, 67, 51, 40, 58, 94, 72, 12, 42, 18, 1, 24, 49, 76, 32, 7, 96, 56, 48, 27, 97, 88, 23, 0, 99, 78,
                59,
                50, 22, 53, 26, 36, 93, 61, 70, 54, 60, 92, 95, 57, 82, 84, 15, 47, 38, 33, 3, 98, 13, 5, 71, 80, 52, 25
        };
        std::ofstream os("../data.txt");
        buildBTree(bTree, src);
        bTree.showBTree(os);
        return 0;
    }


    bool BTreeTestDemoCode = /*btreeDemo() &&*/ btreeDemoLoop() && bigDataBtreeDemo();

};
#endif

#ifdef BULK
// 调试时开启 #define CLOSE_BULK_POLICY_CACHE 关闭缓存
// #define CLOSE_BULK_POLICY_CACHE
namespace harvey::algorithm::tree::btree {

    using IntBulkSource = bulk::BulkSource<int>;

    bool bulkLoopDemo() {
        for (int n = 0; n < 100000; n += Random::signedInt(1, 100)) {
            std::vector<int> src(n);
            for (int i = 0; i < n; ++i) {
                src[i] = i;
            }
            int order = Random::signedInt(3, 100);
            IntBTree bTree(order);
            bTree.bulk(IntBulkSource(src.begin(), src.end()));
            // bTree.showBTree();
            int maxDepth = bTree.qualified();
            if (n % 100 == 0) {
                std::cout << "ping...order = " << order << ", n = " << n << ", max-depth = " << maxDepth
                          << ", rate = " << bTree.calRate() << std::endl;
            }
        }
        return true;
    }

    bool bulkBigDataDemo() {
        // 大数据测试
        int n = 100000000;
        std::vector<int> src(n);
        for (int i = 0; i < n; ++i) {
            src[i] = i;
        }
        int order = Random::signedInt(5, 100);
        std::cout << "start...order = " << order << ",n = " << n << std::endl;
        IntBTree bTree(order);
        bTree.bulk(IntBulkSource(src.begin(), src.end()));
        // bTree.showBTree();
        std::cout << "max-depth = " << bTree.qualified() << std::endl;
        std::cout << "rate = " << bTree.calRate() << std::endl;
        return true; // 释放资源这一步最消耗时间
    }

    bool bulkDemo() {
        int n = 96;
        std::vector<int> src(n);
        for (int i = 0; i < n; ++i) {
            src[i] = i;
        }
        int order = 48;
        IntBTree bTree(order);
        bTree.bulk(IntBulkSource(src.begin(), src.end()));
        bTree.showBTree();
        int maxDepth = bTree.qualified();
        std::cout << "ping...order = " << order << ", n = " << n << ", max-depth = " << maxDepth
                  << ", rate = " << bTree.calRate() << std::endl;
        return true;
    }

    bool bulkDemoSucceed = bulkBigDataDemo() && bulkDemo() && bulkLoopDemo();

}
#endif

// 一. 优化思路
//  序号 策略                                                          效果(目标填充率)
//  0. 普通的B+Tree                                                      55%-65%
//  1. B*Tree, 插入时不分裂, 转移到兄弟, 兄弟也满了才分裂                      75%-85%
//  2. 检测(How To Get?)到比较稀疏, 就触发合并什么的(在Node设置一个rate字段吗?)
//      设置element_count表示存储的值有多少,node_count表示有几个节点:
//          parent.element_count = parent.size+(leaf?0:stream(parent.children).map(node::element_count).sum())
//          parent.node_count = 1+(leaf?0:stream(parent.children).map(node::node_count).sum())
//      每插入元素一个到node, 两个值的变化:
//      - 元素直接插入到节点  this.element_count++, parent.element_count++(递归)
//      - 元素延迟插入到节点  this.brother.element_count++, parent.element_count++(递归)
//      - 节点分裂          reset(new_node_left.element_count), reset(new_node_right.element_count), parent.element_count++(递归)
//      每删除元素一个
//      还要考虑如果检测到太低了, 又如何进行节点合并呢?把一个太少的+合并到兄弟?
//  3. 对数据进行批量插入的优化, 批量插入的数据排序后再插入(Bulk)                85%-100%,
//        有一个很有意思的数据点, order=48, n=96, 由于下限的存在, 即使是最优方案, 还是会留出大量的空间
// 二. 序列化
//  T* 要搞成T, 但是这样又...因为要转化...导致大量的IO, 很复杂!
//  考虑使用某种"代理"呢? 就是内存中的BTree结构使用的是代理T,
// 三. IO
