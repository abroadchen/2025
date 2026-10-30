//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+5;

int n, m, l, r, ans;
bool v[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) {
        cin >> l >> r;
        for (int j = l; j <= r; j++) v[j] = 1;
    }
    rep(i,m) if (!v[i]) ans++;
    cout << ans << '\n';
    rep(i,m) if (!v[i]) cout << i << ' ';
    return 0;
}