//
// Created by Psy.C on 2025/9/13.
//


#include <cstring>
#include <ios>
#include <iostream>
using namespace std;
typedef long long ll;
const int MAXN = 55;

ll k, n, dp[MAXN][2][2], res[MAXN];


ll solve(ll cur, ll rev, ll inv) {
    if (dp[cur][rev][inv] > -1) return dp[cur][rev][inv];
    if (cur * 2 >= n) return dp[cur][rev][inv] = 1;

    ll& ret = dp[cur][rev][inv] = 0;
    for (int i = 0; i < 2; ++i)
        if (res[cur + 1] == i || res[cur + 1] == -1)
            for (int j = 0; j < 2; ++j)
                if (res[n - cur] == j || res[n - cur] == -1)
                    if ((i == j || 2 * cur + 1 != n) && (!rev || i <= j) && (!inv || i <= 1 - j))
                        ret += solve(cur + 1, rev & (i == j), inv & (i != j));
    return ret;
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k; k++;
    memset(dp, -1, sizeof(dp));
    memset(res, -1, sizeof(res));

    if (solve(0, 1, 1) < k) return cout << -1, 0;

    for (int i = 1; i <= n; ++i) {
        memset(dp, -1, sizeof(dp));
        res[i] = 0;
        ll t = solve(0, 1, 1);
        if (t < k) k -= t, res[i] = 1;
        cout << res[i];
    }
    return 0;
}