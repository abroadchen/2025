//
// Created by Psy.C on 2026/2/27.
//
/**
N = 3e4+1：最大数组长度，M = 201：最大分组数
n, m：输入的数组长度和分组数
f[N][M][3][2]：四维DP数组，状态含义稍后解释
num[N]：输入的数值数组
ans[N][2]：辅助DP数组
res：最终结果，初始化为负无穷

f[i][1][0][0]：第i个位置在第1组中选择负号的状态
f[i][1][1][1]：第i个位置在第1组中选择正号的状态
从前面继承状态或从0开始，然后加上当前值（正或负）
f[i][1][2][0]：第i个位置在第1组中处于"已选择负号"的累积状态
f[i][1][2][1]：第i个位置在第1组中处于"已选择正号"的累积状态

[0][0]：当前组选择负号，系数为-2
[1][1]：当前组选择正号，系数为+2
[2][0]/[2][1]：累积状态，表示当前组已选择的符号状态
从后往前计算ans数组
ans[i][0]：从i到n，选择负号的最优值
ans[i][1]：从i到n，选择正号的最优值
遍历可能的分割点i
将前i个元素的最优解与后缀[i+1, n]的最优解合并
考虑不同状态组合的可能情况

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e4+1, M = 201, inf = 0x80808080;
int n, m, f[N][M][3][2], num[N], ans[N][2], res = inf;
int main() {
    fast;
    cin >> n >> m; memset(f, 0x80, sizeof f);
    for (int i = 1; i <= n; ++i) cin >> num[i];
    for (int i = 1; i <= n; ++i) {
        f[i][1][0][0] = max(f[i-1][1][0][0], 0) - num[i];
        f[i][1][1][1] = max(f[i-1][1][1][1], 0) + num[i];
    }
    for (int i = 1; i <= n; ++i) {
        f[i][1][2][0] = max(f[i-1][1][2][0], f[i][1][0][0]);
        f[i][1][2][1] = max(f[i-1][1][2][1], f[i][1][1][1]);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 2; j < m; ++j) {
            f[i][j][0][0] = max({f[i-1][j][0][0], f[i-1][j-1][1][1], f[i-1][j-1][2][1]}) - 2*num[i];
            f[i][j][1][1] = max({f[i-1][j][1][1], f[i-1][j-1][0][0], f[i-1][j-1][2][0]}) + 2*num[i];
            f[i][j][2][0] = max({f[i-1][j][2][0], f[i-1][j-1][2][0], f[i-1][j-1][0][0], f[i-1][j][0][0]});
            f[i][j][2][1] = max({f[i-1][j][2][1], f[i-1][j-1][2][1], f[i-1][j-1][1][1], f[i-1][j][1][1]});
        }
    for (int i = n; i >= 1; --i) {
        ans[i][0] = max(ans[i+1][0], 0) - num[i];
        ans[i][1] = max(ans[i+1][1], 0) + num[i];
    }
    for (int i = m-1; i < n; ++i) {
        res = max(res, max(f[i][m-1][0][0], f[i][m-1][2][0]) + ans[i+1][1]);
        res = max(res, max(f[i][m-1][1][1], f[i][m-1][2][1]) + ans[i+1][0]);
    }
    cout << res << '\n';
    return 0;
}