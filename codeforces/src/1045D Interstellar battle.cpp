//
// Created by Psy.C on 2026/11/7.
//

/**
真正学会的起点..
链式前向星存无向边，N<<1 是因为一条边存两次。
add(u,v) 头插法。
fa[v]=u：记录父节点。
sum[u] += p[v]：累加 u 的所有直接儿子 v 的选中概率。
递归建树（以 1 为根），一次 DFS 即可完成全部 sum。
关键点：树上每个节点只和它的父节点相邻（在树中除根外每个节点只有一个父），所以"是否与其父冲突"是唯一的约束对

输入给的 p[i] 是"不被选中"的概率，这里 p[i] = 1 - p[i] 转成"被选中"的概率。
ans += p[i]：概率的线性可加——先累加所有选中概率。
输入下标从 0 开始，++u;++v 转成 1 起始。
ans -= p[u]*p[v]：减去每对相邻点同时选中的概率（独立事件，乘积）
以 1 为根跑 DFS，求出每个节点的 sum[]（儿子选中概率和）。
读入要更新的节点 u（转 1 起始）和新概率（输入是"不选中"，转成 x = 选中概率）
整体逻辑是**「增量式维护」：更新某个节点概率时，只改动它自身、其父亲、其儿子**相关的三项，避免全图重算。
每次先把节点 u 的旧贡献去掉（自身、父子边），再把它新贡献加回来，复杂度 O(1)（因为每个节点的度数相关项只有父亲+儿子，由树结构保证）

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
#define ld long double
using namespace std;

constexpr int N = 1e5+10;

struct edge { int to, nxt; } e[N<<1];

int cnt, head[N];
void add(int u, int v) {
    e[++cnt].to = v; e[cnt].nxt = head[u]; head[u] = cnt;
}

int fa[N];
ld sum[N], p[N];
void dfs(int u, int f) {
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == f) continue;
        fa[v] = u; sum[u] += p[v];
        dfs(v, u);
    }
}

int n, m;
void solve() {
    cin >> n;
    ld ans = 0;
    rep(i,n) { cin >> p[i]; p[i] = 1 - p[i]; ans += p[i]; }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v; ++u; ++v; add(u, v); add(v, u);
        ans -= p[u]*p[v];
    }
    dfs(1, -1);
    cin >> m;
    while (m--) {
        int u; ld x; cin >> u >> x; ++u; x = 1 - x;
        ans -= p[u]; ans += p[u]*sum[u];//去掉旧 p[u] 的贡献 去掉旧 p[u] 与其儿子的关系项
        if (u != 1) { ans += p[u]*p[fa[u]]; sum[fa[u]] -= p[u]; }//去掉旧 p[u] 与其父亲的关系项 同步更新父亲的 sum（临时移除旧值）
        ans += x; ans -= x*sum[u];//加上新 x 的贡献 加上新 x 与其儿子的关系项
        if (u != 1) { ans -= x*p[fa[u]]; sum[fa[u]] += x; }//加上新 x 与其父亲的关系项 同步更新父亲的 sum（加入新值）
        p[u] = x;//真正更新 p[u]
        cout << fixed << setprecision(6) << ans << '\n';
    }
}


int main() {
    fast;
    int T = 1;
    while (T--) solve();
    return 0;
}