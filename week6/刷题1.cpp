// 1456
class Solution {
public:
    int maxVowels(string s, int k) {
        unordered_set<char> vow = {'a','e','i','o','u'};
        int cnt = 0;
        // 第一个窗口
        for(int i = 0; i < k; i++){
            if(vow.count(s[i])) cnt++;
        }
        int ans = cnt;
        // 滑动
        for(int i = k; i < s.size(); i++){
            if(vow.count(s[i-k])) cnt--; // 左边出去
            if(vow.count(s[i])) cnt++;   // 右边进来
            ans = max(ans, cnt);
        }
        return ans;
    }
};


// 2841
class Solution {
public:
    long long maxSum(vector<int>& nums, int m, int k) {
        unordered_map<int,int> mp;
        long long sum = 0;
        long long ans = 0;
        int n = nums.size();

        // 初始化第一个窗口
        for(int i = 0; i < k; i++){
            sum += nums[i];
            mp[nums[i]]++;
        }
        int distinct = mp.size();
        if(distinct >= m){
            ans = sum;
        }

        // 滑动窗口
        for(int i = k; i < n; i++){
            // 左边出去 nums[i-k]
            int out = nums[i-k];
            sum -= out;
            mp[out]--;
            if(mp[out] == 0){
                mp.erase(out);
                distinct--;
            }
            // 右边进来 nums[i]
            int in = nums[i];
            sum += in;
            if(mp[in] == 0){
                distinct++;
            }
            mp[in]++;

            if(distinct >= m){
                ans = max(ans, sum);
            }
        }
        return ans;
    }
};
