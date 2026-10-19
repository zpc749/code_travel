// K个不同整数的子数组（992）
class Solution {
public:
    // 普通函数：统计nums中和 <= s 的子数组个数
    int atMost(vector<int>& nums, int s) {
        if(s < 0) return 0;
        int left = 0;
        int sum = 0;
        int res = 0;
        for(int right = 0; right < nums.size(); right++){
            sum += nums[right];
            while(sum > s){
                sum -= nums[left];
                left++;
            }
            // [left,right]合法，以right结尾一共有 right-left+1 个子数组
            res += right - left + 1;
        }
        return res;
    }

    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return atMost(nums, goal) - atMost(nums, goal - 1);
    }
};


// 和相同的二元子数组（930）
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        auto atMost = [&](int s) {
            if(s < 0) return 0;
            int left = 0, sum = 0, ans = 0;
            for(int r=0;r<nums.size();r++){
                sum += nums[r];
                while(sum > s){
                    sum -= nums[left];
                    left++;
                }
                ans += r-left+1; // 越短越合法模板
            }
            return ans;
        };
        return atMost(goal) - atMost(goal-1);
    }
};


// 统计优美子数组（1248）
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        auto atMost = [&](int x){
            if(x<0) return 0;
            int left=0, cntOdd=0, ans=0;
            for(int r=0;r<nums.size();r++){
                if(nums[r]%2 ==1) cntOdd++;
                while(cntOdd > x){
                    if(nums[left]%2 ==1) cntOdd--;
                    left++;
                }
                ans += r-left+1;
            }
            return ans;
        };
        return atMost(k) - atMost(k-1);
    }
};


// 统计包含K个不同整数的子数组（3859）
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k, int m) {
        unordered_map<int, int> cnt;
        int left1 = 0, left2 = 0;
        int kind = 0; // 当前窗口不同数字种类
        int good = 0; // 当前窗口中，满足出现次数>=m的数字个数
        long long ans = 0;

        for(int right = 0; right < nums.size(); right++){
            int x = nums[right];
            if(cnt[x]==0) kind++;
            cnt[x]++;
            // 刚好到达m次，这个数字变成"达标"
            if(cnt[x] == m) good++;

            // left1收缩：保证窗口种类 <=k
            while(kind > k){
                int lx = nums[left1];
                if(cnt[lx]==m) good--;
                cnt[lx]--;
                if(cnt[lx]==0) kind--;
                left1++;
            }

            // left2收缩：窗口种类 ==k，并且全部k种都>=m，尽可能右移left2
            while(kind == k && good == k){
                int lx = nums[left2];
                if(cnt[lx]==m) good--;
                cnt[lx]--;
                if(cnt[lx]==0) kind--;
                left2++;
            }
            // 起点在 [left1, left2 -1] 全部合法，数量 left2-left1
            ans += left2 - left1;
        }
        return ans;
    }
};
