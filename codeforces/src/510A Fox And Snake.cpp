//
// Created by Psy.C on 2026/2/27.
//
/**
n, m：网格的尺寸（行和列）
a[N][N]：存储图案的网格
用'.'（点字符）初始化整个网格
对于所有奇数编号的行（i&1为真），用'#'（井号字符）填充所有单元格
这意味着第1、3、5等行完全填满'#'
对于偶数编号的行（!(i&1)为真），应用特殊规则：
计算d = i/2（行号的一半）
如果d是奇数，则在最后一列放置'#'（a[i][m] = '#'）
如果d是偶数，则在第一列放置'#'（a[i][1] = '#'）
逐行打印完整的网格
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 51;
int n, m;
char a[N][N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            a[i][j] = '.';
    for (int i = 1; i <= n; ++i) if (i&1)
        for (int j = 1; j <= m; ++j)
            a[i][j] = '#';
    for (int i = 1; i <= n; ++i) if (!(i&1)) {
        if (const int d = i/2; d&1) a[i][m] = '#';
        else a[i][1] = '#';
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cout << a[i][j];
        cout << '\n';
    }
    return 0;
}