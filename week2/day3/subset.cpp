// 子集（78）

vector<int> res;
vector<int> path;
void backtracking(vector<int>& nums, int startIndex)
{
  res.push_back(path);
  if (startIndex >= nums.size()) return;
  for (int i= startIndex; i < nums.size(); i++)
  {
    path.push_back(nums[i]);
    backtracking(nums, i + 1);
    path.pop_back();
  }
}



// 子集2（90）

vector<vector<int>> result;
vector<int> path;
void backtracking(vector<int>& nums, int startIndex, vector<bool>& used) {
    result.push_back(path);
    for (int i = startIndex; i < nums.size(); i++) {
        // used[i - 1] == true，说明同一树枝candidates[i - 1]使用过
        // used[i - 1] == false，说明同一树层candidates[i - 1]使用过
        // 而我们要对同一树层使用过的元素进行跳过
        if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) {
            continue;
        }
        path.push_back(nums[i]);
        used[i] = true;
        backtracking(nums, i + 1, used);
        used[i] = false;
        path.pop_back();
    }
}
