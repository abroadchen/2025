//
// Created by Psy.C on 2026/3/13.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, m, k, t, a[N], b[N];
int main() {
    fast;
    cin >> n >> m >> k >> t;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> b[i];
    if (a[k] < b[m-t+1]) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}