//
// Created by Psy.C on 2026/9/15.
//
/**
读入 n（要检查的数的个数），ans 初始化为 0。
循环 n 次，每次读入一个数 t，判断是否满足 t > l && t < r——即 严格位于 (l, r) 开区间内，是则 ans++
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int p, l, r; cin >> p >> l >> r;
    int n, ans(0); cin >> n;
    for (int i = 0, t; i < n; ++i) {
        cin >> t;
        if (t > l && t < r) ans++;
    }
    cout << ans << '\n';
    return 0;
}