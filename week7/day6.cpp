// 好子数组的最大分数（1793）
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        int l = k, r = k;   // 起点都在k，背向向外扩展
        int curMin = nums[k];
        int ans = curMin;
        while(l > 0 || r < n-1)
        {
            // 优先选左右更大的那边扩展，保证min尽可能大
            int leftVal = (l-1 >= 0) ? nums[l-1] : -1;
            int rightVal = (r+1 < n) ? nums[r+1] : -1;
            if(leftVal > rightVal)
            {
                l--;
                curMin = min(curMin, nums[l]);
            }
            else
            {
                r++;
                curMin = min(curMin, nums[r]);
            }
            ans = max(ans, curMin * (r - l + 1));
        }
        return ans;
    }
};


// 三角形的最小周长
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        // a <= b <= c，满足 a+b>c 就可以构成三角形
        for(int i = (int)nums.size()-1; i >= 2; i--)
        {
            if(nums[i-2] + nums[i-1] > nums[i])
            {
                return nums[i-2] + nums[i-1] + nums[i];
            }
        }
        return 0;
    }
};
