// 和有限的最长子序列（2389）
class Solution {
public:
    vector<int> answerQueries(vector<int>& nums, vector<int>& queries) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<int> pre(n + 1, 0);
        for(int i = 0; i < n; i++){
            pre[i+1] = pre[i] + nums[i];
        }
        vector<int> ans;
        for(int q : queries){
            // 找第一个 > q 的位置，下标就是答案
            int pos = upper_bound(pre.begin(), pre.end(), q) - pre.begin();
            ans.push_back(pos - 1);
        }
        return ans;
    }
};


// 比较字符串最小字母出现频次（1170）
class Solution {
public:
    int f(string &s){
        int cnt[26] = {0};
        for(char c : s) cnt[c-'a']++;
        for(int i = 0; i < 26; i++){
            if(cnt[i] > 0) return cnt[i];
        }
        return 0;
    }
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        vector<int> fw;
        for(auto &w : words){
            fw.push_back(f(w));
        }
        sort(fw.begin(), fw.end());
        vector<int> ans;
        for(auto &q : queries){
            int fq = f(q);
            // 第一个大于 fq 的位置
            int pos = upper_bound(fw.begin(), fw.end(), fq) - fw.begin();
            ans.push_back(fw.size() - pos);
        }
        return ans;
    }
};


// 咒语和药水的成功对数（2300）
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());
        int m = potions.size();
        vector<int> ans;
        for(long long s : spells){
            // s * p >= success  => p >= (success + s - 1)/s 向上取整
            long long target = (success + s - 1) / s;
            int pos = lower_bound(potions.begin(), potions.end(), target) - potions.begin();
            ans.push_back(m - pos);
        }
        return ans;
    }
};


// 找到 K 个最接近的元素（658）
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int l = 0, r = arr.size() - k;
        while(l < r){
            int mid = (l + r) / 2;
            // 比较 arr[mid] 和 arr[mid + k] 谁离 x更远
            if(x - arr[mid] > arr[mid + k] - x){
                l = mid + 1;
            }else{
                r = mid;
            }
        }
        return vector<int>(arr.begin() + l, arr.begin() + l + k);
    }
};


// 统计公平数对的数目（2563）
class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        sort(nums.begin(), nums.end());
        long long ans = 0;
        int n = nums.size();
        for(int j = 0; j < n; j++){
            // nums[i] >= lower - nums[j]
            int L = lower - nums[j];
            // nums[i] <= upper - nums[j]
            int R = upper - nums[j];
            // i < j，查找范围 [0, j-1]
            auto left_it = lower_bound(nums.begin(), nums.begin()+j, L);
            auto right_it = upper_bound(nums.begin(), nums.begin()+j, R);
            ans += right_it - left_it;
        }
        return ans;
    }
};
