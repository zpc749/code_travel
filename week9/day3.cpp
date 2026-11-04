// 分配给商店的最多商品的最小值（2064）
class Solution {
public:
    bool check(vector<int>& qty, int k, int mid) {
        long long need = 0;
        for(int x : qty) {
            need += (x + mid - 1) / mid; // 向上取整，需要多少商店
        }
        return need <= k;
    }
    int minimizedMaximum(int n, vector<int>& quantities) {
        int l = 1, r = 1e9;
        while(l < r) {
            int mid = l + (r - l) / 2;
            if(check(quantities, n, mid)) r = mid;
            else l = mid + 1;
        }
        return l;
    }
};

// 袋子里最少数目的球（1760）
class Solution {
public:
    bool check(vector<int>& nums, int op, int mid) {
        long long need = 0;
        for(int x : nums) {
            if(x > mid) need += (x - 1)/mid;
        }
        return need <= op;
    }
    int minimumSize(vector<int>& nums, int maxOperations) {
        int l = 1, r = 1e9;
        while(l < r) {
            int mid = l + (r - l) / 2;
            if(check(nums, maxOperations, mid)) r = mid;
            else l = mid + 1;
        }
        return l;
    }
};

// 最小化数对的最大差值（2616） 
class Solution {
public:
    bool check(vector<int>& nums, int p, int mid) {
        int cnt = 0;
        for(int i = 0; i < nums.size()-1; ) {
            if(nums[i+1] - nums[i] <= mid) {
                cnt++;
                i += 2; // 选了这一对，不能复用
            } else {
                i++;
            }
        }
        return cnt >= p;
    }
    int minimizeMax(vector<int>& nums, int p) {
        sort(nums.begin(), nums.end());
        int l = 0, r = nums.back() - nums[0];
        while(l < r) {
            int mid = l + (r - l) / 2;
            if(check(nums, p, mid)) r = mid;
            else l = mid + 1;
        }
        return l;
    }
};

// 分割数组的最大值（410）
class Solution {
public:
    bool check(vector<int>& nums, int m, int mid) {
        int cnt = 1;
        long long sum = 0;
        for(int x : nums) {
            if(sum + x > mid) {
                cnt++;
                sum = x;
            } else {
                sum += x;
            }
        }
        return cnt <= m;
    }
    int splitArray(vector<int>& nums, int m) {
        int l = *max_element(nums.begin(), nums.end());
        long long r = accumulate(nums.begin(), nums.end(), 0LL);
        while(l < r) {
            int mid = l + (r - l) / 2;
            if(check(nums, m, mid)) r = mid;
            else l = mid + 1;
        }
        return l;
    }
};

// 图的最大边权的最小值（3419）
class Solution {
public:
    vector<int> fa;
    int find(int x) {
        if(fa[x] != x) fa[x] = find(fa[x]);
        return fa[x];
    }
    bool check(int n, vector<vector<int>>& edges, int mid) {
        fa.resize(n);
        for(int i=0;i<n;i++) fa[i]=i;
        for(auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if(w <= mid) {
                int fu = find(u), fv = find(v);
                if(fu != fv) fa[fu] = fv;
            }
        }
        return find(0) == find(n-1);
    }
    int minMaxWeight(int n, vector<vector<int>>& edges) {
        int l = 1, r = 1e6;
        int ans = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(check(n, edges, mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};
