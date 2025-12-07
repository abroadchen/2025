//
// Created by Psy.C on 2025/12/6.
//
/*
*如果是"WUB"：
跳过接下来的2个字符（总共跳过"WUB"三个字符）
如果不是在单词开头（flag == 0），则输出一个空格
继续下一次循环
*如果不是"WUB"：
设置flag = 0表示已经开始输出单词
输出当前字符
 *
*时间复杂度：O(n)，其中n是字符串长度
空间复杂度：O(1)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string s; cin >> s;
    int flag = 1;//是否是单词的开始，避免输出多余的空格
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'W' && s[i+1] == 'U' && s[i+2] == 'B') {
            i += 2;
            if (!flag) cout << ' ';
            continue;
        }
        flag = 0;
        cout << s[i];
    }
    return 0;
}