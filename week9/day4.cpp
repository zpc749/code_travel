// 两球之间的磁力（1552）
class Solution {
public:
    bool check(vector<int>& pos, int m, int mid) {
        int cnt = 1;
        int last = pos[0];
        for(int i = 1; i < pos.size(); i++) {
            if(pos[i] - last >= mid) {
                cnt++;
                last = pos[i];
            }
        }
        return cnt >= m;
    }
    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());
        int l = 1, r = position.back() - position[0];
        int ans = 0;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(check(position, m, mid)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};

// 礼盒的最大甜蜜度（2517）
class Solution {
public:
    bool check(vector<int>& a, int k, int mid) {
        int cnt = 1;
        int last = a[0];
        for(int i = 1; i < a.size(); i++) {
            if(a[i] - last >= mid) {
                cnt++;
                last = a[i];
            }
        }
        return cnt >= k;
    }
    int maximumTastiness(vector<int>& price, int k) {
        sort(price.begin(), price.end());
        int l = 0, r = price.back() - price[0];
        int ans = 0;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(check(price, k, mid)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};

// 找出最安全路径（2812）
class Solution {
public:
    const int dx[4] = {-1,1,0,0};
    const int dy[4] = {0,0,-1,1};
    bool check(vector<vector<int>>& dis, int limit) {
        int n = dis.size();
        if(dis[0][0] < limit) return false;
        vector<vector<bool>> vis(n, vector<bool>(n, false));
        queue<pair<int,int>> q;
        q.push({0,0});
        vis[0][0] = true;
        while(!q.empty()) {
            auto [x,y] = q.front(); q.pop();
            if(x == n-1 && y == n-1) return true;
            for(int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if(nx>=0 && nx<n && ny>=0 && ny<n && !vis[nx][ny] && dis[nx][ny] >= limit) {
                    vis[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }
        return false;
    }
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dis(n, vector<int>(n, -1));
        queue<pair<int,int>> q;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1) {
                    dis[i][j]=0;
                    q.push({i,j});
                }
            }
        }
        // 多源BFS预计算每个格子到最近小偷距离
        while(!q.empty()){
            auto [x,y]=q.front();q.pop();
            for(int d=0;d<4;d++){
                int nx=x+dx[d], ny=y+dy[d];
                if(nx>=0&&nx<n&&ny>=0&&ny<n&&dis[nx][ny]==-1){
                    dis[nx][ny]=dis[x][y]+1;
                    q.push({nx,ny});
                }
            }
        }
        int l=0, r=n;
        int ans=0;
        while(l<=r){
            int mid=l+(r-l)/2;
            if(check(dis,mid)){
                ans=mid;
                l=mid+1;
            }else{
                r=mid-1;
            }
        }
        return ans;
    }
};

// 恢复网络路径（3620）
class Solution {
public:
    vector<int> fa;
    int find(int x) {
        if(fa[x] != x) fa[x] = find(fa[x]);
        return fa[x];
    }
    bool check(int n, vector<vector<int>>& edges, int mid) {
        fa.resize(n);
        for(int i=0;i<n;i++) fa[i]=i;
        for(auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if(w >= mid) {
                int fu = find(u), fv = find(v);
                if(fu != fv) fa[fu] = fv;
            }
        }
        return find(0) == find(n-1);
    }
    int maxMinWeight(int n, vector<vector<int>>& edges) {
        int l = 1, r = 1e6;
        int ans = 0;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(check(n, edges, mid)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};

// 最大划分因子（3710）
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

class Solution {
public:
    int manhattan(vector<int>& a, vector<int>& b) {
        return abs(a[0]-b[0]) + abs(a[1]-b[1]);
    }
    // 二分图染色，判断是否二分图
    bool check(int mid, vector<vector<int>>& points) {
        int n = points.size();
        vector<int> color(n, -1); // -1未染色，0/1两种颜色
        for(int i = 0; i < n; i++) {
            if(color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;
                while(!q.empty()) {
                    int u = q.front();
                    q.pop();
                    for(int v = 0; v < n; v++) {
                        if(u == v) continue;
                        int d = manhattan(points[u], points[v]);
                        if(d < mid) { // u和v不能同组，必须异色
                            if(color[v] == -1) {
                                color[v] = color[u] ^ 1;
                                q.push(v);
                            } else if(color[v] == color[u]) {
                                // 冲突！不是二分图，mid不可行
                                return false;
                            }
                        }
                    }
                }
            }
        }
        // 还要保证：两种颜色都存在（两组都非空）
        bool has0 = false, has1 = false;
        for(int c : color) {
            if(c == 0) has0 = true;
            if(c == 1) has1 = true;
        }
        return has0 && has1;
    }

    int maximumPartitionFactor(vector<vector<int>>& points) {
        int l = 0, r = 4000000;
        int ans = 0;
        while(l <= r) {
            int mid = l + (r - l)/2;
            if(check(mid, points)) {
                ans = mid;
                l = mid + 1; // 最大化最小值，尝试更大
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }
};
