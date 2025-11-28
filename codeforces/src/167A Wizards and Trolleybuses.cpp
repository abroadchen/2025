//
// Created by Psy.C on 2025/11/28.
//

#include <iomanip>
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;

int main() {
    fast;
    ll n, a, d; cin >> n >> a >> d;
    double y(-1), x(0);
    while (n--) {
        ll t, v; cin >> t >> v;
        const auto td = static_cast<double>(t),
        vd = static_cast<double>(v),
        ad = static_cast<double>(a),
        dd = static_cast<double>(d);
        if (2 * d * a > v * v) x = 0.5 * vd / ad + 1. * dd / vd;
        else x = sqrt(2. * dd / ad);
        x += td;
        y = y > x ? y : x;
        cout << fixed << setprecision(5) << y << '\n';
    }
    return 0;
}