//
// Created by Psy.C on 2026/3/13.
//
/**
f[i-1]+1: 从前一个位置转移过来，值增加1
a[i]-1: 当前位置的值减1
min(a[i-1], a[i+1]): 取相邻两个元素的最小值
从后往前更新f[i]，确保f[i]考虑了来自右侧的影响
取原来的f[i]和f[i+1]+1（从右边转移过来）的最小值
遍历所有中间位置，找出最大的f[i]值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5 + 5;

int n, a[N], f[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 2; i <= n-1; ++i)
        f[i] = min(f[i-1]+1, min(a[i]-1, min(a[i-1], a[i+1])));
    for (int i = n-1; i >= 2; --i)
        f[i] = min(f[i], f[i+1] + 1);
    for (int i = 2; i <= n-1; ++i)
        ans = max(ans, f[i]);
    cout << ans + 1;
    return 0;
}