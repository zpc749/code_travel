// 多路查找树（B树）

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct BTreeNode {
    vector<int> keys;              // 关键字
    vector<BTreeNode*> children;   // 子节点
    bool leaf;                     // 是否叶子
    BTreeNode(bool leaf) : leaf(leaf) {}
};

class BTree {
    BTreeNode* root;
    int t;                         // 最小度数

public:
    BTree(int _t) : root(nullptr), t(_t) {}
    ~BTree() { destroy(root); }

    void traverse() { traverse(root); cout << endl; }
    BTreeNode* search(int k) { return search(root, k); }
    void insert(int k);
    void remove(int k);

private:
    void destroy(BTreeNode* node) {
        if (!node) return;
        if (!node->leaf)
            for (auto child : node->children) destroy(child);
        delete node;
    }

    BTreeNode* search(BTreeNode* node, int k) {
        if (!node) return nullptr;
        int i = 0;
        while (i < node->keys.size() && k > node->keys[i]) i++;
        if (i < node->keys.size() && node->keys[i] == k) return node;
        if (node->leaf) return nullptr;
        return search(node->children[i], k);
    }

    void traverse(BTreeNode* node) {
        if (!node) return;
        int i;
        for (i = 0; i < node->keys.size(); i++) {
            if (!node->leaf) traverse(node->children[i]);
            cout << node->keys[i] << " ";
        }
        if (!node->leaf) traverse(node->children[i]);
    }

    // 分裂 parent 的第 i 个子节点
    void splitChild(BTreeNode* parent, int i) {
        BTreeNode* y = parent->children[i];
        BTreeNode* z = new BTreeNode(y->leaf);
        int mid = t - 1;

        z->keys.assign(y->keys.begin() + t, y->keys.end());
        y->keys.resize(mid);

        if (!y->leaf) {
            z->children.assign(y->children.begin() + t, y->children.end());
            y->children.resize(t);
        }

        parent->keys.insert(parent->keys.begin() + i, y->keys[mid]);
        parent->children.insert(parent->children.begin() + i + 1, z);
    }

    void insertNonFull(BTreeNode* node, int k) {
        int i = node->keys.size() - 1;
        if (node->leaf) {
            node->keys.push_back(0);
            while (i >= 0 && node->keys[i] > k) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = k;
        } else {
            while (i >= 0 && node->keys[i] > k) i--;
            i++;
            if (node->children[i]->keys.size() == 2 * t - 1) {
                splitChild(node, i);
                if (node->keys[i] < k) i++;
            }
            insertNonFull(node->children[i], k);
        }
    }

    void insert(int k) {
        if (!root) {
            root = new BTreeNode(true);
            root->keys.push_back(k);
            return;
        }
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(false);
            s->children.push_back(root);
            splitChild(s, 0);
            insertNonFull(s, k);
            root = s;
        } else {
            insertNonFull(root, k);
        }
    }

    // 找前驱：左子树最大关键字
    int getPred(BTreeNode* node, int idx) {
        BTreeNode* cur = node->children[idx];
        while (!cur->leaf) cur = cur->children.back();
        return cur->keys.back();
    }

    // 找后继：右子树最小关键字
    int getSucc(BTreeNode* node, int idx) {
        BTreeNode* cur = node->children[idx + 1];
        while (!cur->leaf) cur = cur->children[0];
        return cur->keys[0];
    }

    // 从左兄弟借一个关键字
    void borrowFromPrev(BTreeNode* node, int idx) {
        BTreeNode* child = node->children[idx];
        BTreeNode* sibling = node->children[idx - 1];

        child->keys.insert(child->keys.begin(), node->keys[idx - 1]);
        if (!child->leaf) {
            child->children.insert(child->children.begin(), sibling->children.back());
            sibling->children.pop_back();
        }
        node->keys[idx - 1] = sibling->keys.back();
        sibling->keys.pop_back();
    }

    // 从右兄弟借一个关键字
    void borrowFromNext(BTreeNode* node, int idx) {
        BTreeNode* child = node->children[idx];
        BTreeNode* sibling = node->children[idx + 1];

        child->keys.push_back(node->keys[idx]);
        if (!child->leaf) {
            child->children.push_back(sibling->children[0]);
            sibling->children.erase(sibling->children.begin());
        }
        node->keys[idx] = sibling->keys[0];
        sibling->keys.erase(sibling->keys.begin());
    }

    // 合并 node->children[idx] 和 node->children[idx+1]
    void merge(BTreeNode* node, int idx) {
        BTreeNode* child = node->children[idx];
        BTreeNode* sibling = node->children[idx + 1];

        child->keys.push_back(node->keys[idx]);
        child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());

        if (!child->leaf) {
            child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
        }

        node->keys.erase(node->keys.begin() + idx);
        node->children.erase(node->children.begin() + idx + 1);
        delete sibling;
    }

    // 确保 node->children[idx] 至少有 t 个关键字
    void fill(BTreeNode* node, int idx) {
        if (idx != 0 && node->children[idx - 1]->keys.size() >= t)
            borrowFromPrev(node, idx);
        else if (idx != node->keys.size() && node->children[idx + 1]->keys.size() >= t)
            borrowFromNext(node, idx);
        else {
            if (idx != node->keys.size())
                merge(node, idx);
            else
                merge(node, idx - 1);
        }
    }

    void remove(BTreeNode* node, int k) {
        int idx = 0;
        while (idx < node->keys.size() && node->keys[idx] < k) idx++;

        if (idx < node->keys.size() && node->keys[idx] == k) {
            if (node->leaf) {
                node->keys.erase(node->keys.begin() + idx);
            } else {
                if (node->children[idx]->keys.size() >= t) {
                    int pred = getPred(node, idx);
                    node->keys[idx] = pred;
                    remove(node->children[idx], pred);
                } else if (node->children[idx + 1]->keys.size() >= t) {
                    int succ = getSucc(node, idx);
                    node->keys[idx] = succ;
                    remove(node->children[idx + 1], succ);
                } else {
                    merge(node, idx);
                    remove(node->children[idx], k);
                }
            }
        } else {
            if (node->leaf) {
                cout << "Key " << k << " not found.\n";
                return;
            }
            bool flag = (idx == node->keys.size());
            if (node->children[idx]->keys.size() < t)
                fill(node, idx);
            if (flag && idx > node->keys.size())
                remove(node->children[idx - 1], k);
            else
                remove(node->children[idx], k);
        }
    }

public:
    void remove(int k) {
        if (!root) return;
        remove(root, k);
        if (root->keys.empty() && !root->leaf) {
            BTreeNode* old = root;
            root = root->children[0];
            delete old;
        }
    }
};

int main() {
    BTree t(3); // 最小度数 3，每个节点最多 5 个关键字，最少 2 个

    vector<int> keys = {10, 20, 5, 6, 12, 30, 7, 17, 3, 25, 18, 2, 1, 15, 28};
    for (int k : keys) {
        t.insert(k);
        cout << "Insert " << k << ": ";
        t.traverse();
    }

    cout << "\nAfter all insertions: ";
    t.traverse();

    vector<int> del = {6, 12, 20, 10, 3, 1};
    for (int k : del) {
        t.remove(k);
        cout << "Delete " << k << ": ";
        t.traverse();
    }

    return 0;
}
