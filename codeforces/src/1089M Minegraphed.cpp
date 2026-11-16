//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
b[层][行][列]，三层，每层 3n×3n，初始全部为 #
拆解 (a)：

b[0][i*3][j] = '.'：把第 0 层的第 i*3 行整行（所有列）都置为 .。
b[2][j][i*3] = '.'：把第 2 层的第 i*3 列整列（所有行 j）置为 .。
注意这里用 j 遍历所有行。
b[1][i*3][i*3+1]、b[1][i*3+1][i*3+1]、b[2][i*3+1][i*3+1] 各置 .：打通第 1、2 层里位于对角线附近的三格。
拆解 (b)：

输入一行 n 个数（0/1）。
若第 j 个为 1（ok），则把三层的 [j*3+1][i*3+1] 处都置为 .。
即"第 i 行、第 j 列"这个交叉点在三维立方体里的对应格被打通——相当于在三维网格中"根据矩阵 1 的位置开洞"。
拆解 (c)：

b[0][i*3][n*3-1] = i + '1'：把第 0 层最后一列的字符设为 字符(i+1)，用于把 '1','2',… 标到最右列，作为层内第 i 行的行号标签（供阅读用）。

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; ++i)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    vector b(3,vector(n*3, string(n*3,'#')));
    rep(i,n) {
        rep(j,n*3) b[0][i*3][j] = b[2][j][i*3] = '.';
        b[1][i*3][i*3+1] = b[1][i*3+1][i*3+1] = b[2][i*3+1][i*3+1] = '.';
        rep(j,n) {
            int ok; cin >> ok;
            if (ok) rep(k,3) b[k][j*3+1][i*3+1] = '.';
        }
        b[0][i*3][n*3-1] = i + '1';
    }
    cout << n*3 << ' ' << n*3 << ' ' << 3 << '\n';
    for (int i = 2; ~i; --i) {
        rep(j,n*3) cout << b[i][j] << '\n';
        if (i) cout << '\n';
    }
    return 0;
}