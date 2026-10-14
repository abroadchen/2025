//
// Created by Psy.C on 2026/10/14.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+10;

int f[N], v[N], n;
int main() {
    fast;
    f[1] = 1, f[2] = 1; v[1] = 1;
    for (int i = 3; i <= 20; ++i)
        f[i] = f[i-1] + f[i-2], v[f[i]] = 1;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            if (v[i] == 1) cout << "O";
            else cout << "o";
        }
        cout << '\n';
    }
    return 0;
}