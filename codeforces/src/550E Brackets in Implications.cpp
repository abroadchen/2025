//
// Created by Psy.C on 2026/3/9.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, a[N], i;
int main() {
    fast;
    cin >> n;
    for (i = 1; i <= n; ++i) cin >> a[i];
    if (n == 1) {
        if (a[1] == 1) cout << "NO\n";
        else cout << "YES\n0";
        return 0;
    }
    if (a[n] == 1) return cout << "NO\n", 0;
    for (i = 1; i <= n-2; ++i) if (a[i] != 1) break;
    if (i == n-1 && a[n-1] == 0 && a[n] == 0)
        return cout << "NO\n", 0;
    cout << "YES\n";
    for (i = 1; i <= n-2; ++i) cout << '(' << a[i] << "->";
    cout << a[n-1];
    for (i = 1; i <= n-2; ++i) cout << ')';
    cout << "->0\n";
    return 0;
}