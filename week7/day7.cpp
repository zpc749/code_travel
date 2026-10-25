// 移除元素（27）
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0) return 0;
        int l = 0, r = 0;
        for (r; r < nums.size(); r++){
            if (nums[r] != val){
                nums[l++] = nums[r];
            }
        }
        return l;
    }
};


// 删除有序数组中的重复项（26）
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 1) return 1;
        int l = 0, r = 1;
        for (r; r<nums.size(); r++){
            if (nums[r] != nums[l]){
                nums[++l] = nums[r];
            }
        }
        return l+1;
    }
};


// 删除有序数组中的重复项2（80）
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int l = 0;
        for (int r = 0; r<nums.size();r++){
            if (l < 2 || nums[r] != nums[l-2])
            nums[l++] = nums[r];
        }
        return l;
    }
};


// 移动零（283）
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int l = 0;
        for (int r = 0; r <nums.size(); r++){
            if (nums[r] != 0){
                nums[l++] = nums[r];
            }
        }
        for (int i = l; i<nums.size();i++)
            nums[i] = 0;
    }
};


// 颜色分类（75）
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int l = 0;        // 0区的下一个存放位置
        int r = nums.size()-1; // 2区的前一个存放位置
        int i = 0;        // 当前遍历指针
        while(i <= r) {
            if(nums[i] == 0) {
                swap(nums[i], nums[l]);
                l++;
                i++;
            } else if(nums[i] == 2) {
                swap(nums[i], nums[r]);
                r--;   // 注意：i不要++！换过来的数还没检查
            } else { // ==1，本来就在中间区
                i++;
            }
        }
    }
};
