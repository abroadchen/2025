//
// Created by Psy.C on 2026/10/8.
//
/**
依次读入 n 个数，a[x] = i 记录数值 x 在第 i 个位置出现。
mx 记录出现的最大数值
遍历所有出现过的数值 i，选出现位置最早的那个数值 i 作为答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 8e5+5, inf = 1e9;
int n, x, a[N], mn = inf, mx = -inf, ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> x; a[x] = i;
        mx = max(mx, x);
    }
    for (int i = 0; i <= mx; ++i) {
        if (a[i] && a[i] < mn) {
            ans = i;
            mn = a[i];
        }
    }
    cout << ans;
    return 0;
}