//
// Created by Psy.C on 2026/9/14.
//
/**
N：树上点数上限。
M：询问路径条数上限（m 条路径）。
K：边数组大小（流量网络总边数）。
I = N*2 + M：网络节点数的上界估计（树链剖分线段树节点 + 路径节点 + 源汇）
add(u,v,c) 加一条容量 c 的正向边和一条容量 0 的反向边（标准最大流建图）。tot=1 起始，用 e[i^1] 取反向边
dfs 里用 int& i = head[u] 会修改 head[]，所以 dinic 里在每次 bfs 前用 cur 备份恢复 head（memcpy(cur,head,...)，之后 memcpy(head,cur,...)）。这是实现细节，不会影响正确性

分层 BFS，找出增广路径，dep 记录层数。
Dinic 的多路增广（当前弧优化体现在 for 循环引用 i=head[u]），边满流或到不了 T 时 dep[u]=-1 剪枝。
循环 bfs + dfs 直到无法增广，返回最大流 ret。
get(S)：从源点沿剩余容量>0的边 DFS，标记可达点。这是求最小割的割集（S 侧点）‍的经典做法，用于最后输出方案（选哪些边/路径）
g[u] 存邻接（ii = (点, 边编号)）。
第一趟 dfs：算子树大小 sz、父节点 fa、深度 dep2、重儿子 son，并把每条树边的编号 val[v] 记录在子节点 v 上（即"边权落点"
第二趟 dfs：重链剖分。bl[u] 是 u 所在重链的链头。dfn[u] 是 dfs 序，pos[dfn[u]] = val[u] 把 dfs 序位置映射到树边的编号。这样一条链上的连续边就对应 dfs 序上的连续区间

线段树的每个节点对应网络中的一个点。叶节点 l==r 代表一条具体的树边（位置 l），它向汇点 T 连一条容量 1 的边——表示每条树边最多被选一次。
b[pos[l]] = rt：把"树边编号（即 pos[l]）"映射到它对应的线段树叶节点编号。这样给出了"树边 → 网络节点"的映射，供最后输出哪些树边被选中。
内部节点向左右儿子连容量 inf 的边，保证流量可以从祖先流到任意叶子
query：把网络中的源点侧节点 v 与线段树区间 [L,R]（即 dfs 序上一段连续树边）连容量 inf 的边——表示"选择这条路径会占用区间内的所有树边"

源点 S → 每条路径一个节点（容量1）‍：代表"是否选择这条路径"。
每条路径节点 → 线段树区间（该路径覆盖的树边，容量 inf）。
线段树叶 → 汇点 T（容量1）："每条树边最多被选一次"。
于是流的意义：若选某条路径，它所需的流量 1 必须从 S 流经该路径节点、再流到线段树覆盖的所有叶节点、最后到 T。因为每条树边（叶→T）容量只有 1，所以两条共享任何一条树边的路径无法同时满流 → 最大流 = 能选出的、两两不共边的路径最大数量

最大流 dinic 就是答案（最多不相交完整路径数）。
get(S) 求出最小割中 S 侧的可达点集 vis：
一个路径节点 a[i] 不可达（!vis）→ 该路径在割集里 → 未选，加入 ans1（输出被"放弃"的路径编号）。
一个树边（叶）节点 b[i] 可达（vis）→ 该边被选，加入 ans2。
输出：放弃的路径数及其编号；选取的树边数及其编号
 */
#include <bits/stdc++.h>
#define ii pair<int,int>
using namespace std;

constexpr int N = 2e4+10, M = 1e4+10, K = 5e6+10, I = N*2+M, inf = 0x3f3f3f3f;

struct edge { int v, c, nxt; } e[K];

int tot=1, head[I];
inline void adde(int u, int v, int c) {
    e[++tot].v = v, e[tot].c = c, e[tot].nxt = head[u], head[u] = tot;
}
inline void add(int u, int v, int c) {
    adde(u, v, c), adde(v, u, 0);
}

int dep[I], q[I];
inline bool bfs(int S, int T) {
    memset(dep, 0, sizeof(dep)); dep[S] = 1;
    int l = 1, r = 1; q[1] = S;
    while (l <= r) {
        int u = q[l++];
        for (int i = head[u], v; i; i = e[i].nxt) {
            if (e[i].c && !dep[v=e[i].v]) {
                dep[v] = dep[u]+1, q[++r] = v;
                if (v == T) return 1;
            }
        }
    }
    return 0;
}

int dfs(int u, int dist, int T) {
    if (u == T) return dist;
    int ret = 0;
    for (int& i = head[u], v; i; i = e[i].nxt) {
        if (dep[v=e[i].v] == dep[u]+1 && e[i].c) {
            int d = dfs(v, min(dist-ret, e[i].c), T);
            e[i].c -= d, e[i^1].c += d, ret += d;
            if (ret == dist) return dist;
        }
    }
    if (!ret) dep[u] = -1;
    return ret;
}

bool vis[I];
void get(int u) {
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt)
        if (e[i].c && !vis[e[i].v])
            get(e[i].v);
}

int cur[I];
int dinic(int S, int T) {
    int ret = 0;
    memcpy(cur, head, sizeof head);
    while (bfs(S, T))
        ret += dfs(S, inf, T), memcpy(head, cur, sizeof cur);
    return ret;
}

int sz[N], fa[N], val[N], dep2[N], son[N];
list<ii> g[N];
void dfs(int u) {
    sz[u] = 1;
    for (auto [fst, snd] : g[u]) {
        int v = fst, id = snd;
        if (v == fa[u]) continue;
        val[v] = id, dep2[v] = dep2[u]+1, fa[v] = u, dfs(v), sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

int bl[N], dfn[N], pos[N];
void dfs(int u, int top) {
    bl[u] = top;
    static int ind;
    dfn[u] = ++ind, pos[ind] = val[u];
    if (son[u]) dfs(son[u], top);
    for (auto key: g[u] | views::keys) {
        int v = key;
        if (v == fa[u] || v == son[u]) continue;
        dfs(v, v);
    }
}

struct node { int ls, rs; } tr[N<<1];
#define mid ((l+r)>>1)
int cnt, rt, b[N], T;
void build(int& rt, int l, int r) {
    if (!rt) rt = ++cnt;
    if (l == r) {
        add(rt, T, 1), b[pos[l]] = rt;
        return;
    }
    build(tr[rt].ls, l, mid), build(tr[rt].rs, mid+1, r);
    add(rt, tr[rt].ls, inf), add(rt, tr[rt].rs, inf);
}

void query(int rt, int l, int r, int L, int R, int v) {
    if (L <= l && r <= R) { add(v, rt, inf); return; }
    if (L <= mid) query(tr[rt].ls, l, mid, L, R, v);
    if (R > mid) query(tr[rt].rs, mid+1, r, L, R, v);
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int S, a[M];
list<int> ans1, ans2;
int main() {
    int n, m; rd(n), rd(m);
    for (int i = 1, u, v; i <= n-1; ++i) {
        rd(u), rd(v);
        g[u].emplace_back(v, i), g[v].emplace_back(u, i);
    }
    dfs(1), dfs(1, 1);
    S = 1, T = 2, cnt = 2; build(rt, 1, n);
    for (int i = 1, u, v; i <= m; ++i) {
        a[i] = cnt + i;
        add(S, cnt+i, 1);
        rd(u), rd(v);
        while (bl[u]^bl[v]) {
            if (dep2[bl[u]] < dep2[bl[v]]) swap(u, v);
            query(rt, 1, n, dfn[bl[u]], dfn[u], i+cnt), u = fa[bl[u]];
        }
        if (dep2[u] > dep2[v]) swap(u, v);
        query(rt, 1, n, dfn[son[u]], dfn[v], i+cnt);
    }
    printf("%d\n", dinic(S, T)); get(S);
    for (int i = 1; i <= m; ++i)
        if (!vis[a[i]]) ans1.push_back(i);
    for (int i = 1; i <= n; ++i)
        if (vis[b[i]]) ans2.push_back(i);
    printf("%d ", ans1.size());
    for (int x : ans1) printf("%d ", x); puts("");
    printf("%d ", ans2.size());
    for (int x : ans2) printf("%d ", x); puts("");
    return 0;
}