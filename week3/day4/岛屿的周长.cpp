#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    int sum = 0;    // 陆地数量
    int cover = 0;  // 相邻数量
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                sum++; // 统计总的陆地数量
                // 统计上边相邻陆地
                if(i - 1 >= 0 && grid[i - 1][j] == 1) cover++;
                // 统计左边相邻陆地
                if(j - 1 >= 0 && grid[i][j - 1] == 1) cover++;
                // 为什么没统计下边和右边？ 因为避免重复计算
            }
        }
    }

    cout << sum * 4 - cover * 2 << endl;

}



// 简单版
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    int direction[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};
    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                for (int k = 0; k < 4; k++) {       // 上下左右四个方向
                    int x = i + direction[k][0];
                    int y = j + direction[k][1];    // 计算周边坐标x,y
                    if (x < 0                       // x在边界上
                            || x >= grid.size()     // x在边界上
                            || y < 0                // y在边界上
                            || y >= grid[0].size()  // y在边界上
                            || grid[x][y] == 0) {   // x,y位置是水域
                        result++;
                    }
                }
            }
        }
    }
    cout << result << endl;

}
