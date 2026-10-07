//
// Created by Psy.C on 2026/10/7.
//
/**
g[u]：邻接表，存 (v, id)。
id == 0：有向边 u -> v（只能由 u 到 v）。
id != 0：无向边（第 id 条），连接 u 和 v。
st[id]：无向边 id 的其中一个端点（读取时记为 u）。
op[id]：记录无向边 id 的最终定向方向。
vis：是否访问到。
flg：两种模式的开关
t==1：有向边，邻接表只从 u 出发。
t==2：无向边，双向都加入邻接表，压缩 id
第一遍 flg=0：

遇到无向边 (u,v,id) 且 v 未访问：把它定成 op[id] = (st[id] != u)。
若 st[id] == u（u 是这条无向边读取时的起点），则 op[id]=0（+ 方向，朝 v）。
若 st[id] != u（u 是读取时的终点），则 op[id]=1（- 方向）。
并继续 DFS 到 v。
含义：从源点可达的顶点，顺着 DFS 把它能用的无向边"向外定向"，使得新顶点能被覆盖，最大化可达顶点数
第二遍 flg=1：遇到无向边时，把方向定成指向已访问的 v 之外，即定向成"朝 u"（st[id]!=v 表示朝向 u），但不继续 dfs(v)（v 已经被访问过，或者我们选择不扩展）。

这是个两点式结果的题：比较两种策略，得到不同（也可能相同）的"最大可达顶点数 ans"和对应定向
两遍分别输出可达顶点数 ans 和每条无向边的定向（- 表示 op=1，+ 表示 op=0）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 3e5+5;

int ans, vis[N], op[N], st[N];
vector<ii> g[N];
bool flg;
void dfs(int u) {
    ans++, vis[u] = 1;
    for (auto [v, id] : g[u]) {
        if (vis[v]) continue;
        if (!id) dfs(v);
        else if (flg) op[id] = st[id] != v;
        else op[id] = st[id] != u, dfs(v);
    }
}

int main() {
    fast;
    int n, m, s, idx = 0; cin >> n >> m >> s;
    for (int i = 1, t, u, v; i <= m; ++i) {
        cin >> t >> u >> v;
        if (t == 1) g[u].emplace_back(v, 0);
        else st[++idx] = u, g[u].emplace_back(v, idx), g[v].emplace_back(u, idx);
    }
    dfs(s);
    cout << ans << '\n';
    for (int i = 1; i <= idx; ++i) cout << (op[i] ? '-' : '+');
    cout << '\n';
    memset(op, 0, sizeof(op));
    memset(vis, 0, sizeof(vis));
    ans = 0, flg = 1;
    dfs(s);
    cout << ans << '\n';
    for (int i = 1; i <= idx; ++i) cout << (op[i] ? '-' : '+');
    return 0;
}