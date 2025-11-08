//
// Created by Psy.C on 2025/9/14.
//

#include <cstdio>
#include <iosfwd>
#include <iostream>
using namespace std;

#define LL long long
int n, m;
bool g[55][55];
LL dp[20][600000], ans = 0;

int lowbit(int x) { return x & -x; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u][v] = g[v][u] = 1;
    }
    for (int i = 0; i < n; ++i) dp[i][1 << i] = 1;
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            if (((i >> j) & 1) == 0) continue;
            for (int k = 0; k < n; ++k) {
                if (!g[j][k] || j == k) continue;
                if (lowbit(i) > (1 << k)) continue;
                if ((i >> k) & 1) {
                    if (lowbit(i) == (1 << k))
                        ans += dp[j][i];
                }
                else
                    dp[k][i|(1 << k)] += dp[j][i];
            }
        }
    }
    cout << (ans - m) / 2;
    return 0;
}