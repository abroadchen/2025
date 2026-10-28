//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
x：区间最大值
lz：懒标记（区间加）
三个工具函数：

merge：f.x = max(l.x, r.x)
calc：给节点 rt 整体加 val（改 x 和 lz）
push_down：下传懒标记
这棵线段树维护的“值”是后期 DFS 序上每个位置的一个距离值
dfn[u]：u 的 DFS 序编号（1..n）
to[dfn[u]] = u：编号反查节点
sz[u]：子树大小 → u 的子树在 DFS 序上是连续区间 [dfn[u], dfn[u]+sz[u]-1]
a[u]：根到 u 的路径长度
dis[u]：u 子树内，从 u 到最远叶子的距离（即子树内经过 u 的最深深度）
to 数组的意义：后文线段树建树时，用 DFS 序位置映射回节点、拿到其 a 值
建树后，线段树区间 [l,r] 的 x 就是：DFS 序在 [l,r] 区间内所有节点的 a（根到该点距离）的最大值。

作用：a[v] - a[to[p]] 恰好等于点 v 到 DFS 序位置 p 对应节点的树上距离。所以线段树能快速回答："某个"u 到"一段 DFS 序范围内的所有点"的最远距离
当从 u 下钻到儿子 v 时，把线段树整体值的"参考基准"从 u 挪到 v。设当前线段树某位置 p 的值表示"当前点 u 到点 to[p] 的距离"（初始为根到该点距离，即相对根的深度差）。换到 v 时，

对 v 子树外的点 p：u到p 比 v到p 少一条边 w，所以 距离 = (u到p)+w，整体加 w ✓；
对 v 子树内的点 p：u到p 比 v到p 多一条边 w，所以减 w ✓。
于是递归到 v 时，ask(1, 左/右区间).x 直接就是"v 到外部最远点的距离"，即 del[v] = max(del[v], 外部区间 max a 的相对值)。

这样每个 del[u] 就正确求出来了。
dis[v]+w = "从 u 经过儿子 v 这一支，最深能到多远（相对 u）"，若 > x 说明从 u 出发这支必须被切断（否则以 u 为根的块直径超限）。
son[u]：存放这些必须被砍的儿子；dg[v]=1 标记 v
若某点子树半径 dis[u]>x，单独一个点也要算一次。
若 son[u].size()>=2，说明 u 有两个及以上必须切的支路，无法在 u 处用"砍掉 u"一个动作同时处理 → 返回 inf（不可行）。
否则 dp[u] = 处理 u 子树所需最少砍刀数
del[i] ≤ x 保证"以 i 为新块的根"时，这个块外部方向最远距离也在限制内。
以 i 为根的块，其内部允许超限的子支被切成 1 + Σ dp[t] 块。总块数≤可接受数量则判可行
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 1; i <= n; i++)
#define mid ((l+r)>>1)
#define ii pair<int,int>
#define int long long
using namespace std;

constexpr int N = 1e5+10, inf = 1e9;

struct node { int l, r, x, lz; } tr[N<<2];

inline void merge(node &f, node &l, node &r) { f.x = max(l.x, r.x); }
inline void calc(int rt, int val) { tr[rt].lz += val; tr[rt].x += val; }
inline void push_down(int rt) {
    if (!tr[rt].lz) return;
    calc(rt<<1, tr[rt].lz); calc(rt<<1|1, tr[rt].lz);
    tr[rt].lz = 0;
}

int a[N], to[N];
void build(int rt, int l, int r) {
    tr[rt] = {l, r};
    if (l == r) { tr[rt].x = a[to[l]]; return; }
    build(rt<<1, l, mid); build(rt<<1|1, mid+1, r);
    merge(tr[rt], tr[rt<<1], tr[rt<<1|1]);
}
void add(int rt, int st, int ed, int val) {
    int l = tr[rt].l, r = tr[rt].r;
    if (st <= l && r <= ed) { calc(rt, val); return; }
    push_down(rt);
    if (st <= mid) add(rt<<1, st, ed, val);
    if (ed > mid) add(rt<<1|1, st, ed, val);
    merge(tr[rt], tr[rt<<1], tr[rt<<1|1]);
}
node ask(int rt, int st, int ed) {
    int l = tr[rt].l, r = tr[rt].r;
    if (st <= l && r <= ed) return tr[rt];
    push_down(rt);
    if (ed <= mid) return ask(rt<<1, st, ed);
    if (st > mid) return ask(rt<<1|1, st, ed);
    node res{}, L = ask(rt<<1, st, ed), R = ask(rt<<1|1, st, ed);
    merge(res, L, R);
    return res;
}

int fa[N], dfn[N], sz[N], tim, dis[N];
vector<ii> g[N];
void dfs(int u, int f) {
    fa[u] = f, dfn[u] = ++tim, sz[u] = 1, to[dfn[u]] = u;
    for (auto [fst, snd] : g[u]) {
        int v = fst, w = snd;
        if (v == f) continue;
        a[v] = a[u] + w;
        dfs(v, u);
        dis[u] = max(dis[u], dis[v]+w), sz[u] += sz[v];
    }
}

int del[N], n;
void dfs2(int u, int f) {
    if (dfn[u] != 1) del[u] = max(del[u], ask(1,1,dfn[u]-1).x);
    if (dfn[u]+sz[u]-1 != n) del[u] = max(del[u], ask(1,dfn[u]+sz[u],n).x);
    for (auto [fst, snd] : g[u]) {
        int v = fst, w = snd;
        if (v == f) continue;
        if (dfn[v] != 1) add(1,1,dfn[v]-1,w);
        if (dfn[v]+sz[v]-1 != n) add(1,dfn[v]+sz[v],n,w);
        add(1,dfn[v],dfn[v]+sz[v]-1,-w);
        dfs2(v,u);
        if (dfn[v] != 1) add(1,1,dfn[v]-1,-w);
        if (dfn[v]+sz[v]-1 != n) add(1,dfn[v]+sz[v],n,-w);
        add(1,dfn[v],dfn[v]+sz[v]-1,w);
    }
}

vector<int> son[N];
int dp[N], dg[N];
void solve(int u, int x) {
    if (son[u].size() >= 2) dp[u] = inf;
    else if (dis[u] > x || dg[u]) dp[u] = 1;
    else dp[u] = 0;
    for (auto key: g[u] | views::keys) {
        int v = key;
        if (v != fa[u]) solve(v, x);
    }
    for (int t : son[u]) dp[u] += dp[t];
}

int k;
inline bool check(int x) {
    int i, u;
    rep(i,n) dg[i] = 0;
    rep(u,n) {
        son[u].clear();
        for (auto [fst, snd] : g[u]) {
            int v = fst, w = snd;
            if (v == fa[u]) continue;
            if (dis[v]+w > x) son[u].push_back(v), dg[v] = 1;
        }
    }
    solve(1, x);
    rep(i,n) {
        if (del[i] > x) continue;
        if (son[i].size() > 2) continue;
        int res = 1;
        for (int t : son[i]) res += dp[t];//以 i 为根，减去被切支后所需块数
        if (res <= k) return 1;//≤k 次可行
    }
    return 0;
}

int i, u, v, w;
signed main() {
    fast;
    cin >> n >> k;
    rep(i,n-1) {
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    dfs(1, 0); build(1,1,n); dfs2(1,0);
    int l = 0, r = inf, res = -114514;
    while (l <= r) {
        if (check(mid)) res = mid, r = mid-1;
        else l = mid+1;
    }
    cout << res << '\n';
    return 0;
}