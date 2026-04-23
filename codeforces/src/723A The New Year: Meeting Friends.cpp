//
// Created by Psy.C on 2026/4/23.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b, c, mx, mn;
int main() {
    fast;
    cin >> a >> b >> c;
    mx = max(a, b); mx = max(mx, c);
    mn = min(a, b); mn = min(mn, c);
    cout << mx - mn << '\n';
    return 0;
}