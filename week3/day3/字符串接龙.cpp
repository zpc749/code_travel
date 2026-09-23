// 字符串接龙（110）

// 广搜
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;
int main() {
    string beginStr, endStr, str;
    int n;
    cin >> n;
    unordered_set<string> strSet;
    cin >> beginStr >> endStr;
    for (int i = 0; i < n; i++) {
        cin >> str;
        strSet.insert(str);
    }

    // 记录strSet里的字符串是否被访问过，同时记录路径长度
    unordered_map<string, int> visitMap; // <记录的字符串，路径长度>

    // 初始化队列
    queue<string> que;
    que.push(beginStr);

    // 初始化visitMap
    visitMap.insert(pair<string, int>(beginStr, 1));

    while(!que.empty()) {
        string word = que.front();
        que.pop();
        int path = visitMap[word]; // 这个字符串在路径中的长度

        // 开始在这个str中，挨个字符去替换
        for (int i = 0; i < word.size(); i++) {
            string newWord = word; // 用一个新字符串替换str，因为每次要置换一个字符

            // 遍历26的字母
            for (int j = 0 ; j < 26; j++) {
                newWord[i] = j + 'a';
                if (newWord == endStr) { // 发现替换字母后，字符串与终点字符串相同
                    cout <<  path + 1 << endl; // 找到了路径 
                    return 0;
                }
                // 字符串集合里出现了newWord，并且newWord没有被访问过
                if (strSet.find(newWord) != strSet.end()
                        && visitMap.find(newWord) == visitMap.end()) {
                    // 添加访问信息，并将新字符串放到队列中
                    visitMap.insert(pair<string, int>(newWord, path + 1));
                    que.push(newWord);
                }
            }
        }
    }

    // 没找到输出0
    cout << 0 << endl;

}
