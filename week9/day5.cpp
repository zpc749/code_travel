// 668. 乘法表中第 K 小的数
class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        auto count = [&](int x) -> int {
            int res = 0;
            for (int i = 1; i <= m; i++) {
                res += min(x / i, n);
            }
            return res;
        };
        int l = 1, r = m * n;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (count(mid) >= k) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
};

// 378. 有序矩阵中第 K 小的元素
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        auto count = [&](int x) -> int {
            int res = 0;
            int i = n - 1, j = 0;
            while (i >= 0 && j < n) {
                if (matrix[i][j] <= x) {
                    res += i + 1;
                    j++;
                } else {
                    i--;
                }
            }
            return res;
        };
        int l = matrix[0][0], r = matrix[n-1][n-1];
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (count(mid) >= k) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
};

// 719. 找出第 K 小的数对距离
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        auto count = [&](int x) -> int {
            int res = 0;
            int left = 0;
            for (int right = 0; right < nums.size(); right++) {
                while (nums[right] - nums[left] > x) {
                    left++;
                }
                res += right - left;
            }
            return res;
        };
        int l = 0, r = nums.back() - nums[0];
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (count(mid) >= k) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
};
