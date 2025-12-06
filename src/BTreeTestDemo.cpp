#define DEBUG

#define BULK

#include <fstream>
#include "tree/btree/BTree.h"
#include "./util/Random.h"

using namespace harvey::algorithm::tree::btree;

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
            2, 8, 12, 18, 30, 24, 6, 5, 4, 1, 3, 46, 73, 45, 39, 2, 6, 83, 55, 89, 21, 37, 4, 64, 100, 66, 14, 43, 34,
            87, 20, 8, 91, 86, 74, 29, 69, 65, 11, 85, 63, 30, 62, 44, 77, 16, 28, 90, 17, 81, 68, 9, 75, 79, 35, 19,
            31, 10, 67, 51, 40, 58, 94, 72, 12, 42, 18, 1, 24, 49, 76, 32, 7, 96, 56, 48, 27, 97, 88, 23, 0, 99, 78, 59,
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
//
// TODO
//  3. 对数据进行批量插入的优化, 批量插入的数据排序后再插入(Bulk)
// 二. 序列化
//  T* 要搞成T, 但是这样又...因为要转化...导致大量的IO, 很复杂!
//  考虑使用某种"代理"呢? 就是内存中的BTree结构使用的是代理T,
// 三. IO
#ifdef BASIC_BTREE
bool BTreeTestDemoCode = /*btreeDemo() &&*/ btreeDemoLoop() && bigDataBtreeDemo();
#endif

namespace harvey::algorithm::tree::btree {
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
        int smallerChildrenCount;

        SplitPolicy() : SplitPolicy(-1, 0, 0, 0) {}

        SplitPolicy(int layer, int nodeSize, int smallerChildSize, int smallerChildrenCount) :
                layer(layer), nodeSize(nodeSize), smallerChildSize(smallerChildSize),
                smallerChildrenCount(smallerChildrenCount) {}

        [[nodiscard]] bool notFound() const {
            return nodeSize == -1;
        }

        void update(const SplitPolicy &challenger) {
            // ok and better
            this->layer = challenger.layer;
            this->nodeSize = challenger.nodeSize;
            this->smallerChildSize = challenger.smallerChildSize;
            this->smallerChildrenCount = challenger.smallerChildrenCount;
        }

        [[nodiscard]] bool ok(int childSizeMin) const {
            // 1. if(smaller) smaller >= child_min
            return (smallerChildrenCount == 0 || smallerChildSize >= childSizeMin) &&
                   // 2. if(bigger) bigger >= child_min
                   smallerChildSize + 1 >= childSizeMin;
        }
    };


    class SplitPolicyFactory {
    protected:
        int level;

        explicit SplitPolicyFactory(int level) : level(level) {}

        [[nodiscard]] int maxOn(int layer) const {
            return power(level, layer) - 1;
        }

        [[nodiscard]] int minOn(int layer) const {
            int lb = (level - 1) >> 1;
            return power(lb + 1, layer) - 1;
        }

        static int power(int a, int b) {
            int res = 1;
            for (int i = 0; i < b; i++) res *= a;
            return res;
        }

    public:


        /**
         * 1. 让size尽可能大, 这样layer就会尽可能小 <br>
         * 2. size=level-1, 取得理论layer最小值 <br>
         * 3. size--, 这样layer就会逐渐丰满 <br>
         * @param sourceSize
         * @param layer
         * @return
         */
        virtual SplitPolicy create(int sourceSize, int layer) = 0;

        virtual SplitPolicyFactory *childFactory() = 0;

        [[nodiscard]] int getLevel() const {
            return level;
        }

        virtual ~SplitPolicyFactory() = default;
    };


    class NodeSplitPolicyFactory : public SplitPolicyFactory {
    public:
        explicit NodeSplitPolicyFactory(int level) : SplitPolicyFactory(level) {}

        [[nodiscard]] int getLayer(int sourceSize, int layer) const {
            return layer;
        }

        // TODO
        // 要求layer, 就一定是layer!
        // layer->level
        // policy.smaller*policy.smaller.count+
        // (policy.smaller+1)*(sourceSize-policy.smaller.count-policy.node)+
        // policy.node
        SplitPolicy create(int sourceSize, int layer) override {
            int nodeLowerBound = (level - 1) >> 1;
            if (sourceSize < nodeLowerBound) {
                return {};
            }
            if (sourceSize < level - 1) {// leaf
                return {1, sourceSize, 0, 0};
            }
            layer = getLayer(sourceSize, layer);
            int minOnLayer = minOn(layer);
            int maxOnLayer = maxOn(layer);
            SplitPolicy policy;
            for (int nodeSize = level - 1; nodeSize >= nodeLowerBound; --nodeSize) {
                int sourceForChild = sourceSize - nodeSize;
                int childrenCount = nodeSize + 1;
                if (maxOnLayer * childrenCount > sourceForChild) {
                    break;
                }
                int smallerChildSize = sourceForChild / childrenCount;
                int smallerChildrenCount = (smallerChildSize + 1) * childrenCount - sourceForChild;
                SplitPolicy challenger(layer, nodeSize, smallerChildSize, smallerChildrenCount);
                if (challenger.ok(minOnLayer)) {
                    policy.update(challenger);
                }
            }
            return policy;
        }

        SplitPolicyFactory *childFactory() override {
            return this;
        }
    };

    class RootSplitPolicyFactory : public SplitPolicyFactory {
    private:
        NodeSplitPolicyFactory *_childFactory = nullptr;
    public:
        explicit RootSplitPolicyFactory(int level) :
                SplitPolicyFactory(level) {}

        [[nodiscard]] int getLayer(int sourceSize, int layer) const {
            // child layer
            int sourceForChild = sourceSize - level + 1;
            int childrenCount = level;
            for (layer = 1; maxOn(layer) * childrenCount <= sourceForChild; layer++);
            return layer + 1;
        }

        [[nodiscard]] SplitPolicy create(int sourceSize, int layer) override {
            int nodeLowerBound = 1;
            if (sourceSize < nodeLowerBound) {
                return {};
            }
            if (sourceSize < level - 1) {// leaf
                return {1, sourceSize, 0, 0};
            }
            layer = getLayer(sourceSize, layer);
            int minOnLayer = minOn(layer);
            int maxOnLayer = maxOn(layer);
            SplitPolicy policy;
            for (int nodeSize = level - 1; nodeSize >= nodeLowerBound; --nodeSize) {
                int sourceForChild = sourceSize - nodeSize;
                int childrenCount = nodeSize + 1;
                if (maxOnLayer * childrenCount > sourceForChild) {
                    break;
                }
                int smallerChildSize = sourceForChild / childrenCount;
                int smallerChildrenCount = (smallerChildSize + 1) * childrenCount - sourceForChild;
                SplitPolicy challenger(layer, nodeSize, smallerChildSize, smallerChildrenCount);
                if (challenger.ok(minOnLayer)) {
                    policy.update(challenger);
                }
            }
            return policy;
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
}

template<typename T, typename Cmp>
class BTree<T, Cmp>::BulkSource {
    typename std::vector<T>::const_iterator begin;
    typename std::vector<T>::const_iterator end;
public:
    explicit BulkSource(
            const typename std::vector<T>::const_iterator &begin,
            const typename std::vector<T>::const_iterator &end) :
            begin(begin), end(end) {}

    [[nodiscard]] BTreeNodeReference<T, Cmp> build(int btreeLevel) const {// 判断, 调度
        RootSplitPolicyFactory factory(btreeLevel);
        if (sourceSize() == 0) {
            // empty, then return
            return BTreeNodeReference<T, Cmp>(new BTreeNode<T, Cmp>(factory.getLevel()));
        }
        BTreeNodeReference<T, Cmp> node = build(&factory, 0); // 这个layer是随便的, 因为对于root其不生效
        return node;
    }

private:

    [[nodiscard]] int sourceSize() const {
        return end - begin;
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

    // TODO 解开递归
    [[nodiscard]] BTreeNodeReference<T, Cmp> build(SplitPolicyFactory *factory, int layer) const {
        BTreeNodeReference<T, Cmp> node(new BTreeNode<T, Cmp>(factory->getLevel()));
        SplitPolicy policy = factory->create(sourceSize(), layer);
        if (policy.notFound()) {
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
        SplitPolicyFactory *childFactory = factory->childFactory();
        typename std::vector<T>::const_iterator childBegin = begin;
        for (int i = 0; i < policy.nodeSize; ++i) {
            int limit = policy.smallerChildSize + (i >= policy.smallerChildrenCount ? 1 /*bigger*/: 0);
            auto childEnd = childBegin + limit;
            BTreeNodeReference<T, Cmp> child = BulkSource(childBegin, childEnd).build(childFactory, childLayer);
            node->setChild(i, child);
            node->setData(i, BTreeData<T>(*(childEnd)));
            // 1 for parent
            childBegin = childEnd + 1;
        }
        BTreeNodeReference<T, Cmp> child = BulkSource(childBegin, end).build(childFactory, childLayer);
        node->setChild(policy.nodeSize, child);
        return node;
    }

#pragma clang diagnostic pop
};

template<typename T, typename Cmp>
BTree<T, Cmp> &BTree<T, Cmp>::bulk(const BulkSource &source) {
    // 1. 用count算出能建造出几层的树(不考虑是否需要分裂)->N层及以上, N+1层以下
    // 2. 构建N-1层(满), 需要元素X_1个, count==K*X+(K-1)+M
    //      特别的, 构建N-2层满, 需要元素X_2个
    // 3. 如果M==0, 构建K个N-1层(满), root节点的元素是K-1个, 由于条件一, K<level-1
    // 4. 如果M>0, 构建K+1个N-1层, 但不满, 每一个的个数是count_1 = (count-k)/(k+1)
    //      由条件1,2得X_2<count_1<X_1
    // 故可以递归得构建, 步骤一二的判断过程直接执行, 步骤三四递归构架树, 将source划分成一块一块的, 然后构建
    clear();
    root.release();
    root = source.build(level);
    return *this;
}

#include <algorithm>

bool bulkDemo() {
    std::vector<int> src(111);
    for (int i = 0; i < 111; ++i) {
        src[i] = i;
    }
    IntBTree bTree(5);
    bTree.bulk(IntBTree::BulkSource(src.begin(), src.end()));
    return true;
}

#ifdef BULK
bool bulkDemoSucceed = bulkDemo();
#endif