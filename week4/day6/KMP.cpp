​// 获取next数组
void getNext(int* next, string s)
{
    int len = s.length();
    if (len == 1)
        return new int(-1);  // 长度为1,就返回一个[-1]
    
    next = new int[len];
    next[0] = -1;
    next[1] = 0;
    
    int i = 2; cn = 0;  // cn为当前要和前一个字符比对的下标，表示当前最长相等前缀的末尾位置
    while(i < len)
    {
        if (s[i-1] == s[cn])
            next[i++] = ++cn;
        else if (cn > 0)
            cn = next[cn];
        else
            next[i++] = 0;
    } 
}
 
​// c++
 
 
// KMP匹配算法
int KMP(string s1, string s2)
{
    int len1 = s1.length();
    int len2 = s2.length();
    int x = 0;  // s1当前比较的下标
    int y = 0;  // s2当前比较的下标
    int next[] = getNext(s2, len2);  // 获取next数组
 
    while( x < len1 && y < len2)
    {
        if (s1[x] == s2[y])
        {    
            x++;
            y++;
        }
        else if (y == 0)  // P的第一个字符就匹配失败
        {
            x++;
        }
        else
        {
            y = next[y];  // 将P回退到next数组对应的值的下标
        }
    }
    return y == len2 ? x-y : -1;
}
           
