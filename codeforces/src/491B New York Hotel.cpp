//
// Created by Psy.C on 2026/2/19.
//
///时间复杂度为O(n+m)
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 50, inf1 = 1e9+7, inf2 = 2e9+7;
int u, v, n, x[N], l, r, m;
int main() {
    fast;
    cin >> u >> v >> n;
    for (int i = 1; i <= 4; ++i) x[i] = -inf1;
    for (int i = 1; i <= n; ++i) {
        cin >> l >> r;
        x[1] = max(x[1], -l-r); x[2] = max(x[2], l-r);
        x[3] = max(x[3], l+r); x[4] = max(x[4], -l+r);
    }
    cin >> m;
    int ans = inf2, p = 0;
    for (int i = 1; i <= m; ++i) {
        cin >> l >> r;
        int sum = 0;
        sum = max(sum, x[1] + l + r);
        sum = max(sum, x[2] - l + r);
        sum = max(sum, x[3] - l - r);
        sum = max(sum, x[4] + l - r);
        if (sum < ans) { ans = sum; p = i; }
    }
    cout << ans << '\n' << p << '\n';
    return 0;
}