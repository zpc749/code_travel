// 爱生气的书店老板（1052）
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int n = customers.size();
        int base = 0;
        // 第一步：先算出基础满意人数
        for(int i = 0; i < n; i++){
            if(grumpy[i] == 0){
                base += customers[i];
            }
        }

        // 第二步：定长滑窗，求窗口内生气顾客的最大和（挽回增益）
        int curGain = 0;
        // 初始化第一个窗口
        for(int i = 0; i < minutes; i++){
            if(grumpy[i] == 1){
                curGain += customers[i];
            }
        }
        int maxGain = curGain;

        // 滑动窗口
        for(int i = minutes; i < n; i++){
            // 左边移出 i-minutes
            if(grumpy[i - minutes] == 1){
                curGain -= customers[i - minutes];
            }
            // 右边进来 i
            if(grumpy[i] == 1){
                curGain += customers[i];
            }
            maxGain = max(maxGain, curGain);
        }
        return base + maxGain;
    }
};


// 找到字符串中所有字母异位词（438）
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        int n = s.size(), m = p.size();
        if(n < m) return res;

        vector<int> pCnt(26,0), sCnt(26,0);
        for(char c : p) pCnt[c-'a']++;
        // 初始化窗口
        for(int i=0;i<m;i++) sCnt[s[i]-'a']++;
        if(sCnt == pCnt) res.push_back(0);

        for(int i=m;i<n;i++){
            // 右边新增字符
            sCnt[s[i]-'a']++;
            // 左边移除字符
            sCnt[s[i-m]-'a']--;
            if(sCnt == pCnt){
                res.push_back(i - m + 1);
            }
        }
        return res;
    }
};


// 字符串的排列（567）
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        if(m > n) return false;

        vector<int> cnt1(26, 0), cnt2(26, 0);
        // 统计s1字符频次
        for(char c : s1) cnt1[c-'a']++;
        // 初始化第一个窗口
        for(int i = 0; i < m; i++) cnt2[s2[i]-'a']++;

        if(cnt1 == cnt2) return true;

        // 滑动定长窗口
        for(int i = m; i < n; i++)
        {
            // 右边加入新字符
            cnt2[s2[i]-'a']++;
            // 左边移除窗口最老字符
            cnt2[s2[i - m]-'a']--;

            if(cnt1 == cnt2) return true;
        }
        return false;
    }
};


// 子串的最大出现次数（1297）
class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        unordered_map<string, int> cntMap;
        vector<int> charCnt(26, 0);
        int diff = 0; // 当前窗口不同字符数量
        int n = s.size();
        int ans = 0;

        // 初始化第一个窗口
        for(int i = 0; i < minSize; i++){
            int idx = s[i] - 'a';
            if(charCnt[idx] == 0) diff++;
            charCnt[idx]++;
        }
        // 判断第一个窗口
        if(diff <= maxLetters){
            string sub = s.substr(0, minSize);
            cntMap[sub]++;
            ans = max(ans, cntMap[sub]);
        }

        // 定长滑动窗口
        for(int i = minSize; i < n; i++){
            // 右边新字符入窗口
            int inIdx = s[i] - 'a';
            if(charCnt[inIdx] == 0) diff++;
            charCnt[inIdx]++;

            // 左边旧字符移出窗口
            int outIdx = s[i - minSize] - 'a';
            charCnt[outIdx]--;
            if(charCnt[outIdx] == 0) diff--;

            // 当前窗口 [i-minSize+1 , i]
            if(diff <= maxLetters){
                string sub = s.substr(i - minSize + 1, minSize);
                cntMap[sub]++;
                ans = max(ans, cntMap[sub]);
            }
        }
        return ans;
    }
};
