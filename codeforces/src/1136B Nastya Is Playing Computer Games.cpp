//
// Created by Psy.C on 2026/11/26.
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
    int n, k; cin >> n >> k;
    cout << 3*n+min(n-k,k-1);
    return 0;
}