//
// Created by Psy.C on 2026/4/10.
//
/**
n: 输入数组的大小
a[N]: 输入值数组
dp[N]: 动态规划数组，用于中间计算
ans: 最终答案累加器

对于每个位置i，更新dp[i]使用：
min(a[i], a[i+1]) - 1: 当前元素和下一个元素的最小值减1
(min(a[i], min(a[i-1], a[i+1])) - 1)*dp[i-1]: 三个连续元素最小值减1与前一个DP值的乘积
更新ans通过加上：
a[i] - 1: 当前元素减1
(min(a[i], a[i-1]) - 1)*dp[i-1]: 当前元素和前一元素最小值减1与前一个DP值的乘积

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+5, mod = 1e9+7;
ll n, a[N], dp[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        dp[i] = (min(a[i], a[i+1]) - 1 +
            (min(a[i], min(a[i-1], a[i+1])) - 1)*dp[i-1])%mod;
        ans += a[i] - 1 + (min(a[i], a[i-1]) - 1)*dp[i-1];
        ans %= mod;
    }
    cout << ans;
    return 0;
}