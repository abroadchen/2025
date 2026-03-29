//
// Created by Psy.C on 2026/3/29.
//
/**
分子逐步乘以 (n-m), (n-m+1), ..., (n-1), n，分母逐步除以 1, 2, ..., m
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll C(ll n, ll m) {
    if (m > n - m) m = n - m;
    ll ans = 1;
    for (ll i = 0; i < m; ++i)
        ans = ans*(n-i)/(i+1);
    return ans;
}

ll n, ans;
int main() {
    fast;
    cin >> n;
    for (ll i = 5; i <= 7; ++i) ans += C(n, i);
    cout << ans << '\n';
    return 0;
}