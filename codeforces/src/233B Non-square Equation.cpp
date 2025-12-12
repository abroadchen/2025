//
// Created by Psy.C on 2025/12/12.
//

#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll f(ll k) {
    ll res = 0;
    while (k) { res += k % 10; k /= 10; }
    return res;
}


int main() {
    fast;
    ll n; cin>>n;
    ll x = static_cast<ll>(sqrt(n));
    while (x * x + 90 * x >= n) {
        if (x * x + f(x) * x == n) {
            cout << x << '\n';
            return 0;
        }
        x--;
    }
    cout << "-1" << '\n';
    return 0;
}