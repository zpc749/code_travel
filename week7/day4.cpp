// 验证回文串（125）
class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0, r = s.size()-1;
        while(l < r){
            while(l < r && !isalnum(s[l])) l++;
            while(l < r && !isalnum(s[r])) r--;
            if(tolower(s[l]) != tolower(s[r])) return false;
            l++; r--;
        }
        return true;
    }
};


// 两数之和2（167）
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size()-1;
        while(l < r){
            int sum = numbers[l] + numbers[r];
            if(sum == target) return {l+1, r+1};
            else if(sum < target) l++;
            else r--;
        }
        return {};
    }
};


// 有序数组的平方（977）
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n);
        int l = 0, r = n-1, idx = n-1;
        while(l <= r){
            if(abs(nums[l]) > abs(nums[r])){
                res[idx--] = nums[l] * nums[l];
                l++;
            }else{
                res[idx--] = nums[r] * nums[r];
                r--;
            }
        }
        return res;
    }
};


// 盛最多水的容器（11）
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size()-1;
        int ans = 0;
        while(l < r){
            int area = min(height[l], height[r]) * (r-l);
            ans = max(ans, area);
            if(height[l] < height[r]) l++;
            else r--;
        }
        return ans;
    }
};



// 三数之和（15）
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for(int i = 0; i < n; i++){
            if(i>0 && nums[i]==nums[i-1]) continue; //去重
            int l = i+1, r = n-1;
            while(l < r){
                int sum = nums[i]+nums[l]+nums[r];
                if(sum == 0){
                    ans.push_back({nums[i],nums[l],nums[r]});
                    while(l<r && nums[l]==nums[l+1]) l++;
                    while(l<r && nums[r]==nums[r-1]) r--;
                    l++; r--;
                }else if(sum <0) l++;
                else r--;
            }
        }
        return ans;
    }
};
