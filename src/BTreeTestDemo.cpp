#define DEBUG

#define BULK

#include <fstream>
#include "tree/btree/BTree.h"
#include "./util/Random.h"

namespace harvey::algorithm::tree::btree {

    using IntBTreeTrace = BTreeTrace<int, Greater<int>>;
    using IntBTree = BTree<int, Greater<int>>;

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
//  3. 对数据进行批量插入的优化, 批量插入的数据排序后再插入(Bulk)                85%-100%
// 二. 序列化
//  T* 要搞成T, 但是这样又...因为要转化...导致大量的IO, 很复杂!
//  考虑使用某种"代理"呢? 就是内存中的BTree结构使用的是代理T,
// 三. IO

#ifdef BASIC_BTREE
    bool BTreeTestDemoCode = /*btreeDemo() &&*/ btreeDemoLoop() && bigDataBtreeDemo();
#endif

};

// TODO 调试时开启 #define CLOSE_BULK_POLICY_CACHE 关闭缓存
//#define CLOSE_BULK_POLICY_CACHE

#ifndef CLOSE_BULK_POLICY_CACHE

#include "util/type.h"

#endif

namespace harvey::algorithm::tree::btree::bulk {
    struct SplitPolicy {
        int layer;
        int nodeSize;
        /**
         * smallerChildSize = biggerChildSize - 1
         */
        int smallerChildSize;
        /**
         * biggerChildrenCount + smallerChildrenCount = nodeSize + 1
         * 0 <= smallerChildrenCount < nodeSize + 1
         */
        int biggerChildrenCount;

        SplitPolicy() : SplitPolicy(0, 0, 0, 0) {}

        SplitPolicy(int layer, int nodeSize, int smallerChildSize, int biggerChildrenCount) :
                layer(layer), nodeSize(nodeSize), smallerChildSize(smallerChildSize),
                biggerChildrenCount(biggerChildrenCount) {}

        [[nodiscard]] bool found() const {
            return layer != 0;
        }

        void update(const SplitPolicy &challenger) {
            // ok and better
            this->layer = challenger.layer;
            this->nodeSize = challenger.nodeSize;
            this->smallerChildSize = challenger.smallerChildSize;
            this->biggerChildrenCount = challenger.biggerChildrenCount;
        }

        [[nodiscard]] bool ok(int childSizeMin, int childSizeMax) const {
            // 1. if(smaller) smaller >= child_min
            return (biggerChildrenCount == 0 ||
                    childSizeMin <= smallerChildSize + 1 && smallerChildSize + 1 <= childSizeMax) &&
                   // 2. if(bigger) bigger >= child_min
                   childSizeMin <= smallerChildSize && smallerChildSize <= childSizeMax;
        }
    };


    class SplitPolicyFactory {
    private:
        static int power(int a, int b) {
            int res = 1;
            for (int i = 0; i < b; i++) res *= a;
            return res;
        }

    protected:

        [[nodiscard]] int maxOn(int layer) const {
            return power(level, layer) - 1;
        }

        [[nodiscard]] int minOn(int layer) const {
            int lb = (level - 1) >> 1;
            return power(lb + 1, layer) - 1;
        }

        [[nodiscard]] SplitPolicy create(int sourceSize, int layer, int lowerBound) const {
            if (sourceSize < lowerBound) {
                return {};
            }
            if (sourceSize < level) {// leaf
                return {1, sourceSize, 0, 0};
            }
            layer = getLayer(sourceSize, layer);
            int childMin = minOn(layer);
            int childMax = maxOn(layer);
            SplitPolicy policy;
            for (int nodeSize = level - 1; nodeSize >= lowerBound; --nodeSize) {
                int sourceForChild = sourceSize - nodeSize;
                int childrenCount = nodeSize + 1;
                if (policy.found() && childMax * childrenCount < sourceForChild) {
                    // 已经溢出
                    break;
                }
                int biggerChildrenCount = sourceForChild % childrenCount;
                int smallerChildSize = (sourceForChild - biggerChildrenCount) / childrenCount;
                SplitPolicy challenger(layer + 1, nodeSize, smallerChildSize, biggerChildrenCount);
                if (challenger.ok(childMin, childMax)) {
                    policy.update(challenger);
                }
            }
            return policy;
        }

        [[nodiscard]] virtual int getLayer(int sourceSize, int layer) const = 0;

    public:
        const int level;

        explicit SplitPolicyFactory(int level) : level(level) {}

        /**
         * 1. 让size尽可能大, 这样layer就会尽可能小 <br>
         * 2. size=level-1, 取得理论layer最小值 <br>
         * 3. size--, 这样layer就会逐渐丰满 <br>
         * @param sourceSize
         * @param layer 包含node
         * @return
         */
        [[nodiscard]] virtual SplitPolicy create(int sourceSize, int layer) = 0;

        virtual SplitPolicyFactory *childFactory() = 0;


        virtual ~SplitPolicyFactory() = default;
    };

    // 要求layer, 就一定是layer!
    // layer->level
    // policy.smaller*policy.smaller.count+
    // (policy.smaller+1)*(sourceSize-policy.smaller.count-policy.node)+
    // policy.node
    class NodeSplitPolicyFactory : public SplitPolicyFactory {
    private:
#ifndef CLOSE_BULK_POLICY_CACHE
        std::unordered_map<int64, SplitPolicy> cache;
#endif
    public:
        explicit NodeSplitPolicyFactory(int level) : SplitPolicyFactory(level) {}

        [[nodiscard]] int getLayer(int sourceSize, int layer) const override {
            return layer - 1;
        }

        SplitPolicy create(int sourceSize, int layer) override {
#ifndef CLOSE_BULK_POLICY_CACHE
            // 缓存增强
            int64 key = int64(sourceSize) << 32 | layer;
            const std::unordered_map<int64, SplitPolicy>::iterator &find = cache.find(key);
            if (find != cache.end()) {
                return find->second;
            }
#endif
            const SplitPolicy &policy = this->SplitPolicyFactory::create(sourceSize, layer, (level - 1) >> 1);
#ifndef CLOSE_BULK_POLICY_CACHE
            cache.insert({key, policy});
#endif
            return policy;
        }

        SplitPolicyFactory *childFactory() override { return this; }
    };

    class RootSplitPolicyFactory : public SplitPolicyFactory {
    private:
        NodeSplitPolicyFactory *_childFactory = nullptr;
    public:
        explicit RootSplitPolicyFactory(int level) : SplitPolicyFactory(level) {}

        [[nodiscard]] int getLayer(int sourceSize, int layer) const override {
            // child layer
            int sourceForChild = sourceSize - level + 1;
            int childrenCount = level;
            for (layer = 1; maxOn(layer) * childrenCount < sourceForChild; layer++);
            // 此时的layer是完全可以hold住sourceForChild的
            return layer;
        }

        SplitPolicy create(int sourceSize, int layer) override {
            return this->SplitPolicyFactory::create(sourceSize, layer, 1);
        }


        SplitPolicyFactory *childFactory() override {
            if (_childFactory == nullptr) {
                _childFactory = new NodeSplitPolicyFactory(level); // init
            }
            return _childFactory;
        }

        ~RootSplitPolicyFactory() override {
            delete _childFactory;
        }
    };


    template<typename T>
    class BulkSource {
        typename std::vector<T>::const_iterator begin;
        typename std::vector<T>::const_iterator end;
    public:
        explicit BulkSource(
                const typename std::vector<T>::const_iterator &begin,
                const typename std::vector<T>::const_iterator &end) :
                begin(begin), end(end) {}

        template<typename Cmp = Greater<T>>
        [[nodiscard]] BTreeNodeReference<T, Cmp> build(int level) const {// 判断, 调度
            if (sourceSize() == 0) {
                // empty, then return
                return BTreeNodeReference<T, Cmp>(new BTreeNode<T, Cmp>(level));
            }
            bulk::RootSplitPolicyFactory factory(level);
            BTreeNodeReference<T, Cmp> node = build<Cmp>(&factory, 1); // 这个layer是随便的, 因为对于root其不生效
            return node;
        }

    private:

        [[nodiscard]] int sourceSize() const {
            return end - begin;
        }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

        // TODO 解开递归
        template<typename Cmp = Greater<T>>
        [[nodiscard]] BTreeNodeReference<T, Cmp> build(bulk::SplitPolicyFactory *factory, int layer) const {
            BTreeNodeReference<T, Cmp> node(new BTreeNode<T, Cmp>(factory->level));
            const bulk::SplitPolicy policy = factory->create(sourceSize(), layer/*包含node*/);
            if (!policy.found()) {
                throw IllegalStateException("not find bulk build policy!");
            }
            node->resize(policy.nodeSize);
            if (policy.layer == 1) { // leaf
                // 递归出口
                for (int i = 0; i < policy.nodeSize; ++i) {
                    node->setData(i, BTreeData<T>(*(begin + i)));
                }
                return node;
            }
            int childLayer = policy.layer - 1; // for children
            bulk::SplitPolicyFactory *childFactory = factory->childFactory();
            typename std::vector<T>::const_iterator childBegin = begin;
            for (int i = 0; i < policy.nodeSize; ++i) {
                int limit = policy.smallerChildSize + (i < policy.biggerChildrenCount ? 1 /*bigger*/: 0);
                auto childEnd = childBegin + limit;
                BTreeNodeReference<T, Cmp> child = BulkSource<T>(childBegin, childEnd)
                        .build<Cmp>(childFactory, childLayer);
                node->setChild(i, child);
                node->setData(i, BTreeData<T>(*(childEnd)));
                // 1 for parent
                childBegin = childEnd + 1;
            }
            BTreeNodeReference<T, Cmp> child = BulkSource<T>(childBegin, end).build<Cmp>(childFactory, childLayer);
            node->setChild(policy.nodeSize, child);
            return node;
        }

#pragma clang diagnostic pop
    };
}
namespace harvey::algorithm::tree::btree {


    template<typename T, typename Cmp>
    BTree<T, Cmp> &BTree<T, Cmp>::bulk(const bulk::BulkSource<T> &source) {
        // 1. 用count算出能建造出几层的树(不考虑是否需要分裂)->N层及以上, N+1层以下
        // 2. 构建N-1层(满), 需要元素X_1个, count==K*X+(K-1)+M
        //      特别的, 构建N-2层满, 需要元素X_2个
        // 3. 如果M==0, 构建K个N-1层(满), root节点的元素是K-1个, 由于条件一, K<level-1
        // 4. 如果M>0, 构建K+1个N-1层, 但不满, 每一个的个数是count_1 = (count-k)/(k+1)
        //      由条件1,2得X_2<count_1<X_1
        // 故可以递归得构建, 步骤一二的判断过程直接执行, 步骤三四递归构架树, 将source划分成一块一块的, 然后构建
        clear();
        root.release();
        root = source.template build<Cmp>(level);
        return *this;
    }

}

#include <algorithm>

namespace harvey::algorithm::tree::btree {

    bool bulkLoopDemo() {
        for (int n = 0; n < 100000; n += Random::signedInt(1, 100)) {
            std::vector<int> src(n);
            for (int i = 0; i < n; ++i) {
                src[i] = i;
            }
            int level = Random::signedInt(3, 20);
            IntBTree bTree(level);
            bTree.bulk(bulk::BulkSource<int>(src.begin(), src.end()));
            // bTree.showBTree();
            int maxDepth = bTree.qualified();
            if (n % 100 == 0) {
                std::cout << "ping...level = " << level << ", n = " << n << ", max-depth = " << maxDepth
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
        int level = Random::signedInt(5, 20);
        std::cout << "start...level = " << level << ",n = " << n << std::endl;
        IntBTree bTree(level);
        bTree.bulk(bulk::BulkSource<int>(src.begin(), src.end()));
        // bTree.showBTree();
        std::cout << "max-depth = " << bTree.qualified() << std::endl;
        std::cout << "rate = " << bTree.calRate() << std::endl;
        return true;
    }

#ifdef BULK
    bool bulkDemoSucceed = bulkLoopDemo() && bulkBigDataDemo();
#endif

}