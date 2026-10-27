//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e4+1, inf = 0x3f3f3f3f;
int n, b[N];
int main() {
    fast;
    while (cin >> n) {
        int mx = -inf;
        memset(b, 0, sizeof b);
        for (int i = 1, x; i <= n; i++) {
            cin >> x;
            b[x]++;
            mx = max(mx, b[x]);
        }
        cout << mx << '\n';
    }
    return 0;
}