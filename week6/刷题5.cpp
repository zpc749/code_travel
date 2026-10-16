// 不同元素和至少为K（3795）
class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int,int> cnt;
        int l = 0;
        int diffSum = 0;
        int ans = INT_MAX;
        int n = nums.size();

        for(int r = 0; r < n; r++){
            int x = nums[r];
            if(cnt[x] == 0){
                diffSum += x;
            }
            cnt[x]++;

            // 满足条件，收缩左边界，找最小窗口
            while(diffSum >= k){
                ans = min(ans, r - l + 1);
                int y = nums[l];
                cnt[y]--;
                if(cnt[y] == 0){
                    diffSum -= y;
                }
                l++;
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};


// 最短且字典序最小的美丽子字符串（2904）
class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int l = 0;
        int cntOne = 0;
        string ans = "";
        int n = s.size();

        for(int r = 0; r < n; r++){
            if(s[r] == '1') cntOne++;

            // 1的数量超过k，收缩左边界
            while(cntOne > k){
                if(s[l] == '1') cntOne--;
                l++;
            }

            // 刚好等于k个1，尝试把左侧多余0全部删掉，拿到最短
            if(cntOne == k){
                int curL = l;
                while(curL <= r && s[curL] == '0'){
                    curL++;
                }
                string candidate = s.substr(curL, r - curL + 1);
                // 更新答案
                if(ans == ""
                   || candidate.size() < ans.size()
                   || (candidate.size() == ans.size() && candidate < ans)){
                    ans = candidate;
                }
            }
        }
        return ans;
    }
};


// 替换子串得到平衡字符串（1234）
class Solution {
public:
    int balancedString(string s) {
        unordered_map<char,int> cnt;
        int n = s.size();
        int target = n / 4;
        for(auto c : s) cnt[c]++;

        // 已经平衡
        if(cnt['Q'] == target && cnt['W'] == target && cnt['E'] == target && cnt['R'] == target){
            return 0;
        }

        int l = 0;
        int ans = n;

        for(int r = 0; r < n; r++){
            cnt[s[r]]--; // s[r]进入窗口，不属于窗口外

            // 判断：窗口外面所有字符数量都<=target，窗口合法
            while(cnt['Q'] <= target && cnt['W'] <= target && cnt['E'] <= target && cnt['R'] <= target){
                ans = min(ans, r - l + 1);
                cnt[s[l]]++; // s[l]移出窗口，回到窗口外
                l++;
            }
        }
        return ans;
    }
};


// 无限数组的最短子数组（2875）
class Solution {
public:
    int minSizeSubarray(vector<int>& nums, int target) {
        long long sumTotal = accumulate(nums.begin(), nums.end(), 0LL);
        int n = nums.size();
        long long rem = target;
        int k = 0;
        // 有完整循环段
        if(sumTotal != 0){
            k = target / sumTotal;
            rem = target % sumTotal;
        }
        // 拼接nums+nums，用来找跨首尾的子数组
        vector<int> arr = nums;
        arr.insert(arr.end(), nums.begin(), nums.end());
        int l = 0;
        long long curSum = 0;
        int minLen = INT_MAX;

        for(int r = 0; r < arr.size(); r++){
            curSum += arr[r];
            // 正数数组，超过rem就收缩左边界
            while(curSum > rem){
                curSum -= arr[l];
                l++;
            }
            // 找到和恰好等于rem
            if(curSum == rem){
                minLen = min(minLen, r - l + 1);
            }
        }
        if(minLen == INT_MAX){
            return -1;
        }
        return minLen + k * n;
    }
};


// 最小区间（632）
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        // 堆元素：{值，数组编号，数组内下标}，小根堆
        using P = tuple<int, int, int>;
        priority_queue<P, vector<P>, greater<P>> heap;

        int k = nums.size();
        int maxVal = INT_MIN;
        for(int i = 0; i < k; i++){
            heap.emplace(nums[i][0], i, 0);
            maxVal = max(maxVal, nums[i][0]);
        }

        int bestL = get<0>(heap.top());
        int bestR = maxVal;

        while(true){
            auto [minVal, arrIdx, elemIdx] = heap.top();
            heap.pop();
            // 当前数组已经走到末尾，不能继续，结束循环
            if(elemIdx + 1 >= nums[arrIdx].size()) break;

            int nextVal = nums[arrIdx][elemIdx + 1];
            heap.emplace(nextVal, arrIdx, elemIdx + 1);
            maxVal = max(maxVal, nextVal);

            // 更新最优区间
            int newL = get<0>(heap.top());
            int newR = maxVal;
            if(newR - newL < bestR - bestL || (newR-newL == bestR-bestL && newL < bestL)){
                bestL = newL;
                bestR = newR;
            }
        }
        return {bestL, bestR};
    }
};
