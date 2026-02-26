//
// Created by Psy.C on 2026/2/26.
//
///时间复杂度O(n²)，空间复杂度O(n²)。答案是第n行第n列的值，即C(2n-2, n-1)
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a[11][11];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= 1; ++i)
        for (int j = 1; j <= n; ++j)
            a[i][j] = 1;//从起点到第一行任意位置只有一种走法
    for (int i = 2; i <= n; ++i) {
        a[i][1] = 1;//从起点到第一列任意位置只有一种走法
        for (int j = 2; j <= n; ++j)
            a[i][j] = a[i-1][j] + a[i][j-1];//从上方来的路径数 + 从左方来的路径数
    }
    cout << a[n][n] << '\n';
    return 0;
}