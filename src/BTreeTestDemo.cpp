#define DEBUG

#include "tree/BTree.h"

using namespace std;

class ShowUtil {
public:
    template<typename T>
    static string show(const T &t) {
        stringstream ss;
        ss << t << flush;
        return ss.str();
    }
};

using IntBTreeTrace = BTreeTrace<int, Greater<int>>;

int btreeDemo() {
    cout << "hello world" << endl;
    BTree<int, Greater<int>>
            bTree(4);
    bTree.insert(1);
    bTree.insert(5);
    bTree.insert(7);
    bTree.insert(4);
    bTree.insert(16);
    bTree.insert(35);
    bTree.insert(24);
    bTree.insert(42);
    bTree.insert(21);
    bTree.insert(17);
    bTree.insert(18);
    bTree.showBTree();
    const IntBTreeTrace &entry = bTree.search(5);
    return 0;
}


int BTreeTestDemoCode = btreeDemo();