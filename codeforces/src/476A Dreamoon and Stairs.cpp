//
// Created by Psy.C on 2026/2/15.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m, ans;

int main() {
    fast;
    cin >> n >> m;
    while (ans < n/2 + n%2) ans += m;
    if (ans > n) ans = -1;
    cout << ans << '\n';
    return 0;
}