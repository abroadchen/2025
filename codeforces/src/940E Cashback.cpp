//
// Created by Psy.C on 2026/10/18.
//
/**
n：元素个数；c：每组大小；h,t：单调队列的头尾指针；a[N]：原始数组；s[N]：前缀和（s[i]=a[1]+...+a[i]）；q[N]：单调队列（存下标）；dp[N]：DP 数组；mn[N]：记录"以 i 结尾的滑动窗口的最小值"
第一个循环求前缀和 s[i]。
第二个循环是一个固定窗口大小 c 的单调（递增）队列，用来对每个位置 i 求最近 c 个元素中的最小值：
while (h<=t && q[h]+c <= i) q[h++]：把窗口窗口左端滑出的元素（下标 q[h] 距当前 i 已 ≥ c）弹出队头。
while (h<=t && a[q[t]]>=a[i]) q[t--]：维护队头最小的单调队列：把队尾不小于 a[i] 的元素弹出，保证队内从队头到队尾递增（队头即当前窗口最小值）。
q[++t]=i 入队，mn[i] = a[q[h]]：当前窗口 [i-c+1, i] 的最小值存入 mn[i]。
结果：mn[i] = 以 i 结尾、长度为 c 的滑动窗口的最小值。这里用 q[h]+c<=i 弹出，是因为窗口左边界是 i-c+1，当 q[h] <= i-c 即 q[h]+c <= i 时出窗。
第一个循环：i=1..c-1，长度不足一组时，只能一个一个单独处理：dp[i] = dp[i-1]+a[i]（全部单独算，无优惠）。
第二个循环 i=c..n，两种转移取最小值：
dp[i-c] + (s[i]-s[i-c]) - mn[i]：把最后 c 个元素（[i-c+1, i]）作为一组打包。这一组的总和是 s[i]-s[i-c]，若这一组可免掉最小值则减 mn[i]（组内最小值免费）。加上前面 dp[i-c] 的部分。
dp[i-1] + a[i]：第 i 个元素单独处理（不参与打包），继承 dp[i-1] 加上本元素。
输出 dp[n]：最优总代价
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+10;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

ll n, c, h(1), t, a[N], s[N], q[N], dp[N], mn[N];
int main() {
    fast;
    n = rd(), c = rd();
    for (ll i = 1; i <= n; ++i) a[i] = rd(), s[i] = s[i-1] + a[i];
    for (ll i = 1; i <= n; ++i) {
        while (h <= t && q[h] + c <= i) q[h++] = 0;
        while (h <= t && a[q[t]] >= a[i]) q[t--] = 0;
        q[++t] = i, mn[i] = a[q[h]];
    }
    for (ll i = 1; i < c; ++i) dp[i] = dp[i-1] + a[i];
    for (ll i = c; i <= n; ++i)
        dp[i] = min(dp[i-c]+s[i]-s[i-c]-mn[i], dp[i-1]+a[i]);
    cout << dp[n];
    return 0;
}