//
// Created by Psy.C on 2026/10/9.
//
/**
DFS 得到：
dep[x]：深度（根 r 深度为 1）。
dfn[x]：欧拉序/时间戳——DFS 进入每个节点时递增编号。
sz[x]：子树大小。
关键性质：
x
x 的整棵子树在 dfn 上对应连续区间 [dfn[x], dfn[x]+sz[x]-1]。这样"子树"问题就转成"区间"问题，方便用线段树
把节点按 dep（深度）排序 p[]。
主席树版本 rt[dep]：以"深度"为版本维度，按 dfn 为下标键，位置上存权值 a，节点维护区间最小值 mn。
build(rt[dep[p[i]]], rt[dep[p[i-1]]], ...)：从上一个深度版本复制并插入当前深度节点的信息。
这样 rt[d] 这棵主席树，包含了所有深度 ≤ d 的节点的 (dfn, a) 数据，且支持区间最小值查询。
由于版本按深度递增构建，rt[d] 可能只"覆盖"了前若干深度的节点，但主席树支持 mn 查询——某深度尚未出现的 dfn 位置 mn 保持 inf
x, k 通过上一次答案 ans 强制在线反解（Reverse encryption）。
限定深度上限 dep[x]+k（不能超过最大深度 dep[p[n]]）。
在版本 rt[dep[x]+k] 这棵包含"深度 ≤ dep[x]+k"节点的线段树上，查询区间 [dfn[x], dfn[x]+sz[x]-1]（即
x
x 的子树）的最小值
复杂度
O
(
(
n
+
q
)
log
⁡
n
)
O((n+q)logn)、空间
O
(
n
log
⁡
n
)
O(nlogn)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e5+5, inf = 0x7f7f7f7f;

struct node { int l, r, mn; } t[N<<6];

int tot, head[N], nxt[N<<1], to[N<<1];
void add(int x, int y) { to[++tot] = y, nxt[tot] = head[x], head[x] = tot; }

int dep[N], dfn[N], sz[N], cnt;
void dfs(int x, int pre) {
    dep[x] = dep[pre]+1; dfn[x] = ++cnt; sz[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        if (to[i] != pre) {
            dfs(to[i], x);
            sz[x] += sz[to[i]];
        }
    }
}
bool cmp(int x, int y) { return dep[x] < dep[y]; }

#define mid ((l+r)>>1)
void build(int& o, int pre, int l, int r, int x, int v) {
    o = ++cnt; t[o] = t[pre];//拷贝上一个版本节点
    if (l == x && r == x) { t[o].mn = v; return; }
    if (x <= mid) build(t[o].l, t[pre].l, l, mid, x, v);
    else build(t[o].r, t[pre].r, mid+1, r, x, v);
    t[o].mn = min(t[t[o].l].mn, t[t[o].r].mn);
}

int query(int o, int l, int r, int L, int R) {
    if (l >= L && r <= R) return t[o].mn;
    int res = inf;
    if (L <= mid) res = min(res, query(t[o].l, l, mid, L, R));
    if (R > mid) res = min(res, query(t[o].r, mid+1, r, L, R));
    return res;
}

int a[N], p[N], rt[N], ans;
signed main() {
    fast;
    t->mn = inf;
    int n, r; cin >> n >> r;
    for (int i = 1; i <= n; cin >> a[i], ++i) {}
    for (int i = 1, x, y; i < n && cin >> x >> y; ++i) add(x, y), add(y, x);
    dfs(r, 0);
    for (int i = 1; i <= n; ++i) p[i] = i;
    sort(p+1, p+1+n, cmp);
    cnt = 0;
    for (int i = 1; i <= n; ++i) build(rt[dep[p[i]]], rt[dep[p[i-1]]], 1, n, dfn[p[i]], a[p[i]]);
    int q; cin >> q;
    while (q--) {
        int x, k; cin >> x >> k;
        x = (x+ans)%n+1, k = (k+ans)%n;
        cout << (ans=query(rt[min(dep[x]+k, dep[p[n]])], 1, n, dfn[x], dfn[x]+sz[x]-1)) << '\n';
    }
    return 0;
}