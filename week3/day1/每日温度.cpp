// 每日温度（739）

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> st;
        vector<int> result(temperatures.size(), 0);
        st.push(0);
        for (int i = 1; i<temperatures.size();i++)
        {
            if (temperatures[i] < temperatures[st.top()])
                st.push(i);
            else if (temperatures[i] == temperatures[st.top()])
                st.push(i);
            else{
                while(!st.empty() && temperatures[i] > temperatures[st.top()])
                {
                    result[st.top()] = i - st.top();
                    st.pop();
                }
                st.push(i);
            }
        }
        return result;
    }
};
