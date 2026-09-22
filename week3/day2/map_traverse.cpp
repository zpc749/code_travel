// 图的遍历

// 1.深度优先搜索（DFS）
// 递归版（邻接表）
void dfs(int u, vector<vector<int>>& adj, vector<bool>& vis) {
    vis[u] = true;
    cout << u << " ";
    for (int v : adj[u]) {
        if (!vis[v]) dfs(v, adj, vis);
    }
}

// 处理非连通图
for (int i = 0; i < n; ++i) {
    if (!vis[i]) dfs(i, adj, vis);
}
// 递归版（邻接矩阵）
void dfs(int u, vector<vector<int>>& g, vector<bool>& vis) {
    vis[u] = true;
    cout << u << " ";
    for (int v = 0; v < n; ++v) {
        if (g[u][v] && !vis[v]) dfs(v, g, vis);
    }
}
// 迭代版（邻接表）
void dfsIter(int start, vector<vector<int>>& adj, vector<bool>& vis) {
    stack<int> st;
    st.push(start);
    vis[start] = true;          // 入栈时标记，避免重复入栈
    while (!st.empty()) {
        int u = st.top(); st.pop();
        cout << u << " ";
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                st.push(v);
            }
        }
    }
}


// 2.广度优先搜索（BFS）
// 邻接表
void bfs(int start, vector<vector<int>>& adj, vector<bool>& vis) {
    queue<int> q;
    q.push(start);
    vis[start] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
}

// 处理非连通图
for (int i = 0; i < n; ++i) {
    if (!vis[i]) bfs(i, adj, vis);
}
// 邻接矩阵
void bfs(int start, vector<vector<int>>& g, vector<bool>& vis) {
    queue<int> q;
    q.push(start);
    vis[start] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";
        for (int v = 0; v < n; ++v) {
            if (g[u][v] && !vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
}
