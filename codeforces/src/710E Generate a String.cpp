//
// Created by Psy.C on 2026/4/20.
//
/**
dp[i]表示到达位置i的最小花费
dp[i-1]+x：从i-1位置移动一步到达i的费用
dp[(i+1)/2]+y+x：从(i+1)/2位置双倍后加1到达i的费用（先双倍到i+1，再减1到i，或者理解为从(i+1)/2双倍到i-1再+1到i）
dp[i-1]+x：从i-1位置移动一步到达i的费用
dp[i/2]+y：从i/2位置双倍到达i的费用
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e7+7;
ll dp[N];
int n, x, y;///目标位置、单步移动费用、双倍操作费用
int main() {
    fast;
    cin >> n >> x >> y; dp[1] = x;//从0移动到1需要花费x
    for (int i = 2; i <= n; ++i) {
        if (i&1) dp[i] = min(dp[i-1]+x, dp[(i+1)/2]+y+x);
        else dp[i] = min(dp[i-1]+x, dp[i/2]+y);
    }
    cout << dp[n] << '\n';
    return 0;
}