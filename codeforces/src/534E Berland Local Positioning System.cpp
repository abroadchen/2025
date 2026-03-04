//
// Created by Psy.C on 2026/3/4.
//
/**
a[N]: 原始输入数组
d[N]: 差分数组，d[i] = a[i] - a[i-1]
p[N]: 操作计数数组
d[1] = d[2]: 将d[1]设置为d[2]的值（特殊处理）
读入m个操作位置，统计每个位置的操作次数
p[1] <<= 1; p[n] <<= 1;: 将p[1]和p[n]左移1位（乘以2）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e5+1;

int n;
bool ok(const int *c) {///数组c的所有元素是否都相等
    for (int i = 2; i <= n; ++i)
        if (c[i] != c[i-1]) return false;
    return true;
}

int a[N], d[N], p[N];
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; d[i] = a[i] - a[i-1];
    }
    d[1] = d[2];
    int m; cin >> m;
    for (int i = 1, x; i <= m; ++i) {
        cin >> x; p[x]++;
    }
    p[1] <<= 1; p[n] <<= 1;
    if (ok(p)) {
        if (ok(d)) cout << p[1]*(n-1)*d[1]-d[1] << '\n';
        else cout << "-1\n";
        return 0;
    }
    int ans = 0;
    for (int i = 2; i <= n; ++i)
        ans += d[i]*min(p[i-1], p[i]);///相邻两个位置的最小操作次数与差分值的乘积
    cout << ans << '\n';
    return 0;
}