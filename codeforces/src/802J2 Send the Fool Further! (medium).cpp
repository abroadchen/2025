//
// Created by Psy.C on 2026/9/18.
//
/**
dp[cur][0]、dp[cur][1] 是两个 DP 状态（下面解释含义）。
图是无向带权树，节点 0..n-1，n-1 条边
对每个孩子 x，先递归处理，然后收集一个二元组：
w + dp[x][0]
w + dp[x][1]
即：把孩子 x 作为一条边接入 cur 时的两种状态取值
把孩子按 x.first（即 w+dp[x][0]）‍从大到小排序。
取前 cnt = min(k-1, 孩子数) 个的 first 求和得 sum —— 这是选前 k-1 个"最优孩子"的 first 值之和
dp[cur][0] 直接取 sum：即不管细节，先取前 k-1 个孩子的 first 之和。
dp[cur][1]：枚举把某个孩子 i 用它的 second（即 w+dp[x][1]）替换的收益：
若 i 在原前 cnt 个里：val = sum - a[i].first + a[cnt].first（用第 cnt 个的 first 补位）；
否则：val = sum（i 本来不在前 cnt，直接额外加它的 second）；
dp[cur][1] = max(dp[cur][1], val + a[i].second)
从根 0 出发，输出 dp[0][1]
 */
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