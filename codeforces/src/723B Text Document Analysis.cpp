//
// Created by Psy.C on 2026/4/23.
//
/**
s[N]：存储输入字符串
n：字符串长度（但代码中未使用）
s1：记录括号外最长连续字母长度
s2：记录括号内单个字母的数量
flag = 0：标识是否在括号内（0表示不在括号内，1表示在括号内）
len：当前连续字母长度计数器
遇到'('时，进入括号内（flag=1）
遇到')'时，离开括号（flag=0）
如果当前字符是字母（大小写均可），连续长度len加1
如果不是字母，重置len为0
如果不在括号内（!flag为真），更新s1为最大连续字母长度
如果在括号内（flag为真）且当前连续长度为1（即单个字母），s2计数器加1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e4;
char s[N];
int n, s1, s2;
int main() {
    fast;
    cin >> n >> s;
    bool flag = 0;
    for (int i = 0, len = 0; i < n; ++i) {
        if (s[i] == '(') flag = 1;
        if (s[i] == ')') flag = 0;
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) len++;
        else len = 0;
        if (!flag) s1 = max(s1, len);
        else if (len == 1) s2++;
    }
    cout << s1 << ' ' << s2 << '\n';
    return 0;
}