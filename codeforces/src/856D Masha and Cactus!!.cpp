//
// Created by Psy.C on 2026/9/30.
//
/**
数组模拟邻接表：head[u] 指向 u 的第一条边的下标，nxt 存下一条，to 存边终点。
只加一次方向（树用）
sz[x]：x 的子树节点个数。
dep[x]：深度，同时确认 fa（因为边只由父指向子，天然拓扑）。
son[x]：重儿子 = 子树最大那个孩子，为树链剖分做准备
经典树链剖分：重儿子和父节点在同一条重链（top 相同），轻儿子各自开新链。
dfn[x]：树剖后的 dfs 序（即线段树下标），把树拍平成一维数组，使一条重链对应一段连续区间，从而能用线段树维护。
nd[tim]：反查 dfn→节点
利用重链剖分跳链求最近公共祖先：每次把链顶更深的一端跳到它的父节点，直到同链，浅者为 LCA
path：一条带权路径，端点 u,v、权 w。
node：线段树节点，l,r 区间、val 区间和（这里 val 存"dp 差值"用于回退，见后）
标准线段树，对 dfn 序按深度/节点管理区间和
与 LCA 同构的跳链，但把它换成对每条重链区间做 query 累加。
用途：查询路径上已做过的某种"标记/贡献"之和（下面对应 sum - dp 的差值回退机制）
sum = 所有子树 dp 值和（即节点 x 不参与任何路径时子树给出的总收益）。
两条候选：
不选经过 x 的路径：dp[x]=sum。
选一条以 x 为 LCA 的路径 (u,v,w)：该路径贡献 w + 路径上所有节点的总和值。因为选了这条路径，祖先到该路径之间的那些节点不能再用其他路径……这里用 get(u,v) 加 sum，含义是通过线段树把路径上已记录的"差值"加回来，等价于"选这条链能额外多拿的收益"。
取 max 得 dp[x]。
最后 modify(dfn[x], sum-dp[x])：把节点 x 的"恢复值"写入线段树——这是让上方祖先在 get() 查询路径和时，能把子树被覆盖掉的贡献正确加回的巧妙技巧（类似树上路径问题里的经典「吃掉/回填」）

读入 n 节点、m 条带权路径。
建树、树链剖分、线段树初始化。
对每条 (u,v,w)，求 LCA，挂在 t[lca]——这是使得在 dfs3 处理节点 x 时，所有 LCA 恰为 x 的路径都已就绪的关键。
从根 dfs3 自底向上 DP，输出 dp[1] = 整棵树能选出的最大总收益

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5, M = 4e5+5;

int to[M], nxt[M], head[N], cnt;
inline void add(int u, int v) {
    to[++cnt] = v, nxt[cnt] = head[u], head[u] = cnt;
}

int sz[N], dep[N], son[N];
inline void dfs(int x) {
    sz[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        dep[y] = dep[x] + 1;
        dfs(y);
        sz[x] += sz[y];
        if (sz[y] > sz[son[x]]) son[x] = y;
    }
}

int top[N], dfn[N], tim, nd[N];
inline void dfs2(int x, int tp) {
    top[x] = tp; dfn[x] = ++tim; nd[tim] = x;
    if (son[x]) dfs2(son[x], tp);
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (y != son[x]) dfs2(y, y);
    }
}

int fa[N];
inline int getlca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if (dep[x] < dep[y]) swap(x, y);
    return y;
}

struct path {
    int u, v, w;
    path() = default;
    path(int u, int v, int w) : u(u), v(v), w(w) {}
};
struct node { int l, r, val; } s[N<<2];

inline void build(int k, int l, int r) {
    s[k].l = l; s[k].r = r;
    if (l == r) return;
    int mid = (l+r)>>1;
    build(k<<1, l, mid); build(k<<1|1, mid+1, r);
}

inline void modify(int k, int ind, int val) {
    if (s[k].l == s[k].r) { s[k].val += val; return; }
    int mid = (s[k].l + s[k].r) >> 1;
    if (ind <= mid) modify(k<<1, ind, val);
    else modify(k<<1|1, ind, val);
    s[k].val = s[k<<1].val + s[k<<1|1].val;
}

inline int query(int k, int l, int r) {
    if (l <= s[k].l && s[k].r <= r) return s[k].val;
    int mid = (s[k].l + s[k].r) >> 1;
    if (r <= mid) return query(k<<1, l, r);
    if (l > mid) return query(k<<1|1, l, r);
    return query(k<<1, l, mid) + query(k<<1|1, mid+1, r);
}

inline int get(int u, int v) {
    int sum = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        sum += query(1, dfn[top[u]], dfn[u]);//累加一整条重链区间
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    sum += query(1, dfn[v], dfn[u]);//最后一条链
    return sum;
}

int dp[N];
vector<path> t[N];//存所有 LCA 为 x 的带权路径
inline void dfs3(int x) {
    int sum = 0;
    for (int i = head[x]; i; i = nxt[i]) {
        dfs3(to[i]);//先处理所有子树
        sum += dp[to[i]];//累加儿子的 dp（即"不经过 x 的方案"之和）
    }
    dp[x] = sum;//基础值：x 不选任何路径（全由子树拼出）
    for (auto it = t[x].begin(); it != t[x].end(); ++it)//遍历所有以 x 为 LCA 的路径
        dp[x] = max(dp[x], get(it->u, it->v)+it->w+sum);//选这条路径的收益
    modify(1, dfn[x], sum-dp[x]);//把"差值"写进线段树，供祖先路径查询回退
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    fast;
    int n = rd(), m = rd();
    for (int i = 2; i <= n; ++i) {
        fa[i] = rd(); add(fa[i], i);
    }
    dfs(1); dfs2(1, 1); build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        int u = rd(), v = rd(), w = rd();
        t[getlca(u, v)].emplace_back(u, v, w);
    }
    dfs3(1);
    cout << dp[1] << '\n';
    return 0;
}