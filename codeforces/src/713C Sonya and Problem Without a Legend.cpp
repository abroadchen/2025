//
// Created by Psy.C on 2026/4/21.
//
/**
对于第1个位置，枚举所有可能的值b[i]
dp[1][i]表示前1个元素，且第1个元素变成b[i]时的最小代价
使用前缀最小值优化：min(dp[1][i-1], ...)确保当前最优解
外层循环：处理第2到第n个位置
内层循环：枚举当前位置可能的值
状态转移：dp[i][j] = min(前缀最小值, 从前一行转移过来的值)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3007;
int n;
ll a[N], b[N], dp[N][N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; a[i] -= i; b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    int x = unique(b + 1, b + n + 1) - b - 1;//去重后有效元素的数量
    memset(dp, 127, sizeof dp);
    for (int i = 1; i <= x; ++i)
        dp[1][i] = min(dp[1][i-1], abs(a[1] - b[i]));
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= x; ++j)
            dp[i][j] = min(dp[i][j-1], dp[i-1][j]+abs(a[i]-b[j]));
    cout << dp[n][x] << '\n';
    return 0;
}