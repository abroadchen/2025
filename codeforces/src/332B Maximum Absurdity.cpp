//
// Created by Psy.C on 2026/1/10.
//
/**
 * pre[i] = a[1] + a[2] + ... + a[i]
 * dp[i] 表示在 [1, i] 范围内长度为 k 的最大子数组和
 * ind[i] 记录达到最大和的子数组起始位置
 * 在前 k 个元素中，唯一的长度为 k 的子数组和就是 pre[k]
 * ind[k] = 1：这个子数组从位置1开始
 *
*从 k+1 开始遍历到 n
pre[i] - pre[i-k]：计算位置 [i-k+1, i] 的长度为 k 的子数组和
dp[i-1]：在 [1, i-1] 范围内的最优解
如果当前子数组和更大：
dp[i] = pre[i] - pre[i-k]：更新最优值
ind[i] = i - k + 1：记录起始位置
否则继承之前的最优解
 *
 *最大和初始化为最小值（用于寻找最大值）
 *
 *从 2*k 开始，确保能放下两个长度为 k 的子数组
*dp[i-k]：在 [1, i-k] 范围内长度为 k 的最大子数组和
pre[i] - pre[i-k]：在 [i-k+1, i] 范围内长度为 k 的子数组和
两者相加就是两个不重叠子数组的总和
sum = ...：更新最大和
ind1 = ind[i-k]：第一个子数组的起始位置
ind2 = i - k + 1：第二个子数组的起始位置
 *
*时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n, k; cin >> n >> k;
    vector<ll> a(n+1), pre(n+1); pre[0] = 0;
    for (ll i = 1; i <= n; ++i) cin >> a[i], pre[i] = pre[i-1] + a[i];
    vector<ll> dp(n+1), ind(n+1); dp[k] = pre[k]; ind[k] = 1;
    for (ll i = k + 1; i <= n; ++i) {
        if (pre[i] - pre[i-k] > dp[i-1]) {
            dp[i] = pre[i] - pre[i-k];
            ind[i] = i - k + 1;
        } else {
            dp[i] = dp[i-1];
            ind[i] = ind[i-1];
        }
    }
    ll sum = LLONG_MIN, ind1 = 0, ind2 = 0;
    for (ll i = 2 * k; i <= n; ++i) if (dp[i-k] + pre[i] - pre[i-k] > sum) {
        sum = dp[i-k] + pre[i] - pre[i-k];
        ind1 = ind[i-k];
        ind2 = i - k + 1;
    }
    cout << ind1 << ' ' << ind2;
    return 0;
}