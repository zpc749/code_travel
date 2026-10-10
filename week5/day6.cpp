// 爬楼梯（70）
class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n);
        if (n == 1) return 1;
        if (n == 2) return 2;
        dp[0] = 1;
        dp[1] = 2;
        for(int i = 2; i<n;i++)
        {
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n-1];
    }
};


// 杨辉三角（118）
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res(numRows);
        for (int i = 0; i<numRows;i++)
        {
            res[i].resize(i+1,1);
            for (int j = 1; j<i;j++)
                res[i][j] = res[i-1][j-1] + res[i-1][j];
        }
        return res;
    }
};


// 打家劫舍（198）
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2;i < nums.size(); i++)
        {
            dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
        }
        return dp[nums.size()-1];
    }
};


// 完全平方数（279）
class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1, n+1);
        dp[0] = 0;
        for (int i = 1;i*i <= n;i++)
        {
            for (int j = i*i;j<=n;j++)
            {
                dp[j] = min(dp[j-i*i] + 1, dp[j]);
            }
        }
        return dp[n] == n+1 ? 0 : dp[n];
    }
};


// 零钱兑换（322）
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, amount+1);
        dp[0] = 0;
        for (int i = 0; i<coins.size();i++)
        {
            for (int j = coins[i]; j <= amount; j++)
            {
                dp[j] = min(dp[j], dp[j-coins[i]] + 1);
            }
        }
        return dp[amount] == amount+1 ? -1 : dp[amount];
    }
};


// 单词拆分（139）
#include <unordered_set>
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // 转换wordDict为unordered_set
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());

        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;

        for (int i = 1; i <= s.size(); i++) {
            for (int j = 0; j < i; j++) {
                // 判断s[j:i]是否在wordSet中
                if (dp[j] && wordSet.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break; // 提前停止内层循环
                }
            }
        }
        return dp[s.size()];
    }
};


// 最长递增子序列（300）
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n+1);
        int res = 1;
        for (int i = 0; i < n; i++) {
            dp[i] = 1; // 至少包含自己
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = res > dp[i] ? res : dp[i];
        }
        return res;
    }
};


// 乘积最大子数组（152）
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int curMax = nums[0];
        int curMin = nums[0];
        int ans = nums[0];
        for(int i = 1; i < nums.size(); i++){
            int num = nums[i];
            // 临时保存，防止curMax被覆盖之后，计算curMin用到新值
            int tmpMax = max({num, curMax * num, curMin * num});
            int tmpMin = min({num, curMax * num, curMin * num});
            curMax = tmpMax;
            curMin = tmpMin;
            ans = max(ans, curMax);
        }
        return ans;
    }
};


// 分割等和子集（416）
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int i = 0;i<nums.size();i++)
        {
            sum += nums[i];
        }
        if (sum%2 == 1) return false;

        int target = sum/2;
        vector<bool> dp(target+1, false);
        dp[0] = true;
        for (int num : nums)
        {
            for (int j = target; j>= num;j--)
            {
                dp[j] = dp[j] || dp[j-num];
            }
        }
        return dp[target];
    }
};


// 最长有效括号（32）
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        vector<int> dp(n, 0);
        int ans = 0;
        for(int i = 1; i < n; i++){
            if(s[i] == ')'){
                int pre = i - dp[i-1] - 1;
                if(pre >= 0 && s[pre] == '('){
                    dp[i] = dp[i-1] + 2;
                    if(pre - 1 >= 0) dp[i] += dp[pre - 1]; // 拼接前面连续有效串
                }
                ans = max(ans, dp[i]);
            }
        }
        return ans;
    }
};
