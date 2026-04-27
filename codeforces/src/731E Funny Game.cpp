//
// Created by Psy.C on 2026/4/26.
//
/**
N: 数组最大长度
n: 输入序列长度
a[N]: 输入数组
sum[N]: 前缀和数组
dp[i][0]: 从位置i开始的某种状态下的最大值
dp[i][1]: 从位置i开始的另一种状态下的最小值
mx: 当前最大的dp[i][1] + sum[i]值
mn: 当前最小的dp[i][0] - sum[i]值
设置边界条件：对于最后一个位置，两种状态的值都为0
初始化mx和mn：mx = 0 + sum[n], mn = 0 - sum[n]
从后往前遍历每个位置
dp[i][0] = mx: 状态0取当前最大值
dp[i][1] = mn: 状态1取当前最小值
更新mn: 维护最小的dp[i][0] - sum[i]值
更新mx: 维护最大的dp[i][1] + sum[i]值
输出从位置1开始的最优解
时间复杂度是O(n)，空间复杂度也是O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+7;
int n, a[N];
ll sum[N], dp[N][2], mx, mn;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) sum[i] = sum[i-1] + a[i];
    dp[n][0] = dp[n][1] = 0;
    mx = dp[n][1] + sum[n], mn = dp[n][0] - sum[n];
    for (int i = n-1; i >= 1; --i) {
        dp[i][0] = mx; dp[i][1] = mn;
        if (dp[i][0] - sum[i] < mn)
            mn = dp[i][0] - sum[i];
        if (dp[i][1] + sum[i] > mx)
            mx = dp[i][1] + sum[i];
    }
    cout << dp[1][0] << '\n';
    return 0;
}