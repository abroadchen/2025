//
// Created by Psy.C on 2026/2/18.
//
/**
a[5][N]: 二维数组，a[type][index]存储第type种数字的第index个出现位置
c[N]: 计数数组，c[i]记录第i种数字出现的次数

时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5001, M = 5;
int n, a[5][N], c[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        a[x][++c[x]] = i;
    }
    for (int i = 1; i <= 3; ++i) n = min(n, c[i]);
    cout << n << '\n';
    for (int i = 1; i <= n; ++i)
        cout << a[1][i] << ' ' << a[2][i] << ' ' << a[3][i] << '\n';
    return 0;
}