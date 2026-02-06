//
// Created by Psy.C on 2026/2/6.
//
/**
时间复杂度：

预处理：O(n log n)（主要是排序）
每次查询：O(1)
总体：O(n log n + m)
空间复杂度：O(n)
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100001
using namespace std;


int main() {
    fast;
    ll n, i, a[N], b[N], sa[N], sb[N]; cin >> n;
    for (i = 1; i <= n; ++i) {
        cin >> a[i];
        sa[i] = sa[i-1] + a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    ll m, s, l, r; cin >> m;
    for (i = 1; i <= n; ++i) sb[i] = sb[i-1] + b[i];
    for (i = 1; i <= m; ++i) {
        cin >> s >> l >> r;
        if (s == 1) cout << sa[r] - sa[l-1];//查询原数组在区间[l,r]的和
        if (s == 2) cout << sb[r] - sb[l-1];
        cout << '\n';
    }
    return 0;
}