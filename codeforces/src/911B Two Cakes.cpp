//
// Created by Psy.C on 2026/10/12.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a, b;
int main() {
    fast;
    cin >> n >> a >> b;
    if (a > b) swap(a, b);
    int ans = 0;
    for (int i = 1; i <= a; ++i)
        if (a/i + b/i >= n) ans = max(i, ans);
    cout << ans << '\n';
    return 0;
}