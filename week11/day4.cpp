// 怪物猎人 (2021校赛最后一题)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1005;
const ll INF = 1e18;

vector<int> g[MAXN];
ll hp[MAXN];
// dp[u][k][0] u子树用k魔法，u不魔法杀；dp[u][k][1] u魔法杀
ll dp[MAXN][MAXN][2];
int sz[MAXN];

void dfs(int u) {
    sz[u] = 1;
    // 初始化
    for(int i=0;i<MAXN;i++) dp[u][i][0]=dp[u][i][1]=INF;
    dp[u][0][0] = hp[u];
    dp[u][1][1] = 0;

    for(int v: g[u]) {
        dfs(v);
        // 临时数组保存合并前u的值，防止覆盖
        ll tmp[MAXN][2];
        for(int i=0;i<MAXN;i++) tmp[i][0]=tmp[i][1]=INF;
        // 背包合并：枚举u原来用a次魔法，子树v用b次魔法
        for(int a=0;a<=sz[u];a++) {
            if(dp[u][a][0]==INF && dp[u][a][1]==INF) continue;
            for(int b=0;b<=sz[v];b++) {
                if(dp[v][b][0]==INF && dp[v][b][1]==INF) continue;
                // ========= u 当前状态是 0：u不魔法杀 =========
                if(dp[u][a][0] != INF) {
                    // v不魔法杀：要额外加上 hp[v]
                    if(dp[v][b][0] != INF)
                        tmp[a+b][0] = min(tmp[a+b][0], dp[u][a][0] + dp[v][b][0] + hp[v]);
                    // v魔法杀，不加hp[v]
                    if(dp[v][b][1] != INF)
                        tmp[a+b][0] = min(tmp[a+b][0], dp[u][a][0] + dp[v][b][1]);
                }
                // ========= u 当前状态是 1：u魔法杀 =========
                if(dp[u][a][1] != INF) {
                    // u魔法死掉，不管v是魔法还是普通杀，v的hp不会加到u的代价！！！
                    if(dp[v][b][0] != INF)
                        tmp[a+b][1] = min(tmp[a+b][1], dp[u][a][1] + dp[v][b][0]);
                    if(dp[v][b][1] != INF)
                        tmp[a+b][1] = min(tmp[a+b][1], dp[u][a][1] + dp[v][b][1]);
                }
            }
        }
        // 更新dp[u]，更新子树大小
        for(int i=0;i<MAXN;i++) {
            dp[u][i][0] = tmp[i][0];
            dp[u][i][1] = tmp[i][1];
        }
        sz[u] += sz[v];
    }
}

int main() {
    ios::sync_with_stdio(false);cin.tie(0);
    int T; cin>>T;
    while(T--) {
        int n; cin>>n;
        for(int i=1;i<=n;i++) g[i].clear();
        for(int i=2;i<=n;i++) {
            int p; cin>>p;
            g[p].push_back(i);
        }
        for(int i=1;i<=n;i++) cin>>hp[i];
        dfs(1);
        // ans[m] = min(dp[1][m][0], dp[1][m][1])
        for(int m=0;m<=n;m++) {
            ll ans = min(dp[1][m][0], dp[1][m][1]);
            if(m>0) cout << ' ';
            cout << ans;
        }
        cout << '\n';
    }
    return 0;
}
