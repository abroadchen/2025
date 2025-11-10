//
// Created by Psy.C on 2025/11/10.
//
/*
*f：记录前一个字符，初始化为-1（表示没有前一个字符）
cnt：记录连续相同字符的计数，初始化为0
 *
 *循环遍历字符串的每个字符
*如果当前字符与前一个字符不同：
更新前一个字符f为当前字符
重置计数器cnt为0
 *增加连续相同字符的计数
 *
 *时间复杂度为O(n)
 *
 */
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; getline(cin, s);

    int f(-1), cnt(0);
    string res("NO");
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] != f) { f = s[i]; cnt = 0; }
        ++cnt;
        if (cnt >= 7) { res = "YES"; break; }
    }
    cout << res << '\n';
    return 0;
}