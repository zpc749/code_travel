// 最大子数组问题（递归和分治）

int maxSubArray(vector<int>& nums)
{
  return divide(nums, 0, nums.size()-1);
}
int divide(vector<int>& nums, int l, int r)
{
  if (l == r) return nums[l];

  int mid = l + (r-l)/2;
  int leftMax = divide(nums, l, mid);
  int rightMax = divide(nums, mid+1, r);
  int crossMax = crossSum(nums, l, mid, r);
  return max({leftMax, rightMax, crossMax});
}
int crossSum(vector<int>& nums, int l, int mid, int r)
{
  int leftSum = INT_MIN, sum = 0;
  for (int i = mid, i >= l;i--)
  {
    sum += nums[i];
    leftSum = max(leftSum, sum);
  }
  int rightSum = INT_MIN, sum = 0;
  for (int i = mid+1;i<=r;i++)
  {
    sum += nums[i];
    rightSum = max(rightSum, sum);
  }
  return leftSum + rightSum;
}
