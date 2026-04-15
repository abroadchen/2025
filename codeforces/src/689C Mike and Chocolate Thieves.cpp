//
// Created by Psy.C on 2026/4/15.
//
/**
m：目标完美立方数个数
初始化：mn=-1（找不到时的返回值），搜索范围[1, 2^60]
二分搜索：
mid：当前检查的中间值
计算ans：计算1到mid范围内完美立方数的个数
循环条件：k从2开始直到k³ ≤ mid
统计：mid/(k*k*k) 表示在1到mid中有多少个k³的倍数
累加：所有完美立方数（及其倍数）的总数
ans == m：找到可能解，记录为mn
ans >= m：当前值太大，缩小右边界
ans < m：当前值太小，增大左边界
时间复杂度：O(log(2^60) × √m) ≈ O(60√m)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll m;
int main() {
    fast;
    cin >> m;
    ll ans, mn = -1, l = 1, r = 1ll<<60;
    while (l <= r) {
        ll mid = (l + r) / 2; ans = 0;
        for (ll k = 2; k*k*k <= mid; ++k)
            ans += mid/(k*k*k);
        if (ans == m) mn = mid;
        if (ans >= m) r = mid - 1; else l = mid + 1;
    }
    cout << mn << '\n';
    return 0;
}