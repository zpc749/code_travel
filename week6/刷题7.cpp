// 包含所有三种字符的子字符串数目（1358）
class Solution {
public:
    int numberOfSubstrings(string s) {
        int cnt[3] = {0};
        int left = 0;
        long long ans = 0;
        for(int right = 0; right < s.size(); right++){
            cnt[s[right]-'a']++;
            // 窗口满足条件，不断右移left，寻找临界边界
            while(cnt[0] && cnt[1] && cnt[2]){
                cnt[s[left]-'a']--;
                left++;
            }
            // 退出while：[left,right]不满足条件
            // 所有起点0~left-1，右端right，全部合法，一共left个
            ans += left;
        }
        return ans;
    }
};


// 统计最大元素出现至少K次的子数组（2962）
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int maxVal = *max_element(nums.begin(), nums.end());
        // unordered_map<int,int> umap;
        int cnt = 0;
        long long ans = 0;
        int l = 0;
        for (int r = 0; r < nums.size(); r++){
            if (nums[r] == maxVal) cnt++;
            while(cnt >= k){
                if (nums[l] == maxVal) cnt--;
                l++;
            }
            ans += l;
        }
        return ans;
    }
};

// 字符至少出现K次的子字符串1（3325）
class Solution {
public:
    int numberOfSubstrings(string s, int k) {
        int n = s.size();
        int left = 0;
        int cnt[26] = {0};
        long long ans = 0;
        for(int right = 0; right < n; right++){
            cnt[s[right]-'a']++;
            // 只要存在字符>=k，就收缩左边界
            while(true){
                bool ok = false;
                for(int i=0;i<26;i++){
                    if(cnt[i]>=k) {ok=true;break;}
                }
                if(!ok) break;
                cnt[s[left]-'a']--;
                left++;
            }
            ans += left;
        }
        return ans;
    }
};
