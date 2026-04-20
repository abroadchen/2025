//
// Created by Psy.C on 2026/4/19.
//
/**
n, m: 矩阵的行数和列数
s[5]: 用于存储每个像素的颜色值（预留足够空间）
ok = 0: 表示目前只包含黑白灰颜色
ok = 1: 表示发现了其他颜色
遍历n×m矩阵的所有像素
读取当前像素的颜色
检查是否为'W'(白)、'B'(黑)、'G'(灰)之外的颜色
如果是其他颜色，设置ok = 1
ok = 1: 发现了彩色，输出"#Color"
ok = 0: 只有黑白灰，输出"#Black&White"
O(n×m): 遍历整个矩阵一次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m;
char s[5];
int main() {
    fast;
    cin >> n >> m;
    int ok = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            cin >> s;
            if (s[0] != 'W' && s[0] != 'B' && s[0] != 'G')
                ok = 1;
        }
    if (ok) cout << "#Color";
    else cout << "#Black&White";
    return 0;
}