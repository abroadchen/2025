//
// Created by Psy.C on 2026/4/20.
//
/**
n: 点的数量
x: 起始位置
a[N]: 点的坐标数组
如果只有一个点，不需要移动，距离为0
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+7;
int n, x, a[N];
int main() {
    fast;
    cin >> n >> x;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    if (n == 1) return cout << "0\n", 0;
    int d1 = min(abs(x - a[2]) + abs(a[n] - a[2]), abs(x - a[n]) + abs(a[n] - a[2])),
    d2 = min(abs(x - a[1]) + abs(a[n-1] - a[1]), abs(x - a[n-1]) + abs(a[n-1] - a[1]));
    cout << min(d1, d2) << '\n';
    return 0;
}