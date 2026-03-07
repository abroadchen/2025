//
// Created by Psy.C on 2026/3/7.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a[105], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1, x; j <= n; ++j) {
            cin >> x;
            if (x == 1) a[i] = 1;
            if (x == 2) a[j] = 1;
            if (x == 3) a[i] = a[j] = 1;
        }
    for (int i = 1; i <= n; ++i) if (!a[i]) ans++;
    cout << ans << '\n';
    for (int i = 1; i <= n; ++i) if (!a[i]) cout << i << ' ';
    cout << '\n';
    return 0;
}