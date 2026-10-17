// 乘积小于K的子数组（713）
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;
        int cnt = 0;
        int l = 0;
        long long sum = 1;
        for(int r= 0; r < nums.size();r++){
            sum *= nums[r];
            while(sum >= k){
                sum /= nums[l];
                l++;
            }
            cnt += r-l+1;
        }
        return cnt;
    }
};


// 统计得分小于K的子数组数目（2302）
class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        if (k == 1) return 0;
        long long score = 0;
        long long sum = 0;
        long long ans = 0;
        int l = 0;
        for (int r = 0; r <nums.size(); r++){
            sum += nums[r];
            score = sum*(r-l+1);
            while(score >= k){
                sum -= nums[l];
                l++;
                score = sum*(r-l+1);
            }
            ans += r-l+1;
        }
        return ans;
    }
};


// 统计满足K约束的子字符串数量1（3258）
class Solution {
public:
    int countKConstraintSubstrings(string s, int k) {
        unordered_map<int,int> umap;
        int ans = 0;
        int l = 0;
        for (int r = 0; r < s.size(); r++){
            umap[s[r]-'0']++;
            while(umap[0] > k && umap[1] > k){
                umap[s[l]-'0']--;
                l++;
            }
            ans += r-l+1;
        }
        return ans;
    }
};
