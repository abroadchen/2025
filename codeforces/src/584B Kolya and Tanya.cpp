//
// Created by Psy.C on 2026/3/17.
//
/**
时间复杂度：
O(log n)，主要消耗在两次快速幂运算上
空间复杂度：
O(1)，只使用常数个变量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int mod = 1e9+7;
ll ksm(ll n, ll k) {
    ll res = 1;
    while (k) {
        if (k&1) res = res * n % mod;
        n = n * n % mod;
        k >>= 1;
    }
    return res % mod;
}

ll n, m, ans;
int main() {
    fast;
    cin >> n; m = 3*n;
    ans = ksm(3, m);
    ans = (ans + mod - ksm(7, n)) % mod;
    cout << ans << '\n';
    return 0;
}