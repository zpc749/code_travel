// 分发饼干（455）

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int count = 0;
        int gp = 0, sp = 0;
        while(gp < g.size() && sp < s.size())
        {
            if (g[gp] <= s[sp])
            {
                gp++;
                count++;
            }
            sp++;
        }
        return count;
    }
};
