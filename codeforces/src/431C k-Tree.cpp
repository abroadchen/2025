//
// Created by Psy.C on 2026/2/5.
//
/**
* n: 总和目标值
k: 可选数字的最大值（1到k）
d: 特殊数字的最小值（至少使用一次≥d的数字）
*dp[i][1] = 使用小于d的数字组成i的方法数
dp[i][2] = 使用至少一个大于等于d的数字组成i的方法数
 *
*i: 当前要组成的和（从1到n）
j: 当前使用的数字（从1到min(k,i)）
p = i - j: 剩余需要组成的和
used: 标记当前数字j是否≥d
 *当前数字j < d时，继承之前只用小于d数字的方案
 *
*当p == 0时（只剩当前数字j）：
dp[i][1]++: 如果j < d，增加一个方案
if (used) dp[i][2]++: 如果j ≥ d，增加到包含≥d数字的方案
当p != 0时（还需要之前的数字组合）：
if (used) dp[i][2] += dp[p][1]: 当前j ≥ d，加上之前只用<d数字的方案
else dp[i][2] += dp[p][2]: 当前j < d，加上之前已含≥d数字的方案
 *
 *输出使用至少一个≥d数字组成n的方案数
 *时间复杂度：O(n×k)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define mod 1000000007
using namespace std;


int main() {
    fast;
    ll n, k, d, dp[105][3]{}; cin >> n >> k >> d;
    for (ll i = 1; i <= n; ++i) for (ll j = 1, p; j <= k && j <= i; ++j) {
        p = i - j; bool used = false;
        if (j >= d) used = true;
        dp[i][1] += dp[p][1];
        if (p == 0) {
            dp[i][1]++;
            if (used) dp[i][2]++;
        } else {
            if (used) dp[i][2] += dp[p][1];
            else dp[i][2] += dp[p][2];
        }
        dp[i][1] %= mod; dp[i][2] %= mod;
    }
    cout << dp[n][2] % mod;
    return 0;
}