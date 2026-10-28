// 判断子序列（392）
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0;
        while(i < s.size() && j < t.size()){
            if(s[i] == t[j]) i++;
            j++;
        }
        return i == s.size();
    }
};


// 通过删除字母匹配到字典里最长单词（524）
class Solution {
public:
    bool isSub(string sub, string &s){
        int i=0,j=0;
        while(i<sub.size() && j<s.size()){
            if(sub[i]==s[j]) i++;
            j++;
        }
        return i == sub.size();
    }
    string findLongestWord(string s, vector<string>& dictionary) {
        string ans = "";
        for(auto &w : dictionary){
            if(isSub(w, s)){
                if(w.size() > ans.size() || (w.size()==ans.size() && w < ans)){
                    ans = w;
                }
            }
        }
        return ans;
    }
};


// 追加字符以获得子序列（2486）
class Solution {
public:
    int appendCharacters(string s, string t) {
        int i=0,j=0;
        while(i < s.size() && j < t.size()){
            if(s[i]==t[j]){
                j++;
            }
            i++;
        }
        return t.size() - j;
    }
};


// 一次替换后的子序列（最多替换一个字符）（3983）
class Solution {
private:
    vector<vector<vector<int>>> memo;
    string s, t;
    bool dfs(int i, int j, int cnt) {
        if (i == s.size()) return true;
        if (j == t.size()) return false;
        if (memo[i][j][cnt] != -1) return memo[i][j][cnt];

        bool res;
        if (s[i] == t[j]) {
            res = dfs(i+1, j+1, cnt);
        } else {
            bool skip = dfs(i, j+1, cnt);
            bool change = false;
            if (cnt > 0) change = dfs(i+1, j+1, cnt - 1);
            res = skip || change;
        }
        return memo[i][j][cnt] = res;
    }
public:
    bool isOneEditSubsequence(string s_, string t_) {
        s = s_; t = t_;
        memo.assign(s.size(), vector<vector<int>>(t.size(), vector<int>(2, -1)));
        return dfs(0, 0, 1);
    }
};
