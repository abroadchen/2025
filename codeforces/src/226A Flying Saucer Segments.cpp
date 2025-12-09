//
// Created by Psy.C on 2025/12/9.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll f(ll a, ll b, const ll m) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % m;
        a = a * a % m;
        b >>= 1;
    }
    return res - 1;//(a^b - 1) mod m
}


int main() {
    fast;
    ll n, m; cin >> n >> m;
    cout << (f(3, n, m) + m) % m << '\n';
    return 0;
}