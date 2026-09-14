// 力扣169——多数元素
// 本题采用摩尔投票法Boyer-Moore投票法

int majorityElement(vector<int>& nums)
{
  int candidate = -1;
  int count = 0;
  for (int num : nums)
  {
    if (num == candidata) ++count;
    else if (--count < 0)
    {
      candidate = num;
      count = 1;
    }
  }
  return candidate;
}
