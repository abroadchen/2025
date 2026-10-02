//
// Created by Psy.C on 2026/10/1.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    fast;
    ll n, k, m = 1; cin >> n >> k;
    while (k--) m *= 10;
    cout << n*m/gcd(n, m) << '\n';
    return 0;
}