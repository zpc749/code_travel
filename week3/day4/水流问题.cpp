#include <iostream>
#include <vector>
using namespace std;
int n, m;
int dir[4][2] = {-1, 0, 0, -1, 1, 0, 0, 1};

// 从 x，y 出发 把可以走的地方都标记上
void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y) {
    if (visited[x][y]) return;

    visited[x][y] = true;

    for (int i = 0; i < 4; i++) {
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if (nextx < 0 || nextx >= n || nexty < 0 || nexty >= m) continue;
        if (grid[x][y] < grid[nextx][nexty]) continue; // 高度不合适

        dfs (grid, visited, nextx, nexty);
    }
    return;
}
bool isResult(vector<vector<int>>& grid, int x, int y) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    // 深搜，将x,y出发 能到的节点都标记上。
    dfs(grid, visited, x, y);
    bool isFirst = false;
    bool isSecond = false;

    // 以下就是判断x，y出发，是否到达第一组边界和第二组边界
    // 第一边界的上边
    for (int j = 0; j < m; j++) {
        if (visited[0][j]) {
            isFirst = true;
            break;
        }
    }
    // 第一边界的左边
    for (int i = 0; i < n; i++) {
        if (visited[i][0]) {
            isFirst = true;
            break;
        }
    }
    // 第二边界下边
    for (int j = 0; j < m; j++) {
        if (visited[n - 1][j]) {
            isSecond = true;
            break;
        }
    }
    // 第二边界右边
    for (int i = 0; i < n; i++) {
        if (visited[i][m - 1]) {
            isSecond = true;
            break;
        }
    }
    if (isFirst && isSecond) return true;
    return false;
}


int main() {
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    // 遍历每一个点，看是否能同时到达第一组边界和第二组边界
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (isResult(grid, i, j)) {
                cout << i << " " << j << endl;
            }
        }
    }
}
