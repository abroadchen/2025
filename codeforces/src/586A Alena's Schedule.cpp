//
// Created by Psy.C on 2026/3/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101;
int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] == 1) ans++;
        if (a[i-1] == 1 && a[i] == 0 && a[i+1] == 1) ans++;
    }
    cout << ans;
    return 0;
}