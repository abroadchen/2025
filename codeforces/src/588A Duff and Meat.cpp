//
// Created by Psy.C on 2026/3/18.
//
/**
n: 商品数量
a[i]: 第i个商品的需求量
p[i]: 第i个商品的价格
dp[i]: 前i个商品中价格的最小值
第1个商品的最低价格就是它自己的价格
从第2个开始，dp[i] = min(dp[i-1], p[i])
对于每个商品i，用其需求量a[i]乘以前i个商品的最低价格dp[i]
累加得到总成本
时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
int n, a[N], p[N], dp[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> p[i];
        if (i == 1) dp[i] = p[i];
        else dp[i] = min(dp[i-1], p[i]);
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += a[i] * dp[i];
    cout << ans << '\n';
    return 0;
}