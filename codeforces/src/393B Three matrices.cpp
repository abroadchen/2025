//
// Created by Psy.C on 2026/1/29.
//

#include <iomanip>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; ++i)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    vector a(n, vector(n, 0));
    rep(i,n) rep(j,n) cin >> a[i][j];
    rep(i,n) {
        rep(j,n) cout << setprecision(5) << 0.5 * (a[i][j]+a[j][i]) << ' ';
        cout << '\n';
    }
    rep(i,n) {
        rep(j,n) cout << setprecision(5) << 0.5 * (a[i][j]-a[j][i]) << ' ';
        cout << '\n';
    }
    return 0;
}