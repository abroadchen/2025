//
// Created by Psy.C on 2026/4/17.
//
/**
n, m: 网格的行数和列数
num: 网格中'*'的总数
r[i]: 第i行中'*'的数量
c[j]: 第j列中'*'的数量
x, y: 满足条件的坐标
s[][]: 存储网格
用j-1是因为字符串从0开始

t = r[i] + c[j]: 表示第i行和第j列能覆盖的'*'总数
if (s[i][j-1] == '*') t--: 如果交叉点(i,j)是'*'，会被重复计算，所以减1
if (t == num): 如果覆盖的'*'数量等于总数，说明找到了解

预处理：O(n×m)
搜索：O(n×m)
总体：O(n×m)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e4+5;
int n, m, num, r[N], c[N], x, y;
char s[N][N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        for (int j = 1; j <= m; ++j)
            if (s[i][j-1] == '*') {
                num++; r[i]++; c[j]++;
            }
    }
    int ok = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            int t = r[i] + c[j];
            if (s[i][j-1] == '*') t--;
            if (t == num) {
                ok = 1;
                x = i; y = j;
            }
        }
    if (ok) {
        cout << "YES\n";
        cout << x << ' ' << y;
    } else cout << "NO\n";
    return 0;
}