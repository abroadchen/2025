//
// Created by Psy.C on 2026/3/16.
//
/**
从右往左扫描，对于每个位置i，计算右边的最大值

b[i] 的值取决于：

如果 a[i] 是当前最大值，则 b[i] = a[i]
如果 a[i] 等于后面的最大值，则 b[i] = 0
如果 a[i] 小于后面的最大值，则 b[i] = 后面的最大值
输出操作次数：

如果 b[i] == a[i]，不需要操作，输出0
如果 b[i] == 0，需要1次操作，输出1
否则需要 b[i] - a[i] + 1 次操作

时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, a[N], b[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int mx = 0;
    for (int i = n-1; i >= 0; --i) {
        if (a[i] > mx) b[i] = a[i];
        else if (a[i] == mx) b[i] = 0;
        else b[i] = mx;
        mx = max(mx, a[i]);
    }
    for (int i = 0; i < n-1; ++i) {
        if (b[i] == a[i]) cout << "0 ";
        else if (b[i] == 0) cout << "1 ";
        else cout << b[i] - a[i] + 1 << ' ';
    }
    cout << "0\n";
    return 0;
}