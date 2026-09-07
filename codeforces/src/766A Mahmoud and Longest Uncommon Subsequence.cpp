//
// Created by Psy.C on 2026/9/7.
//
/**
strcmp(a, b)：C 风格字符串比较，相等返回 0，a < b 返回负数，a > b 返回正数
strlen 返回字符串长度（不含结尾 '\0'）。
max(...) 取两者较长者。
若两字符串不同，则输出较长字符串的长度，换行
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+5;
char a[N], b[N];
int main() {
    fast;
    cin >> a >> b;
    if (strcmp(a, b) == 0) cout << "-1\n";
    else cout << max(strlen(a), strlen(b)) << '\n';
    return 0;
}