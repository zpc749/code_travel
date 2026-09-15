// 3. 打家劫舍

// 线性打家劫舍 ————198
dp[i] = max(dp[i-1], dp[i-2] + nums[i-1]);



// 环形打家劫舍（选首不选尾）————213
int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        int result1 = robRange(nums, 0, nums.size() - 2); // 情况一
        int result2 = robRange(nums, 1, nums.size() - 1); // 情况二
        return max(result1, result2);
}
int robRange(vector<int>& nums, int start, int end) {
    if (end == start) return nums[start];
    vector<int> dp(nums.size());
    dp[start] = nums[start];
    dp[start + 1] = max(nums[start], nums[start + 1]);
    for (int i = start + 2; i <= end; i++) {
        dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
     }
    return dp[end];
}



// 二叉树型打家劫舍(偷还是不偷当前节点) ————337
// 长度为2的数组，0：不偷，1：偷
vector<int> robTree(TreeNode* cur) {
    if (cur == NULL) return vector<int>{0, 0};
    vector<int> left = robTree(cur->left);
    vector<int> right = robTree(cur->right);
    // 偷cur，那么就不能偷左右节点。
    int val1 = cur->val + left[0] + right[0];
    // 不偷cur，那么可以偷也可以不偷左右节点，则取较大的情况
    int val2 = max(left[0], left[1]) + max(right[0], right[1]);
    return {val2, val1};
}
