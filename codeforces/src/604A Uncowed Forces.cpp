//
// Created by Psy.C on 2026/3/22.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5;
int m[N], w[N], p, q;
int main() {
    fast;
    for (int i = 0; i < N; ++i) cin >> m[i];
    for (int i = 0; i < N; ++i) cin >> w[i];
    cin >> p >> q;
    double ans = 0;
    for (int i = 0; i < N; ++i) {
        double x = 500. * (i + 1);
        ans += max(0.3*x, (1 - 1.*m[i]/250.)*x - 50*1.*w[i]);
    }
    ans = ans + 100*p - 50*q;
    cout << ans << '\n';
    return 0;
}