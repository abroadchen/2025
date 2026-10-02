//
// Created by Psy.C on 2026/10/2.
//
/**
决策 A（不取 a[i]）‍：直接转入 [i+1..n] 状态，本轮（或这个元素）的归属按对方先手算 → 值 dp[i+1]。
决策 B（取 a[i]）‍：当前玩家先拿走 a[i]，剩下 [i+1..n] 由对方先手处理，对方得 dp[i+1]，自己在该段得 sum - dp[i+1]，再加回自己已拿的 a[i] → 值 sum - dp[i+1] + a[i]。
等价化简：因为更新后 sum = a[i..n]，所以 sum - dp[i+1] + a[i] = sum_new - dp[i+1]，也就是 max(dp[i+1], sum_new - dp[i+1])。
取两者中较大者，即当前玩家总是选让自己得分更高的策略。
边界

dp[n] = a[n]，sum = a[n]：只剩一个数 a[n]，轮到的人直接拿走。

输出

dp[1]：先手玩家最终得到的最大值。
sum - dp[1]：总分数 sum（全序列和）减去先手得分 = 后手玩家得分。
两者之和恰等于整个数组总和，符合"分数守恒"。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 55;
int a[N], dp[N], sum;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    dp[n] = a[n]; sum = a[n];
    for (int i = n-1; i >= 1; --i) {
        dp[i] = max(dp[i+1], sum-dp[i+1]+a[i]);
        sum += a[i];
    }
    cout << sum-dp[1] << ' ' << dp[1];
    return 0;
}