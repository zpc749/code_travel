// 最高频元素的频数（1838）
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        long long sum = 0;
        int l=0, ans=0;
        for(int r=0;r<nums.size();r++){
            sum += nums[r];
            // 把[l,r]全部变成nums[r]需要的操作数 >k，收缩左边界
            while((long long)nums[r]*(r-l+1) - sum > k){
                sum -= nums[l];
                l++;
            }
            ans = max(ans, r-l+1);
        }
        return ans;
    }
};


// 每种字符最少取K个（2516）
class Solution {
public:
    int takeCharacters(string s, int k) {
        int total[3]={0};
        for(auto ch : s) total[ch-'a']++;
        // 任何字符总数不足k，直接不可能
        if(total[0]<k || total[1]<k || total[2]<k) return -1;
        int l=0;
        int win[3]={0};
        int maxKeep = 0;
        for(int r=0;r<s.size();r++){
            win[s[r]-'a']++;
            // 剩下的字符 = total - win，剩下的必须全部>=k
            while(total[0]-win[0]<k || total[1]-win[1]<k || total[2]-win[2]<k){
                win[s[l]-'a']--;
                l++;
            }
            maxKeep = max(maxKeep, r-l+1);
        }
        return s.size() - maxKeep;
    }
};


// 毯子覆盖的最多白色砖块数（2271）
class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
        sort(tiles.begin(), tiles.end());
        int n = tiles.size();
        int left = 0;
        int cover = 0; //窗口内完全被毯子包含的白色砖块总数
        int ans = 0;

        for(int right = 0; right < n; right++){
            int tl = tiles[right][0];
            int tr = tiles[right][1];
            cover += tr - tl + 1;

            // 收缩左边界：如果tiles[left]整个区间都在毯子左边，扔掉
            while(tiles[left][1] < tr - carpetLen + 1){
                cover -= tiles[left][1] - tiles[left][0] + 1;
                left++;
            }
            // 计算毯子盖住的数量：cover 减去毯子左边漏出去的部分
            int uncover = max( tr - carpetLen + 1 - tiles[left][0], 0 );
            ans = max(ans, cover - uncover);
        }
        return ans;
    }
};
