//
// Created by Psy.C on 2026/2/27.
//
/**
0x80808080 = -2130706432  // 本题使用
0x3f3f3f3f = 1061109567   // 常用"无穷大"值
0xc0c0c0c0 = -1061109568  // 对应的"无穷小"值
0x7fffffff = 2147483647   // int最大值
0x80000000 = -2147483648  // int最小值

n：数组长度
K：分组数
a[N]：输入的数值数组
dp[N][M][4]：三维DP数组，第三个维度表示4种状态
cnt：当前分组的系数，首尾分组系数为1，中间分组系数为2
dp[i][j][0]：第i个位置在第j组选择负号的最大值
dp[i][j][1]：第i个位置在第j组不选择正号（累积负号状态）的最大值
dp[i][j][2]：第i个位置在第j组选择正号的最大值
dp[i][j][3]：第i个位置在第j组不选择负号（累积正号状态）的最大值
当当前分组系数为2（中间分组）时，允许从前一分组的对应状态转移过来
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e4+1, M = 201;
int n, K, a[N], dp[N][M][4];
int main() {
    fast;
    cin >> n >> K;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    memset(dp, 0xc0, sizeof(dp));
    for (int i = 0; i <= n; ++i)
        for (int k = 0; k < 4; ++k)
            dp[i][0][k] = 0;//0个分组时所有状态值为0
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= K; ++j) {
            const int cnt = j == 1 || j == K ? 1 : 2;
            dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j-1][3]) - cnt*a[i];
            dp[i][j][1] = max(dp[i-1][j][1], dp[i][j][0]);
            dp[i][j][2] = max(dp[i-1][j][2], dp[i-1][j-1][1]) + cnt*a[i];
            dp[i][j][3] = max(dp[i-1][j][3], dp[i][j][2]);
            if (cnt == 2) {
                dp[i][j][1] = max(dp[i][j][1], dp[i-1][j-1][1]);
                dp[i][j][3] = max(dp[i][j][3], dp[i-1][j-1][3]);
            }
        }
    cout << max(dp[n][K][1], dp[n][K][3]) << '\n';
    return 0;
}