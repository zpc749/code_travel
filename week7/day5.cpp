// 找出数组中的所有K近邻下标（2200）
class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        int n = nums.size();
        vector<int> res;
        int j = 0;
        for(int i = 0; i < n; i++){
            // j走到第一个满足 nums[j]==key 且 j >= i-k 的位置
            while(j < n && nums[j] != key) j++;
            if(j >= n) break;
            if(abs(i - j) <= k){
                res.push_back(i);
            }
            // 如果i已经超过j+k，这个j对后面i没用了，j右移
            if(i >= j + k) j++;
        }
        return res;
    }
};


// 有效三角形的个数（611）
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int ans = 0;
        // 枚举最长边 nums[i]
        for(int i = 2; i < n; i++){
            int l = 0, r = i - 1;
            while(l < r){
                if(nums[l] + nums[r] > nums[i]){
                    // l~r-1 全部满足
                    ans += r - l;
                    r--;
                }else{
                    l++;
                }
            }
        }
        return ans;
    }
};


// 删除最短的子数组使剩余数组有序（1574）
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();
        int r = n - 1;
        // 找最长有序后缀
        while(r > 0 && arr[r-1] <= arr[r]) r--;
        int ans = r; // 全部删掉前缀的情况
        int l = 0;
        // 同向双指针，l右移，r跟着往右扩大合法区间
        while(l < r && (l == 0 || arr[l-1] <= arr[l])){
            while(r < n && arr[l] > arr[r]) r++;
            ans = min(ans, r - l - 1);
            l++;
        }
        return ans;
    }
};
