//
// Created by Psy.C on 2026/9/30.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int mx, mn;
int main() {
    fast;
    int n, k; cin >> n >> k;
    if (k*2 <= n-k) mx = k*2; else mx = n-k;
    if (n == k || k == 0) mn = 0; else mn = 1;
    cout << mn << ' ' << mx << '\n';
    return 0;
}