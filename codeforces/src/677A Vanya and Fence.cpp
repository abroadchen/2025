//
// Created by Psy.C on 2026/4/13.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, h, a[1005];
int main() {
    fast;
    cin >> n >> h;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] <= h) ans++;
        else ans += 2;
    }
    cout << ans << '\n';
    return 0;
}