//
// Created by Psy.C on 2026/1/14.
//
///O(n)，只需遍历数组一次
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    ll tot = 0, mn = 0;
    for (int i = 0, t; i < n; ++i) {
        cin >> t;
        tot += t;//所有数的总和
        if (t > mn) mn = t;//所有数中的最大值
    }
    ll ans = tot / (n - 1);
    if (tot % (n - 1) > 0) ++ans;//如果有余数，向上取整
    if (ans < mn) ans = mn;//结果小于最大值，取最大值
    cout << ans << '\n';
    return 0;
}