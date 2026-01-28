//
// Created by Psy.C on 2026/1/28.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 123456
#define rep(i,n) for (int i = 0; i < n; ++i)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    ll a[N], b[N], ans = 0;
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> b[i];
    rep(i,n) {
        if (a[i]<<1 < b[i] || b[i] == 1) ans -= 1; else {
            if (b[i] % 2 == 0) ans += b[i] * b[i] / 4;
            else ans += b[i]/2 * (b[i]/2+1);
        }
    }
    cout << ans << '\n';
    return 0;
}