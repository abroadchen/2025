//
// Created by Psy.C on 2026/8/25.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 110;

int c[N][N];
void init() {
    for (int i = 0; i <= 100; ++i) c[i][0] = 1;
    for (int i = 1; i <= 100; ++i)
        for (int j = 1; j <= i; ++j)
            c[i][j] = c[i-1][j] + c[i-1][j-1];
}

int dp[N][N], lim[16];
int dfs(int len, bool flag) {
    memset(dp, 0, sizeof dp);
    for (int i = 0; i <= min(len - flag, lim[0]); ++i)
        dp[0][i] = c[len-flag][i];
    for (int i = 1; i < 16; ++i)
        for (int j = 0; j <= len; ++j)
            for (int k = 0; k <= min(j, lim[i]); ++k)
                dp[i][j] += dp[i-1][j-k] * c[len-(j-k)][k];
    return dp[15][len];
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int k, n;
signed main() {
    fast;
    k = rd(), n = rd(); init();
    int len;
    for (int &i : lim) i = n;
    for (len = 1; len <= 16*n; ++len) {
        int cnt = dfs(len, 1);
        if (cnt >= k) break;
        k -= cnt;
    }
    for (int i = 1; i <= len; ++i)
        for (int j = i == 1 ? 1 : 0; j < 16; ++j) {
            lim[j]--;
            int cnt = dfs(len - i, 0);
            if (cnt >= k) { printf("%llx", j); break; }
            k -= cnt;
            lim[j]++;
        }
    return 0;
}