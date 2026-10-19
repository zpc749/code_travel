// 438
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        int n = s.size(), k = p.size();
        if(n < k) return res;

        vector<int> need(26,0), win(26,0);
        for(char ch : p) need[ch-'a']++;
        //初始化第一个窗口
        for(int i=0;i<k;i++) win[s[i]-'a']++;

        if(win == need) res.push_back(0);
        //滑动窗口
        for(int right = k; right < n; right++){
            win[s[right]-'a']++;
            win[s[right - k]-'a']--;
            if(win == need){
                res.push_back(right - k + 1);
            }
        }
        return res;
    }
};

// 424
class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> cnt(26,0);
        int left = 0;
        int maxFreq = 0;
        int ans = 0;
        for(int right = 0; right < s.size(); right++){
            cnt[s[right]-'A']++;
            maxFreq = max(maxFreq, cnt[s[right]-'A']);
            //窗口长度 - 窗口最多字符数量 = 需要替换的字符数
            while( (right-left+1) - maxFreq > k ){
                cnt[s[left]-'A']--;
                left++;
            }
            ans = max(ans, right-left+1);
        }
        return ans;
    }
};

// 2401
class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int mask = 0;
        int left = 0;
        int ans = 0;
        for(int right = 0; right < nums.size(); right++){
            //冲突：mask & nums[right] !=0，不断右移left
            while( mask & nums[right] ){
                mask ^= nums[left];
                left++;
            }
            mask |= nums[right];
            ans = max(ans, right-left+1);
        }
        return ans;
    }
};

// 825
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        sort(ages.begin(), ages.end());
        int n = ages.size();
        int left = 0;
        int ans = 0;
        for(int right = 0; right < n; right++){
            //找到最小left，满足 ages[left] > 0.5*ages[right]+7
            while(ages[left] <= 0.5 * ages[right] +7){
                left++;
            }
            // [left, right-1] 的人可以收到right的好友申请（不能给自己发）
            ans += right - left;
        }
        return ans;
    }
};
