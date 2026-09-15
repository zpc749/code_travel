// 5. 子序列问题


1. 最长递增子序列（300,674）
for (int i = 0; i < n; i++) {
    dp[i] = 1; // 至少包含自己
    for (int j = 0; j < i; j++) {
        if (nums[j] < nums[i]) {
            dp[i] = max(dp[i], dp[j] + 1);
        }
    }
}

2. 最长公共子序列（718，,1143，,1035）
if (text1[i-1] == text2[j-1]) {
    dp[i][j] = dp[i-1][j-1] + 1;
} else {
    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
}

3. 最大子数组和（53）
dp[i] = max(nums[i], dp[i-1] + nums[i]);

4. 不同子序列（115）
if (s[i-1] == t[j-1]) {
    dp[i][j] = dp[i-1][j-1] + dp[i-1][j]; // 用 s[i-1] 匹配 + 不用它
} else {
    dp[i][j] = dp[i-1][j]; // 只能不用 s[i-1]
}

5. 编辑距离（392，,583，,72）
if (word1[i-1] == word2[j-1]) {
    dp[i][j] = dp[i-1][j-1]; // 不用操作
} else {
    dp[i][j] = 1 + min({
        dp[i-1][j],      // 删除 word1[i-1]
        dp[i][j-1],      // 插入 word2[j-1]
        dp[i-1][j-1]     // 替换
    });
}

6. 最长回文子序列（647，,516）
if (s[i] == s[j]) {
    dp[i][j] = dp[i+1][j-1] + 2;
} else {
    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
}
```
