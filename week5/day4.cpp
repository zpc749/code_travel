// 今天复习了linux基础命令：文件管理和用户管理

// 全排列（46）
class Solution {
private:
    vector<vector<int>> res;
    vector<int> path;
    void backtrack(vector<int>& nums, vector<bool>& used) {
        // 🔴 终止条件：path长度等于数组长度 → 一个完整排列
        if(path.size() == nums.size()){
            res.push_back(path);
            return;
        }

        // 🟡 没有 startIndex！i永远从0开始！这是和组合题最大区别！
        for(int i = 0; i < nums.size(); i++){
            if(used[i] == true) continue; // 已经选过，跳过

            used[i] = true;   // 标记已使用
            path.push_back(nums[i]);
            backtrack(nums, used);
            path.pop_back();  // 回溯：撤销选择
            used[i] = false;  // 回溯：撤销标记！非常容易忘
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtrack(nums, used);
        return res;
    }
};


// 子集（78）
class Solution {
private:
    vector<vector<int>> res;
    vector<int> path;
    void backtrack(vector<int>& nums, int startIndex) {
        // ✨ 重点区别：**每一层递归，直接收集path！**（不是等到终点才收）
        res.push_back(path);

        for(int i = startIndex; i < nums.size(); i++){
            path.push_back(nums[i]);
            backtrack(nums, i + 1); // i+1：不重复选、只往后走（和77组合一模一样）
            path.pop_back();
        }
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        backtrack(nums, 0);
        return res;
    }
};


// 电话号码的字母组合（17）
class Solution {
public:
    void dfs(const string& s, const vector<string>& list, int cur, string t, vector<string> & ret)
    {
        if (cur == s.length())
        {
            ret.push_back(t);
            return;
        }

        int idx = s[cur] - '0' - 2;
        for (char c: list[idx])
        {
            dfs(s, list, cur+1, t+c, ret);
        }
    }
    vector<string> letterCombinations(string digits) {
        vector<string> ret;
        if (digits.empty()) return ret;

        vector<string> list{"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        dfs(digits, list, 0, "", ret);
        return ret;
    }
};


// 组合总和（39）
class Solution {
private:
    vector<vector<int>> res;
    vector<int> path;

    void backtrack(vector<int>& candidates, int target, int startIndex, int sum) {
        // 🔴 终止条件：和等于target，收集答案
        if(sum == target){
            res.push_back(path);
            return;
        }
        // 🟡 startIndex！关键：从当前位置往后选 → 避免 [2,3] 和 [3,2] 这种重复组合
        // sum + candidates[i] > target 直接break（需要先排序！）→ 剪枝
        for(int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++){
            path.push_back(candidates[i]);
            // ✅ 重点！i 而不是 i+1：可以重复选当前数字！
            backtrack(candidates, target, i, sum + candidates[i]);
            path.pop_back(); // 回溯撤销
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end()); // 排序是为了能剪枝
        backtrack(candidates, target, 0, 0);
        return res;
    }
};


// 括号生成（22）
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string path;
        backtrack(res, path, 0, 0, n);
        return res;
    }

    // left：已用左括号数量；right：已用右括号数量
    void backtrack(vector<string>& res, string& path, int left, int right, int n) {
        // 🔴 终止条件：长度=2n → 全部用完，收集答案
        if(path.size() == 2 * n){
            res.push_back(path);
            return;
        }

        // 🟢 选择1：还能放左括号（左括号没到n个）
        if(left < n){
            path.push_back('(');    // 选
            backtrack(res, path, left+1, right, n); // 递归
            path.pop_back();        // 回溯！撤销选择
        }

        // 🟢 选择2：还能放右括号（右括号数量 < 左括号，才合法！核心剪枝）
        if(right < left){
            path.push_back(')');
            backtrack(res, path, left, right+1, n);
            path.pop_back();
        }
    }
};


// 单词搜索（79）
class Solution {
public:
    // 上下左右四个方向
    int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

    bool backtrack(vector<vector<char>>& board, string& word, int i, int j, int index) {
        // 🔴 终止条件：index走到单词末尾 → 全部匹配成功
        if(index == word.size()) return true;
        // 越界 / 字符不匹配 → 直接返回false
        if(i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[index])
            return false;

        // ✨ 回溯：临时标记当前格子已访问（改成特殊符号，代替used数组）
        char temp = board[i][j];
        board[i][j] = '#';

        bool res = false;
        // 四个方向遍历选择（相当于之前for循环！）
        for(auto& d : dir){
            int ni = i + d[0];
            int nj = j + d[1];
            if(backtrack(board, word, ni, nj, index + 1)){
                res = true;
                break; // 找到就不用搜别的方向
            }
        }

        board[i][j] = temp; // 🟢 回溯！撤销标记（超级关键）
        return res;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        // 每个格子都可以当起点
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(backtrack(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }
};


// 分割回文串（131）
class Solution {
private:
    vector<vector<string>> res;
    vector<string> path;

    // 判断是否回文
    bool isPalindrome(string& s, int l, int r) {
        while(l < r) {
            if(s[l] != s[r]) return false;
            l++; r--;
        }
        return true;
    }

    void backtrack(string& s, int startIndex) {
        // 终止：切到字符串末尾，说明这是一组合法分割
        if(startIndex >= s.size()) {
            res.push_back(path);
            return;
        }
        // i：当前切割的右端点（子串 [startIndex , i]）
        for(int i = startIndex; i < s.size(); i++) {
            if(isPalindrome(s, startIndex, i)) {
                path.push_back(s.substr(startIndex, i - startIndex + 1));
                backtrack(s, i + 1);   // 下一刀从 i+1 开始
                path.pop_back();        // 回溯撤销
            }
            // 不是回文就直接跳过这个i（剪枝：不用往下搜）
        }
    }

public:
    vector<vector<string>> partition(string s) {
        backtrack(s, 0);
        return res;
    }
};


// N皇后（51）
class Solution {
private:
    vector<vector<string>> res;

    // 检查当前(row,col)能不能放皇后
    bool isValid(int row, int col, vector<string>& board, int n) {
        // 检查正上方（同一列）
        for(int i = 0; i < row; i++)
            if(board[i][col] == 'Q') return false;
        // 左上对角线
        for(int i = row-1, j = col-1; i >=0 && j >=0; i--, j--)
            if(board[i][j] == 'Q') return false;
        // 右上对角线
        for(int i = row-1, j = col+1; i >=0 && j < n; i--, j++)
            if(board[i][j] == 'Q') return false;
        return true;
    }

    void backtrack(int row, vector<string>& board, int n) {
        // 终止：行走到n，全部放完，得到一组合法方案
        if(row == n) {
            res.push_back(board);
            return;
        }
        // for循环：枚举「当前行可以放在哪一列」（相当于之前的i）
        for(int col = 0; col < n; col++) {
            if(isValid(row, col, board, n)) {
                board[row][col] = 'Q';      // 做选择：放皇后
                backtrack(row+1, board, n); // 去下一行（row+1 等价 i+1，不回头）
                board[row][col] = '.';      // 回溯撤销：拿走皇后
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        backtrack(0, board, n);
        return res;
    }
};
