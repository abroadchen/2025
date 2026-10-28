//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
s[N]、t[N]：两个字符数组（C 风格字符串）。
ls：s 的长度；lt：t 的长度；sum：两者长度之和
s[ls-1] == t[lt-1]：两个串当前末尾字符相等。
ls > 0：s 还没有删空。
lt > 0：t 还没有删空。
每轮末尾执行的步进：

ls--：s 的有效末尾前移一位。
lt--：t 的有效末尾前移一位。
sum -= 2：总数减少 2（因为这两个相等的字符被"配掉"了）
输出 sum，也就是"两串总长 − 2×已配对的相等末尾字符数"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5;

char s[N], t[N];
int ls, lt, sum;
int main() {
    fast;
    cin >> s >> t; ls = strlen(s); lt = strlen(t); sum = ls + lt;
    for (; s[ls-1] == t[lt-1] && ls > 0 && lt > 0; ls--, lt--) sum -= 2;
    cout << sum << '\n';
    return 0;
}