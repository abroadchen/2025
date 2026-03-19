//
// Created by Psy.C on 2026/3/20.
//
/**
a[i][(j<<1)-1]：第i行的第(2j-1)列（奇数列）
a[i][j<<1]：第i行的第(2j)列（偶数列）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 100;
int n, m, a[N+5][N<<1|5];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m<<1; ++j)
            cin >> a[i][j];
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)//遍历前m对列
            if (a[i][(j<<1)-1] == 1 || a[i][j<<1] == 1)//如果这一对列中任意一个是1
                cnt++;
    cout << cnt << '\n';
    return 0;
}