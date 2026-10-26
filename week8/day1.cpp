// 搜索二维矩阵2（240）
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if(m == 0) return false;
        int n = matrix[0].size();

        int i = 0;         // 行：从第一行开始
        int j = n - 1;     // 列：从最后一列（右上角）

        while(i < m && j >= 0){
            if(matrix[i][j] == target){
                return true;
            }else if(matrix[i][j] > target){
                j--;  // 太大，舍弃当前列，左移
            }else{
                i++;  // 太小，舍弃当前行，下移
            }
        }
        return false; // 越界没找到
    }
};

// 统计有序矩阵中的负数（1351）
class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;

        int i = 0;
        int j = n-1;
        while( i < m && j >=  0){
            if (grid[i][j] < 0){
                ans += m-i;
                j--;
            }else{
                i++;
            }
        }
        return ans;
    }
};
