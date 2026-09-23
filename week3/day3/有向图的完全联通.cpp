// 有向图的完全联通（105）

// 邻接表，深搜
#include <iostream>
#include <vector>
#include <list>
using namespace std;

void dfs(const vector<list<int>>& graph, int key, vector<bool>& visited) {
    if (visited[key]) {
        return;
    }
    visited[key] = true;
    list<int> keys = graph[key];
    for (int key : keys) {
        // 深度优先搜索遍历
        dfs(graph, key, visited);
    }
}

int main() {
    int n, m, s, t;
    cin >> n >> m;

    // 节点编号从1到n，所以申请 n+1 这么大的数组
    vector<list<int>> graph(n + 1); // 邻接表
    while (m--) {
        cin >> s >> t;
        // 使用邻接表 ，表示 s -> t 是相连的
        graph[s].push_back(t);
    }
    vector<bool> visited(n + 1, false);
    dfs(graph, 1, visited);
    //检查是否都访问到了
    for (int i = 1; i <= n; i++) {
        if (visited[i] == false) {
            cout << -1 << endl;
            return 0;
        }
    }
    cout << 1 << endl;
}
