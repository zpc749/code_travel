// 递增子序列（491）

vector<vector<int>> result;
vector<int> path;
void backtracking(vector<int>& nums, int startIndex) {
    if (path.size() > 1) {
        result.push_back(path);
        // 注意这里不要加return，要取树上的节点
    }
    unordered_set<int> uset; // 使用set对本层元素进行去重
    for (int i = startIndex; i < nums.size(); i++) {
        if ((!path.empty() && nums[i] < path.back())
                || uset.find(nums[i]) != uset.end()) {
                continue;
        }
        uset.insert(nums[i]); // 记录这个元素在本层用过了，本层后面不能再用了
        path.push_back(nums[i]);
        backtracking(nums, i + 1);
        path.pop_back();
    }
}



// 全排列（46）

vector<vector<int>> result;
vector<int> path;
void backtracking (vector<int>& nums, vector<bool>& used) {
    // 此时说明找到了一组
    if (path.size() == nums.size()) {
        result.push_back(path);
        return;
    }
    for (int i = 0; i < nums.size(); i++) {
        if (used[i] == true) continue; // path里已经收录的元素，直接跳过
        used[i] = true;
        path.push_back(nums[i]);
        backtracking(nums, used);
        path.pop_back();
        used[i] = false;
    }
}

// 全排列2（47）
vector<vector<int>> result;
vector<int> path;
void backtracking (vector<int>& nums, vector<bool>& used) {
    // 此时说明找到了一组
    if (path.size() == nums.size()) {
        result.push_back(path);
        return;
    }
    for (int i = 0; i < nums.size(); i++) {
        // used[i - 1] == true，说明同一树枝nums[i - 1]使用过
        // used[i - 1] == false，说明同一树层nums[i - 1]使用过
        // 如果同一树层nums[i - 1]使用过则直接跳过
        if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) {
            continue;
        }
        if (used[i] == false) {
            used[i] = true;
            path.push_back(nums[i]);
            backtracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }
}
