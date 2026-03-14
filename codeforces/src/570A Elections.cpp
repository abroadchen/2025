//
// Created by Psy.C on 2026/3/13.
//
/**
m：列数
n：行数
a[N][N]：二维数组，存储n×m的矩阵
b[N]：计数数组，记录每列最大值出现次数

对每行进行处理：
初始化mx=1（当前行最大值的列索引）
遍历当前行的所有元素，找到最大值的列索引
b[mx]++：将该列的最大值位置计数加1
初始化ans=1
遍历所有列，找到计数值最大的列索引

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 105;
int m, n, a[N][N], b[N];
int main() {
    fast;
    cin >> m >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) cin >> a[i][j];
    int mx = 1;
    for (int i = 1; i <= n; ++i) {
        mx = 1;
        for (int j = 1; j <= m; ++j)
            if (a[i][j] > a[i][mx]) mx = j;
        b[mx]++;
    }
    int ans = 1;
    for (int i = 1; i <= m; ++i)
        if (b[i] > b[ans]) ans = i;
    cout << ans << '\n';
    return 0;
}