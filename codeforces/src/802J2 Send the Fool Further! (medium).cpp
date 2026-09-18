//
// Created by Psy.C on 2026/9/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
#define pll pair<ll, ll>
#define ll long long
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<vector<ii>> g(n);
    for (int i = 2, u, v, c; i <= n; ++i) {
        cin >> u >> v >> c;
        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }
    vector<array<ll, 2>> dp(n+1);
    auto dfs = [&](auto&& self, int cur, int fa) -> void {
        vector<pll> a;
        for (auto [x, w] : g[cur]) {
            if (x == fa) continue;
            self(self, x, cur);
            a.emplace_back(w+dp[x][0], w+dp[x][1]);
        }
        ranges::sort(a, greater<>());
        int cnt = min(k-1, (int)a.size());
        ll sum = accumulate(a.begin(), a.begin()+cnt, 0ll, [&](ll s, auto& x) {
            return s + x.first;
        });
        dp[cur][0] = dp[cur][1] = sum;
        for (int i = 0; i < a.size(); ++i) {
            ll val = sum;
            if (i < cnt) val -= a[i].first - (cnt < a.size() ? a[cnt].first : 0);
            dp[cur][1] = max(dp[cur][1], val+a[i].second);
        }
    };
    dfs(dfs, 0, -1);
    cout << dp[0][1] << '\n';
}

int main() {
    fast;
    int q = 1;
    while (q--) solve();
    return 0;
}