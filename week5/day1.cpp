// 缺失的第一个正数（41）
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n; i++){
            // 条件：是合法1~n的数，而且它还没在正确位置
            while(nums[i] > 0 && nums[i] <= n && nums[nums[i]-1] != nums[i]){
                swap(nums[nums[i]-1], nums[i]);
            }
        }
        // 找第一个不对的位置
        for(int i = 0; i < n; i++){
            if(nums[i] != i+1){
                return i+1;
            }
        }
        // 1~n全齐了
        return n+1;
    }
};


// 矩阵置零（73）
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        bool firstRow = false, firstCol = false;

        // Step 1: 检查第一行和第一列是否需要置零
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) firstCol = true;
        }
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) firstRow = true;
        }

        // Step 2: 使用第一行和第一列记录需要置零的行和列
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // Step 3: 遍历矩阵，根据第一行和第一列置零
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // Step 4: 处理第一行和第一列
        if (firstRow) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }
        if (firstCol) {
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};


// 螺旋矩阵（54）
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) 
            return {};  // 返回空数组

        vector<int> res;
        int top = 0, bottom = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;

        while (top <= bottom && left <= right) {
            // 从左到右
            for (int i = left; i <= right; ++i) {
                res.push_back(matrix[top][i]);
            }
            ++top;  // 上边界向下移动

            // 从上到下
            for (int i = top; i <= bottom; ++i) {
                res.push_back(matrix[i][right]);
            }
            --right;  // 右边界向左移动

            // 从右到左（确保仍在有效范围内）
            if (top <= bottom) {
                for (int i = right; i >= left; --i) {
                    res.push_back(matrix[bottom][i]);
                }
                --bottom;  // 下边界向上移动
            }

            // 从下到上（确保仍在有效范围内）
            if (left <= right) {
                for (int i = bottom; i >= top; --i) {
                    res.push_back(matrix[i][left]);
                }
                ++left;  // 左边界向右移动
            }
        }

        return res;
    }
};


// 旋转图像（48）
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size(); // 矩阵的大小
        // 遍历每一层，从最外层到最内层
        for (int x = 0; x < n / 2; ++x) {
            // 遍历当前层的每个元素
            for (int i = 0; i < n - 2 * x - 1; ++i) { // 固定第 x 层循环
                // 保存 4 点的元素对应关系
                int tmp1 = matrix[x][x + i];
                matrix[x][x + i] = matrix[n - 1 - x - i][x];
                matrix[n - 1 - x - i][x] = matrix[n - 1 - x][n - 1 - x - i];
                matrix[n - 1 - x][n - 1 - x - i] = matrix[x + i][n - 1 - x];
                matrix[x + i][n - 1 - x] = tmp1;
            }
        }
    }
};


// 搜索二维矩阵2（240）
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if(m == 0) return false;
        int n = matrix[0].size();

        int i = 0;         // 行：从第一行开始
        int j = n - 1;     // 列：从最后一列（右上角）

        while(i < m && j >= 0){
            if(matrix[i][j] == target){
                return true;
            }else if(matrix[i][j] > target){
                j--;  // 太大，舍弃当前列，左移
            }else{
                i++;  // 太小，舍弃当前行，下移
            }
        }
        return false; // 越界没找到
    }
};


// 岛屿数量（200）
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size();
        int cnt = 0;
        // 方向数组：上下左右
        int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(grid[i][j] == '1'){
                    cnt++;
                    queue<pair<int,int>> q;
                    q.push({i,j});
                    grid[i][j] = '0';

                    while(!q.empty()){
                        auto [x,y] = q.front(); q.pop();
                        for(auto& d : dirs){
                            int nx = x + d[0];
                            int ny = y + d[1];
                            if(nx>=0&&nx<m&&ny>=0&&ny<n&&grid[nx][ny]=='1'){
                                grid[nx][ny]='0';
                                q.push({nx,ny});
                            }
                        }
                    }
                }
            }
        }
        return cnt;
    }
};


// 腐烂的橘子（994）
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int,int>> q;
        int fresh = 0;
        int time = 0;
        int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

        // 第一步：初始化队列 + 统计新鲜橘子
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 2){
                    q.push({i,j});
                }else if(grid[i][j] == 1){
                    fresh++;
                }
            }
        }

        // 没有新鲜橘子，直接0
        if(fresh == 0) return 0;

        // 多源层序BFS
        while(!q.empty() && fresh > 0){
            int sz = q.size(); // 当前层大小（这一分钟要扩散的所有烂橘子）
            for(int k = 0; k < sz; k++){
                auto [x,y] = q.front(); q.pop();
                for(auto& d : dirs){
                    int nx = x + d[0];
                    int ny = y + d[1];
                    // 越界判断 + 是新鲜橘子
                    if(nx>=0 && nx<m && ny>=0 && ny<n && grid[nx][ny]==1){
                        grid[nx][ny] = 2;
                        fresh--;
                        q.push({nx,ny});
                    }
                }
            }
            time++; // 一层扩散完，时间+1
        }

        return fresh > 0 ? -1 : time;
    }
};


// 实现Trie树（208）
class Trie {
private:
    struct TrieNode {
        TrieNode* children[26];
        bool isEnd;
        TrieNode() {
            for(int i = 0; i < 26; i++) children[i] = nullptr;
            isEnd = false;
        }
    };
    TrieNode* root; // 虚拟根节点（不存字符）

public:
    Trie() {
        root = new TrieNode();
    }

    // 插入
    void insert(string word) {
        TrieNode* p = root;
        for(char c : word) {
            int idx = c - 'a';
            if(!p->children[idx]) {
                p->children[idx] = new TrieNode();
            }
            p = p->children[idx];
        }
        p->isEnd = true; // 单词末尾标记
    }

    // 搜索完整单词（必须是结尾）
    bool search(string word) {
        TrieNode* p = root;
        for(char c : word) {
            int idx = c - 'a';
            if(!p->children[idx]) return false;
            p = p->children[idx];
        }
        return p->isEnd; // 要看是不是单词结束！
    }

    // 只检查前缀，不用是单词结尾
    bool startsWith(string prefix) {
        TrieNode* p = root;
        for(char c : prefix) {
            int idx = c - 'a';
            if(!p->children[idx]) return false;
            p = p->children[idx];
        }
        return true; // 走到头就够了，不用isEnd
    }
};
