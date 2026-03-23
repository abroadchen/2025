//
// Created by Psy.C on 2026/3/23.
//
/**
u, v：边的两个端点
w：边的权重
id：原始边的编号
fl：标记是否在MST中
ST表（Sparse Table）查询区间最大值，使用RMQ（Range Maximum Query）算法
ST表预处理函数，预计算区间最大值
链式前向星建图，用于存储MST

树的第一次DFS：建立父子关系，计算子树大小，找出重儿子
树链剖分的第二次DFS：分配DFS序，建立重链
LCA（最近公共祖先）路径查询函数，使用树链剖分在线查询路径上的最大边权

Kruskal算法构造MST，使用并查集检测环路
对MST进行树链剖分预处理
对于每条边：
如果已经在MST中，则答案就是原MST权重
如果不在MST中，则加上这条边后形成环路，需要删除环路上的最大边
O(m log m + n log n)，主要是排序和树链剖分的时间复杂度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5, M = 4e5+5, A = 2e6+5, inf = 2100000000;

struct node {
    int u, v, w, id, fl;
    bool operator<(const node &o) const {
        return w < o.w;
    }
} p[N];

int f[N];
int find(int x) {
    if (x == f[x]) return x;
    return f[x] = find(f[x]);
}

int st[N][23];
int query(int l, int r) {
    int k = log2(r - l + 1);
    return max(st[l][k], st[r-(1<<k)+1][k]);
}
int n;
void get() {
    for (int j = 1; j <= 22; ++j)
        for (int i = 1; i+(1<<j)-1 <= n; ++i)
            st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
}

struct node2 { int v, w, nxt; } o[M];
int head[N], cnt;
void add(int u, int v, int w) {
    o[++cnt] = {v, w, head[u]}, head[u] = cnt;
}
int d[N], fa[A], siz[N], w[N], son[N];
void dfs(int x, int ff, int dep) {
    d[x] = dep; fa[x] = ff; siz[x] = 1;
    for (int i = head[x], v, mx = -1; i; i = o[i].nxt) {
        v = o[i].v;
        if (v == fa[x]) continue;
        dfs(v, x, dep+1);
        w[v] = o[i].w;
        siz[x] += siz[v];
        if (mx < siz[v]) mx = siz[v], son[x] = v;
    }
}
int top[N], id[N];
void dfs2(int x, int ff) {
    top[x] = ff;
    st[id[x]=++id[0]][0] = w[x];
    if (!son[x]) return;
    dfs2(son[x], ff);
    for (int i = head[x], v; i; i = o[i].nxt) {
        v = o[i].v;
        if (v == son[x] || v == fa[x]) continue;
        dfs2(v, v);
    }
}

int tarjan(int u, int v) {
    int ans = -inf;
    while (top[u] != top[v]) {
        if (d[top[u]] < d[top[v]]) swap(u, v);
        ans = max(ans, query(id[top[u]], id[u]));
        u = fa[top[u]];
    }
    if (d[u] > d[v]) swap(u, v);
    if (u != v) ans = max(ans, query(id[u]+1, id[v]));
    return ans;
}

int m;
ll ans[N], res;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) f[i] = i;
    for (int i = 1, u, v, ww; i <= m; ++i) {
        cin >> u >> v >> ww;
        p[i] = {u, v, ww, i, 0};
    }
    sort(p + 1, p + m + 1);
    for (int i = 1; i <= m; ++i) if (find(p[i].u) != find(p[i].v)) {
        f[find(p[i].u)] = find(p[i].v);
        add(p[i].u, p[i].v, p[i].w); add(p[i].v, p[i].u, p[i].w);
        p[i].fl = 1; res += p[i].w;
    }
    dfs(1, 0, 1); dfs2(1, 1); get();
    for (int i = 1; i <= m; ++i) {
        if (p[i].fl) ans[p[i].id] = res;
        else ans[p[i].id] = res + p[i].w - tarjan(p[i].u, p[i].v);
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << ' ';
    return 0;
}