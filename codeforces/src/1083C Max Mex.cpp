//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
建立欧拉序（出进序）‍：每进入、离开节点都记录一次，tot 最终 = 2n-1。
st[tot][0] = {深度 d, 节点 u}，用深度做 RMQ 的最小值，就可以求 LCA
对区间做按深度取最小的倍增 RMQ，建立 ST 表。lg 预处理区间长度 log
用 LCA 的经典公式：dist = dis[u] + dis[v] − 2·dis[LCA]。z 是从区间 RMQ 取深度最小得到的 LCA
判定「x 是否在 u-v 的树上路径上」：若 dist(x,u)+dist(x,v)==dist(u,v)，则 x 在 u,v 的路径上（三角形等式）
{x, y, f} 表示该区间对应的节点集合，其路径并若是一条路径则 f==1 且两端点为 {x,y}；f==0 表示不是一条路径（无法表示）；f==2 表示空集/无节点（哨兵）。
两个区间各自是一段路径（端点 {p,q} 与 {s,t}）。合并后要想仍是一条路径，其端点必然在 {p,q,s,t} 这 4 个点里取 2 个。代码枚举 6 种端点组合（C(4,2)=6），用 chk 验证另外两个点是否落在形成的路径上；找到一种满足两端都在路径上的组合即为合并结果，否则 f=0（非法）。这是经典的"路径并/路径合并"线段树技巧。
push_up：d[o]=merge(左, 右)。

build：叶子 d[o]={c[l], c[l], 1}（单个节点本身就是一条路径，端点相同）。

注意：c[l] 把线段树下标 l 映射回排列 p 中值 = l 对应的树节点（因为 c[p[i]+1]=i，反过来 c[t] 给的是"p 中值为 t 的节点号"）。也就是说线段树第 t 个位置存储的是"排列值为 t 的那个树节点"。
modify(pos, x)：单点更新该位置对应的节点
若把当前已合法前缀 x 与整段 d[o] 合并仍合法，说明能延伸到 r，返回 r。
否则：若左半合并就非法，去左半找断点；若左半合并合法，则带着合并后的左半（更新 x）去右半找第一个让合并非法的位置。
这是线段树上的"找出前缀中最后一个合法位置"的二分式查询（O(log n)）
{0,0,2} 作为查询起点（f=2 表示"空集"，merge 时会直接返回右侧）。
修改：交换 p[x]、p[y]，同步更新线段树上对应两个位置（把位置 p[x]+1 存的值从 x 改成 y，p[y]+1 从 y 改成 x）。注意下标 +1 因为排列值从 0/1 起始映射到线段树（c[p[i]+1]=i）

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ii pair<int, int>
#define mid ((l+r)>>1)
#define int long long
using namespace std;

constexpr int N = 4e5+5;

int dfn[N], tot, dis[N];
ii st[N][20];
vector<int> G[N];
void dfs(int u, int fa, int d) {
    dfn[u] = ++tot; st[tot][0] = {d, u};
    for (int v : G[u]) {
        if (v == fa) continue;
        dis[v] = dis[u] + 1, dfs(v, u, d+1);
        dfn[u] = ++tot; st[tot][0] = {d, u};
    }
}

int n, lg[N];
void build() {
    assert(tot==2*n-1);
    for (int i = 2; i <= tot; i++) lg[i] = lg[i>>1]+1;
    rep(j,19) for (int i = 1; i+(1<<j)-1 <= tot; i++)
        st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
}
int dist(int u, int v) {
    int l = dfn[u], r = dfn[v];
    if (l > r) swap(l, r);
    int k = lg[r-l+1], z = min(st[l][k], st[r-(1<<k)+1][k]).second;
    return dis[u] + dis[v] - 2*dis[z];
}
bool chk(int x, int u, int v) { return dist(x,u) + dist(x, v) == dist(u, v); }

struct node { int x, y, f; };

int c[N];
struct sgt {
    node d[N<<2];
    node merge(node ls, node rs) {
        if (ls.f == 2) return rs;
        if (rs.f == 2) return ls;
        if (!ls.f || !rs.f) return {0,0,0};
        int p = ls.x, q = ls.y, s = rs.x, t = rs.y;
        if (chk(p,s,t)&&chk(q,s,t)) return {s,t,1};
        if (chk(p,q,t)&&chk(s,q,t)) return {q,t,1};
        if (chk(q,p,t)&&chk(s,p,t)) return {p,t,1};
        if (chk(p,q,s)&&chk(t,q,s)) return {q,s,1};
        if (chk(q,p,s)&&chk(t,p,s)) return {p,s,1};
        if (chk(s,p,q)&&chk(t,p,q)) return {p,q,1};
        return {0,0,0};
    }
    void push_up(int o) { d[o] = merge(d[o<<1], d[o<<1|1]); }
    void build(int l, int r, int o) {
        if (l == r) { d[o] = {c[l], c[l], 1}; return; }
        build(l, mid, o<<1), build(mid+1, r, o<<1|1);
        push_up(o);
    }
    void modify(int pos, node x, int l, int r, int o) {
        if (l == r) { d[o] = x; return; }
        if (pos <= mid) modify(pos, x, l, mid, o<<1);
        else modify(pos, x, mid+1, r, o<<1|1);
        push_up(o);
    }
    int query(node x, int l, int r, int o) {
        if (merge(x,d[o]).f==1) return r;//整段合并合法 → 前缀延伸到 r
        if (l == r) return l-1;//单点也合并不上 → 到 l 为止
        if (!merge(x,d[o<<1]).f) return query(x,l,mid,o<<1);//左半就非法 → 向左递归
        return query(merge(x,d[o<<1]), mid+1, r, o<<1|1);//否则带着已合法的左半，向右找第一个断点
    }
} tr;


inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int p[N];
signed main() {
    fast;
    n = rd();
    rep(i,n) p[i] = rd(), c[p[i]+1] = i;//读排列，记录"值→位置"
    for (int i = 2; i <= n; i++) { int f = rd(); G[i].push_back(f), G[f].push_back(i); }
    dfs(1, 0, 1); build(); tr.build(1,n,1);
    int q = rd();
    while (q--) {
        int op = rd();
        if (op == 1) {
            int x = rd(), y = rd();
            tr.modify(p[x]+1, {y,y,1}, 1, n, 1);//位置(值p[x]处)改为 y
            tr.modify(p[y]+1,{x,x,1}, 1, n, 1);//位置(值p[y]处)改为 x
            swap(p[x], p[y]);//更新排列
        } else cout << tr.query({0,0,2}, 1, n, 1) << '\n';//求最大合法前缀长度
    }
    return 0;
}