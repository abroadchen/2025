//
// Created by Psy.C on 2026/3/4.
//
/**
f[N] 数组存储权重信息
值x、左端点l、右端点r、连续性标志b
重载 + 运算符实现区间合并逻辑

给节点重新编号，保证重链上的节点连续
id[u] 节点u的新编号，rk[tim] 编号tim对应的原节点
top[u] 节点u所在重链的顶端节点
优先遍历重儿子以保证连续性

查询树上路径的函数，使用树链剖分优化
沿着重链向上跳，直到两点在同一重链上
注意要翻转a1的方向（交换l,r）再合并

离线处理：按权重顺序处理边和查询
对于每个查询，将权重>=当前查询权重的边加入线段树
然后查询路径信息
最后按原始ID顺序输出答案
时间复杂度为O((n+m)log²n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

constexpr int N = 1e5+1;

struct edge { int to, nxt; } e[N<<1];

int cnt, head[N];
void add(const int u, const int v) {
    e[++cnt] = {v, head[u]}, head[u] = cnt;
}

int f[N];
struct node {
    int x, l, r; bool b;
    friend node operator+(node x, node y) {
        return {x.x+y.x-f[x.r]-f[y.l]+f[x.r+y.l],
            x.l+x.b*y.l, y.r+y.b*x.r, x.b&&y.b};
    }
} tr[N<<2];

void update(const int x, const int l, const int r, const int i) {//单点更新
    if (l == r) { tr[x] = {f[1], 1, 1, 1}; return; }//设置初始值
    const int mid = (l + r) >> 1;
    i <= mid ? update(x<<1, l, mid, i) : update(x<<1|1, mid+1, r, i);
    tr[x] = tr[x<<1] + tr[x<<1|1];
}

node query(const int x, const int l, const int r, const int L, const int R) {
    if (L <= l && r <= R) return tr[x];
    const int mid = (l + r) >> 1;
    node ans = {0, 0, 0, 1};
    if (L <= mid) ans = query(x<<1, l, mid, L, R);
    if (mid < R) ans = ans + query(x<<1|1, mid+1, r, L, R);
    return ans;
}

int fa[N], siz[N], d[N], son[N];
void dfs(const int u, const int ff) {
    fa[u] = ff; d[u] = d[ff] + 1; siz[u] = 1;
    for (int i = head[u], v; i; i = e[i].nxt) {
        if ((v = e[i].to) == ff) continue;
        dfs(v, u);
        siz[u] += siz[v];
        if (siz[son[u]] < siz[v]) son[u] = v;
    }
}

int id[N], tim, rk[N], top[N];
void dfs2(const int u, const int tp) {
    id[u] = ++tim; rk[tim] = u; top[u] = tp;
    if (son[u]) dfs2(son[u], tp);
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != fa[u] && v != son[u])
            dfs2(v, v);
}

int n;
node query(int x, int y) {
    node a1 = {0, 0, 0, 1}, a2 = {0, 0, 0,1};
    while (top[x] != top[y]) {
        if (d[top[x]] < d[top[y]]) swap(x, y), swap(a1, a2);
        a1 = query(1, 1, n, id[top[x]], id[x]) + a1;
        x = fa[top[x]];
    }
    if (d[x] > d[y]) swap(x, y), swap(a1, a2);
    if (id[x] != id[y]) a2 = query(1, 1, n, id[x]+1, id[y]) + a2;
    return swap(a1.l, a1.r), a1 + a2;
}

struct qu { int u, v, w, id; } a[N], q[N];
bool cmp(const qu x, const qu y) { return x.w > y.w; }
int m, ans[N];
int main() {
    fast;
    n = rd(), m = rd();
    for (int i = 1; i < n; ++i) f[i] = rd();
    for (int i = 1; i < n; ++i) {
        const int u = rd(), v = rd(), w = rd();
        a[i] = {u, v, w, 0}; add(u, v); add(v, u);
    }
    dfs(1, 0); dfs2(1, 1);
    for (int i = 1; i <= n; ++i)
        if (d[a[i].u] > d[a[i].v]) swap(a[i].u, a[i].v);
    for (int i = 1; i <= m; ++i) q[i] = {rd(), rd(), rd(), i};
    sort(a + 1, a + n + 1, cmp);
    sort(q + 1, q + m + 1, cmp);
    for (int i = 1, j = 1; i <= m; ++i) {
        for (; j < n && a[j].w >= q[i].w; ++j)
            update(1, 1, n, id[a[j].v]);
        ans[q[i].id] = query(q[i].u, q[i].v).x;
    }
    for (int i = 1; i <= m; ++i) cout << ans[i] << '\n';
    return 0;
}