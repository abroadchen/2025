//
// Created by Psy.C on 2026/4/21.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll l1, r1, l2, r2, k;
int main() {
    fast;
    cin >> l1 >> r1 >> l2 >> r2 >> k;
    ll r = min(r1, r2), l = max(l1, l2), ans = 0;
    if (l <= r) ans = r - l + 1;
    if (k <= r && k >= l) ans -= 1;
    cout << ans << '\n';
    return 0;
}