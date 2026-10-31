// 34
class Solution { 
public:
    int binarySearch(vector<int>& nums, int target, bool lower) {
        int left = 0, right = (int)nums.size() - 1, ans = (int)nums.size();
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] > target || (lower && nums[mid] >= target)) {
                right = mid - 1;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int leftIdx = binarySearch(nums, target, true);
        int rightIdx = binarySearch(nums, target, false) - 1;
        if (leftIdx <= rightIdx && rightIdx < nums.size() && nums[leftIdx] == target && nums[rightIdx] == target) {
            return vector<int>{leftIdx, rightIdx};
        } 
        return vector<int>{-1, -1};
    }
};


// 35
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0,r = nums.size();
        while(l < r)
        {
            int mid = l + (r-l)/2;
            if (nums[mid] == target)
            {
                return mid;
            }
            else if (nums[mid] > target)
            {
                r = mid;
            }
            else
            {
                l = mid +1;
            }
        }
        return r;
    }
};


// 704
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r= nums.size()-1;
        int index = -1;
        while(l <= r){
            int mid = (l+r)/2;
            if (nums[mid] == target){
                index = mid;
                break;
            }else if(nums[mid] > target){
                r = mid-1;
            }else if (nums[mid] < target){
                l = mid+1;
            }
        }
        return index;
    }
};


// 744
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int l = 0;
        int r = letters.size()-1;
        while(l <= r){
            int mid = l + (r-l)/2;
            if (letters[mid] <= target){
                l = mid +1;
            }else{
                r = mid -1;
            }
        }
        return letters[l%letters.size()];
    }
};


// 2529
class Solution {
public:
    int maximumCount(vector<int>& nums) {
        int n = nums.size();
        int l = 0;
        int r = nums.size() -1;
        while(l <= r){
            int mid = l + (r-l)/2;
            if (nums[mid] < 0){
                l = mid +1;
            }else{
                r = mid - 1;
            }
        }
        int negativeCount = l;
        while(l < n){
            if (nums[l] != 0){
                break;
            }
            l++;
        }
        int positiveCount = n-l;

        return max(negativeCount, positiveCount);
    }
};
