// 最大连续1的个数2（1004）
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int ans = 0, cnt = 0, l = 0;
        for (int r = 0; r < nums.size(); r++)
        {
            if (nums[r] == 0)
                cnt++;
            while(cnt > k)
            {
                if (nums[l] == 0)
                {
                    cnt--;
                }
                l++;
            }
            ans = max(ans, r-l+1);
        }
        return ans;
    }
};


// 考试的最大困扰度（2024）
class Solution {
public:
    // 通用滑窗函数：最多把 target 以外的字符改k次，求最长连续target
    int maxLen(string& s, char target, int k){
        int l = 0;
        int cnt = 0; //窗口内不是target的字符数量
        int res = 0;
        for(int r = 0; r < s.size(); r++){
            if(s[r] != target){
                cnt++;
            }
            while(cnt > k){
                if(s[l] != target){
                    cnt--;
                }
                l++;
            }
            res = max(res, r - l + 1);
        }
        return res;
    }

    int maxConsecutiveAnswers(string answerKey, int k) {
        int ansT = maxLen(answerKey, 'T', k);
        int ansF = maxLen(answerKey, 'F', k);
        return max(ansT, ansF);
    }
};
