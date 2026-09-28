//
// Created by Psy.C on 2026/9/28.
//
/**
a[]：原始 0/1 数组。
l[]：前缀统计数组，l[i] 表示从第 1 位到第 i 位中 0 的个数。
r[]：后缀统计数组，r[i] 表示从第 i 位到第 n 位中 1 的个数。
ans：最终答案
读入 n 和数组
前缀和：l[i] = l[i-1] + (a[i]==0 ? 1 : 0)，即到 i 为止 0 的累计个数
后缀和：从后往前，r[i] = r[i+1] + (a[i]==1 ? 1 : 0)，即从 i 到 n 中 1 的累计个数
枚举每个切割点 i：把 l[i]（前 i 位里的 0 数）和 r[i]（第 i 位到末尾里的 1 数）相加，取最大值。
输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 110;
int n, a[N], l[N], r[N], ans, i;
int main() {
    fast;
    cin >> n;
    for (i = 1; i <= n; ++i) cin >> a[i];
    for (i = 1; i <= n; ++i) l[i] = l[i-1] + (a[i] == 0);
    for (i = n; i >= 1; --i) r[i] = r[i+1] + (a[i] == 1);
    for (i = 1; i <= n; ++i) ans = max(ans, l[i] + r[i]);
    cout << ans << '\n';
    return 0;
}