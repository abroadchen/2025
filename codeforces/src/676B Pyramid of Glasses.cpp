//
// Created by Psy.C on 2026/4/13.
//
/**
n: 三角形的行数
t: 初始流量
dp[i][j]表示第i行第j列的流量

外层循环：遍历每一行i（从1到n）
内层循环：遍历第i行的每一列j（从1到i）
条件判断：if (dp[i][j] >= 1.)
如果当前位置的流量≥1，说明该位置被"激活"
ans++: 计数器+1，表示有位置被激活
流量传播：
dp[i+1][j] += (dp[i][j]-1)*0.5: 向下方位置传递一半多余流量
dp[i+1][j+1] += (dp[i][j]-1)*0.5: 向右下方位置传递一半多余流量
每个位置只有当流量≥1时才算被激活
超过1的部分（dp[i][j]-1）会平均分配给下一行的两个相邻位置
这模拟了一个液体从顶部往下流动并扩散的过程
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5;
int n, t;
double dp[N][N];
int main() {
    fast;
    cin >> n >> t;
    dp[1][1] = 1.*t;//在第1行第1列放置初始流量t
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            if (dp[i][j] >= 1.) {
                ans++;
                dp[i+1][j] += (dp[i][j]-1)*0.5;
                dp[i+1][j+1] += (dp[i][j]-1)*0.5;
            }
    cout << ans << '\n';
    return 0;
}