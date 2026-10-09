// 买卖股票最佳时机（121）
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;  // 到当前为止最低价格
        int maxProfit = 0;       // 最大利润
        for(int p : prices){
            if(p < minPrice)
                minPrice = p;
            else
                maxProfit = max(maxProfit, p - minPrice);
        }
        return maxProfit;
    }
};


// 跳跃游戏（55）
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int cover = 0;
        if (nums.size() == 1) return true; // 只有一个元素，就是能达到
        for (int i = 0; i <= cover; i++) { // 注意这里是小于等于cover
            cover = max(i + nums[i], cover);
            if (cover >= nums.size() - 1) return true; // 说明可以覆盖到终点了
        }
        return false;
    }
};


// 跳跃游戏2（45）
class Solution {
public:
    int jump(vector<int>& nums) {
        int curDistance = 0;    // 当前覆盖的最远距离下标
        int ans = 0;            // 记录走的最大步数
        int nextDistance = 0;   // 下一步覆盖的最远距离下标
        for (int i = 0; i < nums.size() - 1; i++) { // 注意这里是小于nums.size() - 1，这是关键所在
            nextDistance = max(nums[i] + i, nextDistance); // 更新下一步覆盖的最远距离下标
            if (i == curDistance) {                 // 遇到当前覆盖的最远距离下标
                curDistance = nextDistance;         // 更新当前覆盖的最远距离下标
                ans++;
            }
        }
        return ans;
    }
};


// 划分字母区间（763）
class Solution {
public:
    vector<int> partitionLabels(string S) {
        int hash[27] = {0}; // i为字符，hash[i]为字符出现的最后位置
        for (int i = 0; i < S.size(); i++) { // 统计每一个字符最后出现的位置
            hash[S[i] - 'a'] = i;
        }
        vector<int> result;
        int left = 0;
        int right = 0;
        for (int i = 0; i < S.size(); i++) {
            right = max(right, hash[S[i] - 'a']); // 找到字符出现的最远边界
            if (i == right) {
                result.push_back(right - left + 1);
                left = i + 1;
            }
        }
        return result;
    }
};


// 只出现一次的数字（136）
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for(int x : nums){
            res ^= x;   // 等价 res = res ^ x
        }
        return res;
    }
};


//多数元素（169）
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = -1;
        int count = 0;
        for(int x : nums) {
            if(count == 0) {
                candidate = x;     // 选票清零，换新候选人
            }
            if(x == candidate) count++;
            else count--;          // 不是它，抵消一票
        }
        return candidate;
    }
};


// 颜色分类（75）
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int l = 0;        // 0区的下一个存放位置
        int r = nums.size()-1; // 2区的前一个存放位置
        int i = 0;        // 当前遍历指针
        while(i <= r) {
            if(nums[i] == 0) {
                swap(nums[i], nums[l]);
                l++;
                i++;
            } else if(nums[i] == 2) {
                swap(nums[i], nums[r]);
                r--;   // 注意：i不要++！换过来的数还没检查
            } else { // ==1，本来就在中间区
                i++;
            }
        }
    }
};

// 下一个排列（31）
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i = n - 2;
        // ① 从后往前，找第一个【下坡点】：nums[i] < nums[i+1]
        while(i >= 0 && nums[i] >= nums[i+1]) i--;

        if(i >= 0){ // 不是最大排列
            int j = n - 1;
            // ② 从后往前，找第一个比 nums[i] 大的数
            while(nums[j] <= nums[i]) j--;
            swap(nums[i], nums[j]); // ③ 交换
        }
        // ④ 把 i 后面整体反转（变成升序，字典序最小）
        reverse(nums.begin() + i + 1, nums.end());
    }
};


// 寻找重复数（287）
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        // 第一阶段：快慢指针相遇
        do{
            slow = nums[slow];
            fast = nums[nums[fast]];
        }while(slow != fast);

        // 第二阶段：一个指针回到起点，同速走，交点就是环入口=重复数
        slow = 0;
        while(slow != fast){
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};
