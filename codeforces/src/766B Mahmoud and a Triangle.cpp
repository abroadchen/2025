//
// Created by Psy.C on 2026/9/7.
//
/**
取最大的两个元素之差 a[n] - a[n-1] 赋给 d。
由于已升序，a[n] 最大、a[n-1] 次大。
这里 d 的初始含义是"当前相邻差值"，初始为最后两个相邻元素之差
从 i = n-2 一直向前扫到 i = 1，维护"当前相邻差的最小值" d：
检查：若 d < a[i]，输出 "YES" 并直接结束。
更新：d = min(d, a[i+1] - a[i])，即把当前最小相邻差与新的相邻差 a[i+1]-a[i] 取较小者。
循环结束仍未触发 YES，则输出 "NO"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    int d = a[n] - a[n-1];
    for (int i = n-2; i >= 1; --i) {
        if (d < a[i]) { puts("YES"); return 0; }
        d = min(d, a[i+1] - a[i]);
    }
    puts("NO");
    return 0;
}