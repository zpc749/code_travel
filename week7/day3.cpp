// 翻转字符串（344）
class Solution {
public:
    void reverseString(vector<char>& s) {
        int l = 0, r = s.size() - 1;
        while(l < r){
            swap(s[l], s[r]);
            l++;
            r--;
        }
    }
};


// 仅仅翻转字母（917）
class Solution {
public:
    string reverseOnlyLetters(string s) {
        int l = 0, r = s.size()-1;
        while(l < r){
            // 左指针不是字母，右移
            while(l < r && !isalpha(s[l])) l++;
            // 右指针不是字母，左移
            while(l < r && !isalpha(s[r])) r--;
            swap(s[l], s[r]);
            l++; r--;
        }
        return s;
    }
};

// 翻转字符串2（541）
class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.size();
        for(int i = 0; i < n; i += 2*k){
            int l = i;
            int r = min(i + k - 1, n - 1);
            // 相向双指针翻转 [l, r]
            while(l < r){
                swap(s[l], s[r]);
                l++; r--;
            }
        }
        return s;
    }
};

// 翻转字符串中的单词（151）
class Solution {
public:
    string reverseWords(string s) {
        // 1. 去除多余空格
        int slow = 0;
        for(int fast = 0; fast < s.size(); fast++){
            if(s[fast] != ' '){
                if(slow != 0) s[slow++] = ' ';
                while(fast < s.size() && s[fast] != ' '){
                    s[slow++] = s[fast++];
                }
            }
        }
        s.resize(slow);
        // 2. 整体反转整个字符串
        reverse(s.begin(), s.end());
        // 3. 逐个单词内部反转
        int l = 0;
        for(int r = 0; r <= s.size(); r++){
            if(r == s.size() || s[r] == ' '){
                reverse(s.begin()+l, s.begin()+r);
                l = r + 1;
            }
        }
        return s;
    }
};
