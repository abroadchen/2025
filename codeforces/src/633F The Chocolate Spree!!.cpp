//
// Created by Psy.C on 2026/3/30.
//
/**
w[x]: 节点x的权值
f[x][0]: 以x为根的子树中，包含节点x的最优路径的最大权值
f[x][1]: 以x为根的子树中，不包含节点x的最优路径的最大权值
g[x]: 从节点x向下延伸的单链（以x为端点）的最大权值
h[x]: 从节点x向下延伸的单链（不包括x）的最大权值
d[x]: 从节点x向下延伸的单链（包括x）的最大权值

时间复杂度：O(n)，每个节点访问一次
空间复杂度：O(n)，树的存储和DP数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;

ll f[N][2], g[N], h[N], d[N], w[N];
vector<int> G[N];
void dfs(int x, int fa) {
    f[x][0] = w[x]; f[x][1] = w[x]; g[x] = w[x]; h[x] = 0; d[x] = w[x];
    for (int i = 0; i < G[x].size(); ++i) {
        int u = G[x][i];
        if (u == fa) continue;
        dfs(u, x);
        f[x][0] = max(f[x][0], f[u][0]);//子树u中的最优路径
        f[x][0] = max(f[x][0], f[x][1] + f[u][1]);//x的兄弟路径连接
        f[x][0] = max(f[x][0], d[x] + g[u]);//x的链连接u的链
        f[x][0] = max(f[x][0], g[x] + d[u]);//对称
        f[x][1] = max(f[x][1], f[u][1]);//子树u中不包含u的最优路径
        f[x][1] = max(f[x][1], d[x] + d[u]);//x的链和u的链（都不经过x）
        g[x] = max(g[x], w[x] + g[u]);//x + x->u的链
        g[x] = max(g[x], d[x] + f[u][1]);//x的链 + u子树中不包含u的路径
        g[x] = max(g[x], d[u] + w[x] + h[x]);//u的链 + x + x的另一条链
        h[x] = max(h[x], f[u][1]);//u子树中不包含u的最优路径
        d[x] = max(d[x], d[u] + w[x]);//u的链 + x
    }
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }
    dfs(1, 0);
    cout << f[1][0];
    return 0;
}