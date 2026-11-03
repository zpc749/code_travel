// 正方形中的最多点数（3143）
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        vector<int> min1(26, INT_MAX); // 每个字符最小r
        vector<int> min2(26, INT_MAX); // 每个字符次小r
        int n = points.size();
        for(int i = 0; i < n; ++i){
            int x = points[i][0], y = points[i][1];
            int r = max(abs(x), abs(y));
            int c = s[i] - 'a';
            if(r < min1[c]){
                min2[c] = min1[c];
                min1[c] = r;
            }else if(r < min2[c]){
                min2[c] = r;
            }
        }
        // 找到所有次小r的最小值
        int limit = INT_MAX;
        for(int c = 0; c < 26; ++c){
            if(min2[c] != INT_MAX){
                limit = min(limit, min2[c]);
            }
        }
        // 统计多少个最小r < limit
        int cnt = 0;
        for(int c = 0; c < 26; ++c){
            if(min1[c] < limit){
                cnt++;
            }
        }
        return cnt;
    }
};


// 销售价值减少的颜色球（1648）
using ll = long long;
const int MOD = 1e9 + 7;

class Solution {
public:
    int maxProfit(vector<int>& inventory, int orders) {
        auto check = [&](ll T) -> ll {
            ll sum = 0;
            for (ll x : inventory) {
                if (x > T) sum += x - T;
            }
            return sum;
        };

        ll left = 0;
        ll right = *max_element(inventory.begin(), inventory.end()) + 1;
        // 找最大T，满足 check(T) >= orders
        while (left + 1 < right) {
            ll mid = left + (right - left) / 2;
            if (check(mid) >= orders) {
                left = mid;
            } else {
                right = mid;
            }
        }
        ll T = left;
        ll total = 0;
        ll cnt_gt_T1 = 0; // > T+1 的球总数

        for (ll x : inventory) {
            if (x <= T + 1) continue;
            ll num = x - (T + 1);
            // 等差数列和：(T+2 + x) * num / 2
            total = (total + (T + 2 + x) * num / 2) % MOD;
            cnt_gt_T1 += num;
        }
        ll rem = orders - cnt_gt_T1;
        total = (total + rem * (T + 1)) % MOD;
        return total;
    }
};
