//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;


signed main() {
    fast;
    int q; cin >> q;
    while (q--) {
        int k, x; cin >> k >> x;
        cout << (k-1)*9+x << '\n';
    }
    return 0;
}