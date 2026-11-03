// 爱吃香蕉的珂珂（875）
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        // check(k): 速度k能不能h小时吃完
        auto check = [&](long long k) -> bool {
            long long total = 0;
            for(int p : piles){
                total += (p + k - 1) / k; // 向上取整
            }
            return total <= h;
        };

        int left = 0; // 一定不行
        int right = *max_element(piles.begin(), piles.end()); // 最大堆，一小时一堆，一定可行

        while(left + 1 < right){
            int mid = left + (right - left) / 2;
            if(check(mid)){
                right = mid;
            }else{
                left = mid;
            }
        }
        return right;
    }
};

// 在 D 天内送达包裹的能力(1011)
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        auto check = [&](int cap) -> bool {
            int need = 1;
            int cur = 0;
            for(int w : weights){
                if(cur + w > cap){
                    need++;
                    cur = w;
                }else{
                    cur += w;
                }
            }
            return need <= days;
        };

        int left = *max_element(weights.begin(), weights.end()) - 1; // 小于最大包裹一定不行
        int right = accumulate(weights.begin(), weights.end(), 0); // 一天全部运完，一定可行

        while(left + 1 < right){
            int mid = left + (right - left)/2;
            if(check(mid)){
                right = mid;
            }else{
                left = mid;
            }
        }
        return right;
    }
};

// 使结果不超过阈值的最小除数(1283)
class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        auto check = [&](int div) -> bool {
            long long sum = 0;
            for(int x : nums){
                sum += (x + div - 1) / div;
            }
            return sum <= threshold;
        };

        int left = 0;
        int right = *max_element(nums.begin(), nums.end());

        while(left + 1 < right){
            int mid = left + (right - left)/2;
            if(check(mid)){
                right = mid;
            }else{
                left = mid;
            }
        }
        return right;
    }
};

// 完成旅途的最少时间(2187)
class Solution {
public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        auto check = [&](long long t) -> bool {
            long long trips = 0;
            for(int ti : time){
                trips += t / ti;
            }
            return trips >= totalTrips;
        };

        long long left = 0;
        // 最坏情况：只用最快的车跑完全部旅途
        long long minT = *min_element(time.begin(), time.end());
        long long right = minT * (long long)totalTrips;

        while(left + 1 < right){
            long long mid = left + (right - left)/2;
            if(check(mid)){
                right = mid;
            }else{
                left = mid;
            }
        }
        return right;
    }
};

// 修车的最少时间(2594)
#include <cmath>
class Solution {
public:
    long long repairCars(vector<int>& ranks, int cars) {
        auto check = [&](long long t) -> bool {
            long long total = 0;
            for(int r : ranks){
                // r*x*x <= t → x <= sqrt(t/r)
                long long x = sqrt(t / r);
                total += x;
            }
            return total >= cars;
        };

        long long left = 0;
        // 最坏：一个工人 rank=1，cars²
        long long right = 1LL * cars * cars;

        while(left + 1 < right){
            long long mid = left + (right - left)/2;
            if(check(mid)){
                right = mid;
            }else{
                left = mid;
            }
        }
        return right;
    }
};
