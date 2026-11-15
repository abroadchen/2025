//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
dp[v]：从 v 出发、沿 v 的子树向下走到某处、能获得的最大收益（含 v 自己点权，边的收益已扣）。
dp[v] - e[i].w：从 v 走到 u（穿过边 e[i]，损失边权），即以 u 为端点向 v 方向走能得到的收益
更新 ans（跨过 u 的完整路径）‍：

收益 = dp[u]（u 已往某个儿子走的最佳）+ dp[v] - w（u 往 v 方向走）+ a[u]（u 自己）
即以 u 为路径拐点/中转，合并两条从 u 出发的下行链，构成一条经过 u 的整条路径
更新 dp[u]（单侧下行链）‍：

dp[u] = max(dp[u], dp[v] - w)
u 选择收益最大的那个儿子往下走。

最后 dp[u] += a[u]：无论走哪个儿子，都必须算上 u 自己的点权
从节点 1 开始 DFS（父节点记 0 表示无父），最终 ans 就是树上最大收益路径
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 3e5+5;

struct node { int v, nxt, w; } e[N<<1];

int cnt;
ll head[N];
void add(int u, int v, int w) {
    e[++cnt].v = v; e[cnt].w = w; e[cnt].nxt = head[u]; head[u] = cnt;
}

ll ans, a[N], dp[N];
void dfs(int u, int fa) {
    ans = max(ans, a[u]);
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if (v == fa) continue;
        dfs(v, u);
        ans = max(ans, dp[u]+dp[v]-e[i].w+a[u]);
        dp[u] = max(dp[u], dp[v]-e[i].w);
    }
    dp[u] += a[u];
}

int n, u, v, w;
int main() {
    fast; memset(head, -1, sizeof(head));
    cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n-1) { cin >> u >> v >> w; add(u, v, w); add(v,u, w); }
    dfs(1, 0);
    cout << ans;
    return 0;
}