//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
邻接表存边，inf = 1e9+1 表示"极大/未确定"权值。
n 点，强制边 k 条，候选边 m 条
求子树大小 sz、深度 dep、父节点 fa、重儿子 son。
val[to] = 从 fa 到 to 的边权（后面用来初始化线段树叶节点）
dfn[pos]：DFS 序（重链优先），b[cnt] 记录对应 dfn 的点编号。
重儿子延用同一 top，轻儿子新开一条重链
叶节点初始为边权。
upd(k,w)：把节点值设为 w 并打标记（表示"这段区间最终被压到 w，只要原值 ≥ w"）。
push_down：下传标记时，只有子区间值 ≥ w 才更新——这确保不会把更小值变大，维护的是"取所有覆盖操作的最小值"
区间更新：把 [L,R] 内所有 > w 的边权压到 w。若整段 mx 已经 ≤ w（即 w > mx），则无需更新，直接返回
change(a,b,w)：对 a→b 路径上的所有边做区间取 min 为 w。注意 dfn[b]+1 是为了排除 LCA 节点本身（因为 dfn 存的是节点，而我们要操作的是边，用后一条边的 dfn）
put 把线段树结果回写到 ans[点] —— 每个节点的答案即该点作为"边（父→子）"的最终权值

强制边 g[i]：先连起来，权值设 inf，并合并并查集。
可选边 f[i]：先读入，标记 in=false。
用 Kruskal（按权排序 + 并查集）选出可作为树边的可选边（in=true），权值先设为 0。
这些树边 + 强制边共同构成一棵生成树。
剖分整棵树，构建线段树。叶 = 边权（强制边为 inf，树边为 0
对每条非树边 f[i]（权 w），其在树上的 a→b 路径上，所有边权值都不能大于 w（否则该非树边就可替换掉更大权值的树边构成更优 MST 违背性质）。
所以对 a 到 LCA、b 到 LCA 的链路径上每条边做区间取 min 为 w。
多个非树边可能覆盖同一条边，最后取所有约束的最小值
若某条边最终仍是 inf（从未被任何非树边约束），说明无法满足 → 输出 -1。
否则累加所有边权值得总和。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 1; i <= n; i++)
#define ll long long
using namespace std;

constexpr int N = 5e5+5, inf = 1e9+1;
struct edge { int to, nxt, w; } d[N<<1];

int tot, head[N];
void add(int x, int y, int w) {
    d[++tot] = {y,head[x],w}, head[x] = tot;
}

int n, ans[N];
struct tcp {
    int sz[N], dep[N], fa[N], val[N], son[N];
    void dfs(int pos, int f) {
        sz[pos] = 1; dep[pos] = dep[f] + 1, fa[pos] = f;
        for (int i = head[pos]; i; i = d[i].nxt) {
            int to = d[i].to;
            if (to == f) continue;
            val[to] = d[i].w;
            dfs(to, pos);
            sz[pos] += sz[to];
            if (sz[son[pos]] < sz[to]) son[pos] = to;
        }
    }
    int dfn[N], cnt, top[N], b[N];
    void dfs2(int pos, int rt) {
        dfn[pos] = ++cnt, top[pos] = rt; b[cnt] = pos;
        if (son[pos]) dfs2(son[pos], rt);
        for (int i = head[pos]; i; i = d[i].nxt) {
            int to = d[i].to;
            if (top[to]) continue;
            dfs2(to, to);
        }
    }
#define ls k<<1
#define rs (k<<1|1)
#define mid ((l+r)>>1)
    int mx[N<<2], tag[N<<2];
    void push_up(int k) { mx[k] = max(mx[ls], mx[rs]); }
    void upd(int k, int w) { mx[k] = w, tag[k] = w; }
    void push_down(int k) {
        if (!tag[k]) return;
        if (mx[ls] >= tag[k]) upd(ls, tag[k]);
        if (mx[rs] >= tag[k]) upd(rs, tag[k]);
        tag[k] = 0;
    }
    void build(int k, int l, int r) {
        if (l == r) { mx[k] = val[b[l&r]]; return; }
        build(ls, l, mid), build(rs, mid+1, r);
        push_up(k);
    }
    void add(int k, int l, int r, int L, int R, int w) {
        if (w > mx[k]) return;
        if (L <= l && r <= R) return upd(k, w);
        push_down(k);
        if (L <= mid) add(ls, l, mid, L, R, w);
        if (mid < R) add(rs, mid+1, r, L, R, w);
        push_up(k);
    }
    int LCA(int a, int b) {
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            a = fa[top[a]];
        }
        if (dep[a] > dep[b]) return b;
        return a;
    }
    void change(int a, int b, int w) {
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            add(1,1,n,dfn[top[a]], dfn[a], w);
            a = fa[top[a]];
        }
        if (a == b) return;
        if (dep[a] < dep[b]) swap(a, b);
        add(1,1,n,dfn[b]+1, dfn[a], w);
    }
    void put(int k, int l, int r) {
        if (l == r) { ans[b[l&r]] = mx[k]; return; }
        push_down(k);
        put(ls, l, mid), put(rs, mid+1, r);
    }
} TCP;

struct node {
    int a, b, w; bool in;
    bool operator<(const node &o) const {
        return w < o.w;
    }
} f[N], g[N];

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int k, m;
ll ret;
int main() {
    fast; int i;
    cin >> n >> k >> m;
    rep(i,n) fa[i] = i;
    rep(i,k) {
        cin >> g[i].a >> g[i].b;
        add(g[i].a, g[i].b, inf), add(g[i].b, g[i].a, inf);
        fa[find(g[i].a)] = find(g[i].b);
    }
    rep(i,m) cin >> f[i].a >> f[i].b >> f[i].w, f[i].in = false;
    sort(f+1, f+m+1);
    rep(i,m) {
        int x = find(f[i].a), y = find(f[i].b);
        if (x == y) continue;
        f[i].in = true;
        fa[x] = y;
        add(f[i].a, f[i].b, 0); add(f[i].b, f[i].a, 0);
    }
    TCP.dfs(1, 0); TCP.dfs2(1, 1);
    TCP.top[1] = TCP.fa[1] = 1; TCP.build(1,1,n);
    rep(i,m) if (!f[i].in) {
        int lca = TCP.LCA(f[i].a, f[i].b);
        TCP.change(f[i].a, lca, f[i].w);
        TCP.change(f[i].b, lca, f[i].w);
    }
    TCP.put(1,1,n);
    rep(i,n) {
        if (ans[i] == inf) return cout << "-1", 0;
        ret += (ll)ans[i];
    }
    cout << ret << '\n';
    return 0;
}