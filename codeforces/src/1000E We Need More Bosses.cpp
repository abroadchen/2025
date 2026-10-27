//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
链式前向星存无向图（每条无向边存两条有向边）。
add 用于往邻接表插入一条边。
注意：全局 e[], nxt[] 同时被复用（既存原图又存缩点树），靠传入不同的 h[] 表头来切换
dfn[u]：dfs 进入时间戳；low[u]：u 通过树边/返祖边能到达的最早时间戳。
tarjan(v, i)：p 传的是边的编号 i（不是父节点），这样能用 (p^1) 判断是否走回同一条无向边（回边）——因为每条无向边存了两条方向相反、编号相邻的边（x^1 是 y），所以 i != (p^1) 表示"不是回到刚刚走过的那条边的反向边"，从而避免把普通回边误判为桥。
桥的判定：若 low[v] > dfn[u]，则边 (u,v) 是桥。但这里没有显式记录桥，而是用 判桥 + 栈 的方式直接缩边双（标准"去桥后的连通块"）。
当 dfn[u] == low[u] 时，u 是所在边双的最早访问点，从栈里弹出所有点归入同一个 scc（边双连通分量编号）。没有桥的连通块会被并成一个点
对原图每条边，如果两个端点属于不同的边双连通分量，则它们之间一定是一条桥。
在这些桥对应的分量之间连边，得到缩点图。
因为所有桥连起来的分量树是无环的（去掉所有桥后每块内部无边，桥连接形成树），所以缩点图是一棵树。
注意重新用 cnt=0 从头建新表（h[], g[], nx[]）
这是树的最长路径（直径）DP：

d1[u]：从 u 向下（子树内）到叶子的最长距离；d2[u]：次长距离。
对每个孩子 v，d = d1[v] + 1（经过边 u-v），更新 u 的两大最长/次长子链。
res = max(res, d1[u] + d2[u])：经过 u 的最长路径 = 两条从 u 伸出的最长 lian 之和，直径就是这些的最大值。
换根/多起点：外层对每个未访问分量 dfs(i,-1) 跑一遍（因为缩点树可能不连通吗？其实原图若是连通的，缩点树也连通，一次 dfs 就够；这里 for 兜底多分量）
读入 n, m，建原图。
tarjan 求边双连通分量（缩块）。
按桥建缩点树。
在树上跑直径 DP。
输出直径 res。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 3e5+10;

int head[N], cnt, e[N<<1], nxt[N<<1];
inline void add(int h[], int e[], int ne[], int a, int b) {
    e[cnt] = b; ne[cnt] = h[a]; h[a] = cnt++;
}

int dfn[N], low[N], tim, st[N], tp, scc, id[N];
inline void tarjan(int u, int p) {
    dfn[u] = low[u] = ++tim; st[++tp] = u;
    for (int i = head[u]; ~i; i = nxt[i]) {
        int v = e[i];
        if (!dfn[v]) {
            tarjan(v, i);
            low[u] = min(low[u], low[v]);
        }
        else if (i != (p^1)) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        int v; scc++;
        do {
            v = st[tp--];
            id[v] = scc;
        } while (u != v);
    }
}

bool vis[N];
int h[N], g[N<<1], nx[N<<1], d1[N], d2[N], res;
inline void dfs(int u, int p) {
    vis[u] = true;
    for (int i = h[u]; ~i; i = nx[i]) {
        int v = g[i];
        if (v == p) continue;
        dfs(v, u);
        int d = d1[v] + 1;
        if (d > d1[u]) d2[u] = d1[u], d1[u] = d;
        else if (d > d2[u]) d2[u] = d;
    }
    res = max(res, d1[u] + d2[u]);
}

int n, m;
int main() {
    fast;
    cin >> n >> m;
    memset(head, -1, sizeof(head));
    memset(h, -1, sizeof(h));
    while (m--) {
        int x, y; cin >> x >> y;
        add(head, e, nxt, x, y); add(head, e, nxt, y, x);
    }
    rep(i,n) if (!id[i]) tarjan(i, -1);
    cnt = 0;
    rep(i,n) for (int j = head[i]; ~j; j = nxt[j]) {
        int k = e[j];
        if (id[i] != id[k]) add(h, g, nx, id[i], id[k]);
    }
    rep(i,scc) if (!vis[i]) dfs(i,-1);
    cout << res << '\n';
    return 0;
}