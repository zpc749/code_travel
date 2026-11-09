// 739. 每日温度
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& t) {
        int n = t.size();
        vector<int> ans(n,0);
        stack<int> st;
        for(int i=0;i<n;i++){
            while(!st.empty() && t[i]>t[st.top()]){
                int idx = st.top(); st.pop();
                ans[idx] = i - idx;
            }
            st.push(i);
        }
        return ans;
    }
};


// 1475. 商品折扣后的最终价格
class Solution {
public:
    vector<int> finalPrices(vector<int>& p) {
        int n = p.size();
        stack<int> st;
        vector<int> ans(n);
        for(int i=0;i<n;i++){
            while(!st.empty() && p[i] <= p[st.top()]){
                int idx = st.top(); st.pop();
                ans[idx] = p[idx] - p[i];
            }
            st.push(i);
        }
        // 栈剩下的元素，右边没有更小，原价保留
        while(!st.empty()){
            int idx = st.top(); st.pop();
            ans[idx] = p[idx];
        }
        return ans;
    }
};


// 496. 下一个更大元素 I
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int> mp;
        stack<int> st;
        for(int x : nums2){
            while(!st.empty() && x > st.top()){
                mp[st.top()] = x;
                st.pop();
            }
            st.push(x);
        vector<int> res;
        for(int x : nums1){
            if(mp.count(x)) res.push_back(mp[x]);
            else res.push_back(-1);
        }
        return res;
    }
};


// 503. 下一个更大元素 II（环形数组！重点）
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n,-1);
        stack<int> st;
        for(int i=0; i<2*n; i++){
            int val = nums[i%n];
            while(!st.empty() && val > nums[st.top()]){
                int idx = st.top(); st.pop();
                ans[idx] = val;
            }
            if(i < n) st.push(i);
        }
        return ans;
    }
};


// 901. 股票价格跨度
class StockSpanner {
public:
    stack<pair<int,int>> st;
    StockSpanner() {}
    
    int next(int price) {
        int cnt = 1;
        while(!st.empty() && price >= st.top().first){
            cnt += st.top().second;
            st.pop();
        }
        st.push({price,cnt});
        return cnt;
    }
};
