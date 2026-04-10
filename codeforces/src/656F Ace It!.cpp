//
// Created by Psy.C on 2026/4/8.
//
/**
如果字符是 '0'：加 9
如果字符是其他数字（'1'-'9'）：加其数值（s[p] - '0'）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s;
int main() {
    fast;
    cin >> s;
    int cnt = 1;
    for (int p = 1; p < s.size(); ++p)
        cnt += s[p] == '0' ? 9 : s[p] - '0';
    cout << cnt << '\n';
    return 0;
}