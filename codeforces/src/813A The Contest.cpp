//
// Created by Psy.C on 2026/9/21.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m, sum(0), l, r, x;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) { cin >> x; sum += x; }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> l >> r;
        if (r >= sum) { cout << max(l, sum) << '\n'; return 0; }
    }
    cout << -1 << '\n';
    return 0;
}