//
// Created by Psy.C on 2026/9/27.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int l, r, x, y, k;
signed main() {
    fast;
    cin >> l >> r >> x >> y >> k;
    int ok = 0;
    for (int i = x; i <= y; ++i)
        if (r >= k*i && l <= k*i) ok = 1;
    if (ok) cout << "YES\n"; else cout << "NO\n";
    return 0;
}