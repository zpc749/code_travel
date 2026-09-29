#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

struct Edge {
    int u, v, w;   // 起点、终点、持续时间
};

int main() {
    int n, m;   // n 个顶点（事件），m 条边（活动）
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n);   // adj[u] = {v, w}
    vector<Edge> edges;                     // 边集
    vector<int> indegree(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        edges.push_back({u, v, w});
        indegree[v]++;
    }

    // ---------- 1. 拓扑排序 + 正向计算 ve ----------
    vector<int> ve(n, 0);           // 最早发生时间，初始为 0
    vector<int> topo;               // 拓扑序列
    queue<int> q;

    for (int i = 0; i < n; ++i)
        if (indegree[i] == 0) q.push(i);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (auto [v, w] : adj[u]) {
            ve[v] = max(ve[v], ve[u] + w);   // 正向取 max
            if (--indegree[v] == 0) q.push(v);
        }
    }

    // 有环检测
    if ((int)topo.size() != n) {
        cout << "图中存在环，无关键路径" << endl;
        return 0;
    }

    // 工程最短完成时间 = 所有事件 ve 的最大值（汇点的 ve）
    int totalTime = 0;
    for (int i = 0; i < n; ++i) totalTime = max(totalTime, ve[i]);
    cout << "工程最短完成时间: " << totalTime << endl;

    // ---------- 2. 反向计算 vl ----------
    vector<int> vl(n, totalTime);   // 初始化为工程总时间
    // 汇点的 vl = ve
    for (int i = 0; i < n; ++i)
        if (ve[i] == totalTime) vl[i] = totalTime;

    // 按逆拓扑序更新
    for (int i = n - 1; i >= 0; --i) {
        int u = topo[i];
        for (auto [v, w] : adj[u]) {
            vl[u] = min(vl[u], vl[v] - w);   // 反向取 min
        }
    }

    // ---------- 3. 计算每条边的 e 和 l，找关键活动 ----------
    cout << "关键活动（关键路径上的边）：" << endl;
    for (auto& e : edges) {
        int early = ve[e.u];              // 最早开始
        int late  = vl[e.v] - e.w;        // 最晚开始
        if (early == late) {
            cout << e.u << " -> " << e.v
                 << "，持续时间 " << e.w
                 << "，最早开始 " << early
                 << "，最晚开始 " << late << endl;
        }
    }

    return 0;
}
