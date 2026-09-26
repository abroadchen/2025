//
// Created by Psy.C on 2026/9/26.
//
/**
fd[u]：从根到 u 沿树边的距离和。
b[u]：点 u 的附加点权
dfn[u]：DFS 序编号（每个点一个连续区间）。
sz[u]：子树大小，子树在 DFS 序上对应区间 [dfn[u], dfn[u]+sz[u]-1]。
fd[u]：根到 u 的树边距离。
这是把树上子树查询转化为区间查询的关键
叶子节点（对应 DFS 序位置 l）存的值 = b[该点] + fd[该点]。
线段树支持区间加（update）和区间最小值查询（query），带 lazy tag。
核心思想：b[u] + fd[u] 可理解为"从 u 走到某个"出口"的某种代价"，后续更新和查询都围绕它
对树边 i（1..n-1），down[i] = 该边较深的那个端点（子端）。
对点权边 i（n..2n-2），down[i] = 挂载的点 u。
这样"改一条边权"就对应"改某个点"的线段树区间
修改树边 x：该边较深端点 p 的子树内，所有点的 fd 都会变化 delta，所以对 p 的整个子树区间 [dfn[p], dfn[p]+sz[p]-1] 做区间加。
修改点权 b：只影响该单点 p，对它对应叶子做单点加（dfn[p], dfn[p]）
st.query(dfn[p], dfn[p]) - b[p] = 该点的 fd[p]（因为叶子存的是 b+fd，减去 b 得 fd）。记作 dx、dy。
mn = x 子树内最小的 (b+fd)：即从 x 出发往子树内走能到达的最小代价（相当于"出口在最省的地方"）。
两种情况：
y 在 x 子树内：直接 dy − dx（即两点的 fd 之差），因为不用绕道其他出口。
y 不在 x 子树内：路径需要先从 x 往下走到子树内某个"出口"（取子树最小 mn），加上从那个出口到 y 的距离。因为 mn = (b+fd) 最小，而 fd 只含树边部分（不含点权 b），所以"到出口的树边代价 + y 的点权差"组合成 mn − dx + dy。
这个 dy 部分其实叠加了点权 b 的差异（因为叶子存 b+fd）。整体就是在维护"最小化到出口的树边距离，再切换到 y"的最短路思路。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 2e5+5;

struct edge { int u, v, w; } e[N<<1];

ll b[N], fd[N];
int ord[N];
struct sgt {
    struct node { ll mn, tag; } t[N<<1];
    void push(int u, ll tg) { t[u].mn += tg; t[u].tag += tg; }
    int ls[N<<1], rs[N<<1];
    void push_up(int u) { t[u].mn = min(t[ls[u]].mn, t[rs[u]].mn); }
    void push_down(int u) {
        if (t[u].tag != 0) {
            push(ls[u], t[u].tag); push(rs[u], t[u].tag);
            t[u].tag = 0;
        }
    }
    int tot;
    int build(int l, int r) {
        int u = ++tot;
        if (l == r) {
            t[u] = {.mn = b[ord[l]]+fd[ord[l]], .tag = 0};
            return u;
        }
        int mid = (l + r) >> 1;
        ls[u] = build(l, mid); rs[u] = build(mid+1, r);
        push_up(u);
        return u;
    }
    void update(int u, int l, int r, int L, int R, ll k) {
        if (L <= l && R >= r) { push(u, k); return; }
        int mid = (l + r) >> 1;
        push_down(u);
        if (L <= mid) update(ls[u], l, mid, L, R, k);
        if (R > mid) update(rs[u], mid + 1, r, L, R, k);
        push_up(u);
    }
    ll query(int u, int l, int r, int L, int R) {
        if (L <= l && R >= r) return t[u].mn;
        int mid = (l + r) >> 1;
        push_down(u);
        if (R <= mid) return query(ls[u], l, mid, L, R);
        if (L > mid) return query(rs[u], mid + 1, r, L, R);
        return min(query(ls[u], l, mid, L, R), query(rs[u], mid + 1, r, L, R));
    }
} st;

int dfn[N], cnt, sz[N], dep[N];
vector<ii> g[N];
void dfs(int u, int fa) {
    dfn[u] = ++cnt; ord[cnt] = u; sz[u] = 1; dep[u] = dep[fa] + 1;
    for (auto [fst, snd] : g[u]) {
        int v = fst, w = snd;
        if (v == fa) continue;
        fd[v] = fd[u] + w;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

int n, q, down[N<<1];
int main() {
    fast;
    cin >> n >> q;
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        e[i] = {.u = u, .v = v, .w = w};
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        e[i+n-1] = {.u = u, .v = v, .w = w};
        b[u] = w;
    }
    dfs(1, 0);
    for (int i = 1; i <= 2*n-2; ++i) {
        int u = e[i].u, v = e[i].v;
        if (i < n) {
            if (dep[u] > dep[v]) down[i] = u;
            else down[i] = v;
        } else down[i] = u;
    }
    st.build(1, n);
    while (q--) {
        int op, x, y, w; cin >> op;
        if (op == 1) {
            cin >> x >> w;
            if (x < n) {
                int p = down[x], delta = w - e[x].w;
                st.update(1, 1, n, dfn[p], dfn[p]+sz[p]-1, delta);
                e[x].w = w;
            } else {
                int p = down[x], delta = w - b[p];
                st.update(1, 1, n, dfn[p], dfn[p], delta);
                b[p] = w;
            }
        } else {
            cin >> x >> y;
            if (dfn[x] <= dfn[y] && dfn[y] <= dfn[x] + sz[x] - 1) {
                ll dx = st.query(1, 1, n, dfn[x], dfn[x]) - b[x],
                dy = st.query(1, 1, n, dfn[y], dfn[y]) - b[y];
                cout << dy - dx << '\n';
            } else {
                ll dx = st.query(1, 1, n, dfn[x], dfn[x]) - b[x],
                dy = st.query(1, 1, n, dfn[y], dfn[y]) - b[y],
                mn = st.query(1, 1, n, dfn[x], dfn[x]+sz[x]-1);
                cout << mn - dx + dy << '\n';
            }
        }
    }
    return 0;
}