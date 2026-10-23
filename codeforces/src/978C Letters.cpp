//
// Created by Psy.C on 2026/10/22.
//
/**
读入 n 个 a[i]（各段大小）、m 个 b[i]（全局查询编号，从 1 开始）。
对 a 做原地前缀和：a[i] 变成"前 i+1 段的总大小"，即第 i 段的结束全局编号
lower_bound 在前缀和数组 a 中找到第一个 ≥ b[i] 的下标 p，即 b[i] 落在第 p 段（下标 p，输出时编号为 p+1）。
若 a[p] == b[i]：说明 b[i] 正好是第 p 段的结尾（最后位置），则该段内位置 = a[p] - a[p-1]（即该段总大小）。
否则：该段内位置 = b[i] - a[p-1]（全局编号减去前 p 段的累计数）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define rep(i,n) for(i=0;i<n;i++)
using namespace std;

constexpr int N = 2e5+10;

int n, m, i, a[N], b[N];
signed main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    rep(i,m) cin >> b[i];
    for (i = 1; i < n; i++) a[i] += a[i-1];
    rep(i,m) {
        int p = lower_bound(a, a+n, b[i]) - a;
        cout << p+1 << ' ';
        if (a[p] == b[i]) cout << a[p]-a[p-1] << '\n';
        else cout << b[i]-a[p-1] << '\n';
    }
    return 0;
}