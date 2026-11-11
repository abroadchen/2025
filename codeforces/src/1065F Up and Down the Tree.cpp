//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
G[u]：节点 u 的儿子列表。
h[u]：从 u 往下，最远的“未覆盖/高度”标记值（下文细讲）。
dp[u][0]：u 子树内，u 不选作为"中心"时的最优值。
dp[u][1]：u 子树内，u 选作"中心/覆盖点"时的最优值
叶子节点：h = k（最远未覆盖距离初始为 k），两种 dp 均为 1。
非叶子初始化全 0。
先递归处理儿子 v。
h[u] = max(h[v]-1, h[u])：u 的"最远待覆盖高度"是儿子中最大的 h[v]-1（因为上移一层，距离 -1）。
若 h[v] > 0（儿子子树内还有未覆盖的节点），则 dp[u][0] += dp[v][0]——u 不选时，需要继承儿子"未覆盖"方案
这一层在计算"u 选为覆盖中心"时的最优值。
若 h[v] > 0：u 选中后可以覆盖 v 子树内未覆盖的部分，所以把 v 那部分从 dp[v][0] 换成 dp[v][1]（用"覆盖"方案）——即 dp[u][0] - dp[v][0] + dp[v][1]。
若 h[v] <= 0（v 子树已全被覆盖）：直接加上 dp[v][1]

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

constexpr int N = 1e6+10;

vector<int> G[N];
int h[N], k, dp[N][2];
void dfs(int u, int fa) {
    if (G[u].empty()) { h[u] = k; dp[u][0] = dp[u][1] = 1; return; }
    h[u] = dp[u][0] = dp[u][1] = 0;
    rep(i,G[u].size()) {
        int v = G[u][i];
        dfs(v, u);
        h[u] = max(h[v]-1, h[u]);
        if (h[v] > 0) dp[u][0] += dp[v][0];
    }
    rep(i,G[u].size()) {
        int v = G[u][i];
        if (h[v] > 0) dp[u][1] = max(dp[u][1], dp[u][0]-dp[v][0]+dp[v][1]);
        else dp[u][1] = max(dp[u][1], dp[u][0]+dp[v][1]);
    }
}

int n;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 2, x; i <= n; i++) {
        cin >> x; G[x].push_back(i);
    }
    dfs(1, -1);
    cout << dp[1][1] << '\n';
    return 0;
}