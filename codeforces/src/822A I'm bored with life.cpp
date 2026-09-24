//
// Created by Psy.C on 2026/9/23.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    if (n > m) { int t = n; n = m; m = t; }
    ll ans = 1;
    for (ll i = 1; i <= n; ++i) ans *= i;
    cout << ans << '\n';
    return 0;
}