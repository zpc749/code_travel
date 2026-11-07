// 力扣 1515
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    vector<vector<int>> pos;
    // 给定 x,y，计算总欧几里得距离
    double calc(double x, double y) {
        double res = 0;
        for (auto &p : pos) {
            double dx = x - p[0];
            double dy = y - p[1];
            res += sqrt(dx*dx + dy*dy);
        }
        return res;
    }

    // 固定x，三分y，返回这个x下的最小距离
    double f(double x) {
        double l = 0, r = 100; // 题目坐标范围 [0,100]
        for (int step = 0; step < 100; step++) {
            double m1 = l + (r - l)/3;
            double m2 = r - (r - l)/3;
            double d1 = calc(x, m1);
            double d2 = calc(x, m2);
            if (d1 < d2) {
                r = m2;
            } else {
                l = m1;
            }
        }
        return calc(x, (l + r)/2);
    }

    double getMinDistSum(vector<vector<int>>& positions) {
        pos = positions;
        double l = 0, r = 100;
        // 外层三分x
        for (int step = 0; step < 100; step++) {
            double m1 = l + (r - l)/3;
            double m2 = r - (r - l)/3;
            double d1 = f(m1);
            double d2 = f(m2);
            if (d1 < d2) {
                r = m2;
            } else {
                l = m1;
            }
        }
        return f((l + r)/2);
    }
};
