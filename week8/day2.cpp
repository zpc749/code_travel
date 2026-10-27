// 最小公共值（2540）
class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        int one = 0;
        int two = 0;
        while(one < m && two < n){
            if (nums1[one] == nums2[two])
                return nums1[one];
            else if (nums1[one] > nums2[two])
                two++;
            else
                one++;
        }
        return -1;
    }
};


// 两个数组的交集2（350）
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        int one = 0;
        int two = 0;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        vector<int> res;
        while(one < m && two < n){
            if (nums1[one] == nums2[two]){
                res.push_back(nums1[one]);
                one++;
                two++;
            }
            else if (nums1[one] > nums2[two]){
                two++;
            }
            else{
                one++;
            }
        }
        return res;
    }
};


// 合并两个有序数组（88）
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;
        int j = n - 1;
        int k = m + n - 1;
        while(i >= 0 && j >= 0){
            if(nums1[i] > nums2[j]){
                nums1[k--] = nums1[i--];
            }else{
                nums1[k--] = nums2[j--];
            }
        }
        while(j >= 0){
            nums1[k--] = nums2[j--];
        }
    }
};


// 区间列表的交集（986）
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> res;
        int i = 0, j = 0;
        while(i < firstList.size() && j < secondList.size()){
            int L = max(firstList[i][0], secondList[j][0]);
            int R = min(firstList[i][1], secondList[j][1]);
            if(L <= R){
                res.push_back({L, R});
            }
            if(firstList[i][1] < secondList[j][1]){
                i++;
            }else{
                j++;
            }
        }
        return res;
    }
};


// 比较含退格的字符串（844）
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int i = s.size() - 1;
        int j = t.size() - 1;
        int skipS = 0, skipT = 0;
        while(i >= 0 || j >= 0){
            while(i >= 0){
                if(s[i] == '#'){
                    skipS++;
                    i--;
                }else if(skipS > 0){
                    skipS--;
                    i--;
                }else{
                    break;
                }
            }
            while(j >= 0){
                if(t[j] == '#'){
                    skipT++;
                    j--;
                }else if(skipT > 0){
                    skipT--;
                    j--;
                }else{
                    break;
                }
            }
            if(i >=0 && j >=0){
                if(s[i] != t[j]) return false;
            }else{
                if(i >=0 || j >=0) return false;
            }
            i--; j--;
        }
        return true;
    }
};
