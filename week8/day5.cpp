// 最大连续 1 的个数（485）
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        int i = 0;
        while(i < n)
        {
            // 外层：跳过0，找到一组1的起点
            while(i < n && nums[i] == 0) i++;
            int start = i;
            // 内层：跑完这一组连续1
            while(i < n && nums[i] == 1) i++;
            ans = max(ans, i - start);
        }
        return ans;
    }
};


// 最长连续递增序列（674）
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int n = nums.size();
        int ans = 1;
        int i = 0;
        while(i < n)
        {
            int start = i;
            i++;
            while(i < n && nums[i] > nums[i-1])
            {
                i++;
            }
            ans = max(ans, i - start);
        }
        return ans;
    }
};


// 全 0 子数组的数目（2348）
class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        long long ans = 0;
        int n = nums.size();
        int i = 0;
        while(i < n)
        {
            while(i < n && nums[i] != 0) i++;
            int start = i;
            while(i < n && nums[i] == 0) i++;
            long long len = i - start;
            ans += len * (len + 1) / 2;
        }
        return ans;
    }
};


// 数组中的最长山脉（845）
class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int n = arr.size();
        int ans = 0;
        int i = 0;
        while(i < n)
        {
            int start = i;
            // 上坡
            while(i + 1 < n && arr[i+1] > arr[i]) i++;
            int peak = i;
            // 下坡
            while(i + 1 < n && arr[i+1] < arr[i]) i++;
            // 必须有上坡+下坡才是合法山脉
            if(peak > start && i > peak)
            {
                ans = max(ans, i - start + 1);
            }
            else
            {
                i++;
            }
        }
        return ans >= 3 ? ans : 0;
    }
};
