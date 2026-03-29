//
// Created by Psy.C on 2026/3/29.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll C(ll n, int x) {
    ll t = 1;
    for (int i = 1; i <= x; ++i)
        t = t*(n-i+1)/i;
    return t;
}
ll n;
int main() {
    fast;
    cin >> n;
    ll a = C(n, 5) + 4*C(n, 4) + 6*C(n, 3) + 4*C(n, 2) + C(n, 1),
    b = C(n, 3) + 2*C(n, 2) + C(n, 1);
    cout << a*b << '\n';
    return 0;
}