//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
dp[i][j] = 长度为 i、且有 j 个"相邻相同对"的序列数量
长度 1 的序列，0 个相邻相同对（只有一个元素，自然没有对），可选 m 种值 → 共 m 种
当从长度 i 扩到 i+1，在末尾追加第 i+1 个元素时，分两种：

情况 A（相邻相同）‍：新元素与上一元素相等 → 相同对数量不增（仍是 j）。因为相邻相同只有 1 种取法，所以 dp[i+1][j] += dp[i][j]（系数 1）。
情况 B（相邻不同）‍：新元素 ≠ 上一元素 → 相同对 +1，变成 j+1。可选值有 m-1 种，所以 dp[i+1][j+1] += dp[i][j] * (m-1)
输出长度 n、恰好 k 个相邻相同对的序列数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 2005, mod = 998244353;

int n, m, k, dp[N][N];
signed main() {
    fast;
    cin >> n >> m >> k; dp[1][0] = m;
    for (int i = 1; i < n; ++i)
        for (int j = 0; j <= k; ++j) {
            dp[i+1][j] = (dp[i+1][j] + dp[i][j]) % mod;
            dp[i+1][j+1] = (dp[i][j]*(m-1) + dp[i+1][j+1]) % mod;
        }
    cout << dp[n][k];
    return 0;
}