//
// Created by Psy.C on 2026/10/22.
//
/**
读入 w（宽度/总元素数）和 l（窗口长度）。
a[i] 读入后累加前一项，变成前缀和数组（a[i] 表示前 i 项之和，a[0]=0）
用前缀和 a[i]-a[i-l] 求"以 i 结尾、长度为 l 的子段和"，即每个窗口的和。
取所有窗口和的最小值输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+2;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int w, l, a[N], ans(INT_MAX);
int main() {
    fast;
    w = rd(), l = rd();
    for (int i = 1; i < w; ++i) a[i] = rd(), a[i] += a[i-1];
    for (int i = l; i < w; ++i) ans = min(ans, a[i]-a[i-l]);
    cout << ans << '\n';
    return 0;
}