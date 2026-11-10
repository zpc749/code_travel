// 456. 132 模式
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        stack<int> st;
        int second = INT_MIN;
        for(int i = nums.size()-1; i >= 0; i--){
            if(nums[i] < second) return true;
            while(!st.empty() && st.top() < nums[i]){
                second = st.top();
                st.pop();
            }
            st.push(nums[i]);
        }
        return false;
    }
};


// 1944. 队列中可以看到的人数
class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        int n = heights.size();
        vector<int> ans(n,0);
        stack<int> st;
        for(int i = n-1; i >= 0; i--){
            while(!st.empty()){
                ans[i]++;
                if(heights[i] > heights[st.top()]) st.pop();
                else break;
            }
            st.push(i);
        }
        return ans;
    }
};

// 3113. 边界元素是最大值的子数组数目
class Solution {
public:
    long long numberOfSubarrays(vector<int>& nums) {
        stack<pair<int,int>> st;
        long long res = 0;
        for(int x : nums){
            while(!st.empty() && st.top().first < x) st.pop();
            if(!st.empty() && st.top().first == x){
                res += st.top().second;
                st.top().second ++;
            }else{
                st.push({x, 1});
            }
            res++;
        }
        return res;
    }
};


// 3676. 碗子数组的数目
class Solution {
public:
    long long bowlSubarrays(vector<int>& nums) {
        long long ans = 0;
        stack<int> st;
        for(int i=0;i<nums.size();i++){
            int x = nums[i];
            while(!st.empty() && nums[st.top()] < x){
                if(i - st.top() > 1) ans++;
                st.pop();
            }
            if(!st.empty() && i - st.top() >1) ans++;
            st.push(i);
        }
        return ans;
    }
};
