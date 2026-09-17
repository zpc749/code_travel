// k次取反后最大化的数组和（1005）

// 自己的方法
class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] < 0 && k > 0) {
                nums[i] = -nums[i];  // 对负数取反
                k--;                 // 每次取反操作减少一次 k
            }
        }

        // 如果还有剩余 k 次操作，计算 k 的奇偶性
        // 当 k 是奇数时，需要将数组中最小的元素取反一次
        if (k % 2 != 0) {
            int minElement = *min_element(nums.begin(), nums.end());
            sum -= 2 * minElement; // 取反最小的元素（即减去2倍该元素）
        }

        // 求数组的总和
        for (int num : nums) {
            sum += num;
        }

        return sum;
    }
};

// 代码随想录
class Solution {
static bool cmp(int a, int b) {
    return abs(a) > abs(b);
}
public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        sort(A.begin(), A.end(), cmp);       // 第一步
        for (int i = 0; i < A.size(); i++) { // 第二步
            if (A[i] < 0 && K > 0) {
                A[i] *= -1;
                K--;
            }
        }
        if (K % 2 == 1) A[A.size() - 1] *= -1; // 第三步
        int result = 0;
        for (int a : A) result += a;        // 第四步
        return result;
    }
};
