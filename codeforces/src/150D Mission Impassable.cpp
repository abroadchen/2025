//
// Created by Psy.C on 2025/11/23.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#define maxx(a,b) (a) = max((a), (b))
using namespace std;

constexpr int N = 155, inf = 1e9;
int n, c[N], f[N][N], g[N][N][N], dp[N];
string str;

int main() {
    ostream::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        if (c[i] == -1) c[i] = -inf;
    }
    getline(cin, str);
    memset(f, -0x3f, sizeof f);
    memset(g, -0x3f, sizeof g);
    for (int i = 1; i <= n; ++i) g[i][i][1] = 0, f[i][i] = c[1];
    for (int i = 1; i < n; ++i) g[i+1][i][0] = 0;

    for (int len = 2; len <= n; ++len) {
        for (int i = 1, j = i + len - 1; j <= n; ++i, ++j) {
            for (int k = 1; k <= len; ++k) {
                if (k >= 2 && str[i] == str[j]) {
                    maxx(g[i][j][k], g[i+1][j-1][k-2]);
                    maxx(g[i][j][2], g[i+1][j-1][k-2]+c[k-2]);
                }
                for (int l = i; l < j; ++l) maxx(g[i][j][k],
                    max(g[i][l][k]+f[l+1][j], f[i][l]+g[l+1][j][k]));
            }
            for (int k = 1; k <= len; ++k) maxx(f[i][j],
                g[i][j][k] + c[k]);
        }
    }
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1];
        for (int j = 1; j <= i; ++j) dp[i] = max(dp[i],
            dp[j - 1] + f[j][i]);
    }
    cout << dp[n] << '\n';
    return 0;
}