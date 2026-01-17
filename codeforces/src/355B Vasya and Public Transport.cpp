//
// Created by Psy.C on 2026/1/17.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1234
#define rep(i,n) for (int i = 0; i < n; ++i)
using namespace std;


int main() {
    fast;
    int c1, c2, c3, c4; cin >> c1 >> c2 >> c3 >> c4;
    int n, m, a[N], b[N]; cin >> n >> m;
    rep(i,n) cin >> a[i];
    rep(i,m) cin >> b[i];
    int bus = 0, tr = 0;
    rep(i,n) bus += min(c1 * a[i], c2);
    bus = min(bus, c3);
    rep(i,m) tr += min(c1 * b[i], c2);
    tr = min(tr, c3);
    cout << min(bus + tr, c4) << '\n';
    return 0;
}