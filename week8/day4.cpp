// 等差三元组的数目(2367)
class Solution {
public:
    int arithmeticTriplets(vector<int>& nums, int k) {
        int i = 0, j = 0, l = 0;
        int ans = 0;
        int n = nums.size();
        while(i < n && j < n && l < n) {
            if(nums[j] - nums[i] < k) j++;
            else if(nums[j] - nums[i] > k) i++;
            else {
                if(nums[l] - nums[j] < k) l++;
                else if(nums[l] - nums[j] > k) j++;
                else {
                    ans++;
                    i++; j++; l++;
                }
            }
        }
        return ans;
    }
};


// 统计公平数对的数目(2563)
class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        sort(nums.begin(), nums.end());
        long long ans = 0;
        int n = nums.size();
        int l = 0, r = n - 1;
        for(int j = n - 1; j >= 1; j--) {
            while(l < j && nums[l] + nums[j] < lower) l++;
            while(r >= l && nums[r] + nums[j] > upper) r--;
            if(r >= l) ans += r - l + 1;
        }
        return ans;
    }
};


// 区间子数组个数（795）
class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int ans = 0;
        int lastLess = -1;
        int lastIn = -1;
        int n = nums.size();
        for(int i = 0; i < n; i++) {
            if(nums[i] > right) {
                lastLess = i;
                lastIn = -1;
            } else if(nums[i] >= left) {
                lastIn = i;
            }
            if(lastIn != -1) {
                ans += lastIn - lastLess;
            }
        }
        return ans;
    }
};
