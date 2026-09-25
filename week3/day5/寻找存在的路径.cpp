#include <iostream>
#include <vector>
using namespace std;

int n; // 节点数量
vector<int> father = vector<int> (101, 0); // 按照节点大小定义数组大小

// 并查集初始化
void init() {
    for (int i = 1; i <= n; i++)  father[i] = i;
}
// 并查集里寻根的过程
int find(int u) {
    return u == father[u] ? u : father[u] = find(father[u]);
}

// 判断 u 和 v是否找到同一个根
bool isSame(int u, int v) {
    u = find(u);
    v = find(v);
    return u == v;
}

// 将v->u 这条边加入并查集
void join(int u, int v) {
    u = find(u); // 寻找u的根
    v = find(v); // 寻找v的根
    if (u == v) return ; // 如果发现根相同，则说明在一个集合，不用两个节点相连直接返回
    father[v] = u;
}

int main() {
    int m, s, t, source, destination;
    cin >> n >> m;
    init();
    while (m--) {
        cin >> s >> t;
        join(s, t);
    }
    cin >> source >> destination;
    if (isSame(source, destination)) cout << 1 << endl;
    else cout << 0 << endl;
}
