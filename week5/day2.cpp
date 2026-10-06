// 搜索旋转排序数组（33）
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while(l <= r){
            int mid = l + (r - l)/2; // 防溢出
            if(nums[mid] == target) return mid;

            if(nums[l] <= nums[mid]){ 
                // 左边有序
                if(nums[l] <= target && target < nums[mid]){
                    r = mid - 1;
                }else{
                    l = mid + 1;
                }
            }else{ 
                // 右边有序
                if(nums[mid] < target && target <= nums[r]){
                    l = mid + 1;
                }else{
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};


// 寻找旋转排序数组中的最小值（153）
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0;
        int r = nums.size() -1;
        int res = nums[0];

        while(l <= r)
        {
            int mid = l + (r-l)/2;

            if (nums[l] <= nums[mid])
            {
                res = min(res, nums[l]);
                l = mid + 1;
            }
            else
            {
                r = mid;
            }
        }
        return res;
    }
};


// 寻找两个正序数组的中位数（4）
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 保证 nums1 更短，只在短数组二分
        if(nums1.size() > nums2.size()) 
            return findMedianSortedArrays(nums2, nums1);
        
        int n1 = nums1.size(), n2 = nums2.size();
        int l = 0, r = n1;
        int totalLeft = (n1 + n2 + 1) / 2;
        
        while(l <= r){
            int i = l + (r - l)/2; // nums1左边i个
            int j = totalLeft - i; // nums2左边j个
            
            int left1  = (i == 0) ? INT_MIN : nums1[i-1];
            int right1 = (i == n1)? INT_MAX : nums1[i];
            int left2  = (j == 0) ? INT_MIN : nums2[j-1];
            int right2 = (j == n2)? INT_MAX : nums2[j];
            
            if(left1 <= right2 && left2 <= right1){
                // 合法分割
                if((n1+n2)%2 == 1){
                    return max(left1, left2);
                }else{
                    return (max(left1, left2) + min(right1, right2)) / 2.0;
                }
            }else if(left1 > right2){
                // nums1左边太大，分割线往左移
                r = i - 1;
            }else{
                // 分割线往右移
                l = i + 1;
            }
        }
        return 0.0; // 不会走到这里
    }
};


// 每日温度（739）
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n, 0);
        stack<int> st; // 存下标
        
        for(int i = 0; i < n; i++){
            while(!st.empty() && temperatures[i] > temperatures[st.top()]){
                int idx = st.top();
                st.pop();
                ans[idx] = i - idx;
            }
            st.push(i);
        }
        return ans;
    }
};


// 柱状图中的最大矩形（84）
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        // 哨兵：前后加0，强制弹出所有元素
        vector<int> h = heights;
        h.insert(h.begin(), 0);
        h.push_back(0);
        
        stack<int> st;
        int maxArea = 0;
        
        for(int i = 0; i < h.size(); i++){
            // 新来的更小，破坏递增，弹出计算
            while(!st.empty() && h[i] < h[st.top()]){
                int cur = st.top();
                st.pop();
                int left = st.top();
                int width = i - left - 1;
                maxArea = max(maxArea, h[cur] * width);
            }
            st.push(i);
        }
        return maxArea;
    }
};


// 数组中的第K个最大元素（215）
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for(int x : nums){
            minHeap.push(x);
            if(minHeap.size() > k) minHeap.pop();
        }
        return minHeap.top();
    }
};


// 前K个高频元素（347）
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> cnt;
        int n = nums.size();
        for(int x : nums) cnt[x]++;
        
        vector<vector<int>> bucket(n+1); // bucket[频率] = 数字列表
        for(auto& p : cnt){
            bucket[p.second].push_back(p.first);
        }
        
        vector<int> res;
        // 从最大频率往后找
        for(int i = n; i >= 0 && res.size() < k; i--){
            for(int num : bucket[i]){
                res.push_back(num);
                if(res.size() == k) break;
            }
        }
        return res;
    }
};


// 数据流中的中位数（295）
class MedianFinder {
private:
    priority_queue<int> maxHeap; // 左边：较小一半，大顶
    priority_queue<int, vector<int>, greater<int>> minHeap; // 右边：较大一半，小顶

public:
    MedianFinder() {}
    
    void addNum(int num) {
        if(maxHeap.empty() || num <= maxHeap.top()){
            maxHeap.push(num);
        }else{
            minHeap.push(num);
        }
        // 平衡
        if(maxHeap.size() > minHeap.size() + 1){
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }else if(minHeap.size() > maxHeap.size()){
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if(maxHeap.size() > minHeap.size()){
            return maxHeap.top();
        }else{
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
    }
};


/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
