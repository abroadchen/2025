//
// Created by Psy.C on 2026/9/19.
//
/**
a[]：原始序列（含 0 与 1）。
f[]：从左往右，到左边最近 0 的距离。
g[]：从右往左，到右边最近 0 的距离
f[0]=inf：左边哨兵设为极大值，处理"前面没有 0"的情况。
若 a[i]==0 → f[i]=0（当前位置就是 0，距离 0）；
否则 f[i] = f[i-1] + 1（沿用上一个累加距离 +1）。
这给出每个位置到其左侧最近 0 的距离
对称地，每个位置到其右侧最近 0 的距离
每个位置到最近 0 的距离 = min(左边距离, 右边距离)。
输出整个序列
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+5, inf = 0x3f3f3f3f;
int n, a[N], f[N], g[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    f[0] = inf, g[n+1] = inf;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == 0) f[i] = 0;
        else f[i] = f[i-1] + 1;
    }
    for (int i = n; i; --i) {
        if (a[i] == 0) g[i] = 0;
        else g[i] = g[i+1] + 1;
    }
    for (int i = 1; i <= n; ++i)
        cout << min(f[i], g[i]) << ' ';
    return 0;
}