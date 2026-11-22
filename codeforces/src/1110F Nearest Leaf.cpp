//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
标准树 + 重链剖分要用到的数组。
sum[i]：自根到 i 的点权之和（用作树上距离）
自根向下：sum[x] = sum[f]+w[x]（前缀权值）；dep[x]=dep[f]+1；sz[x] 初始为 1。
遍历孩子递归，累加子树大小，并记录最大子树儿子作为重儿子 son[x]
给每个节点分配 dfs 序 dfn[x]，并用 st[tim]=x 记录"第 tim 个 dfs 序对应的节点"（用于通过 dfn 反查节点）。
tp[x]：链顶。重儿子跟着父亲同一链顶 f；轻儿子自己作为新链顶 v。
fa[x]：父节点
经典重链剖分 LCA：两个点不在同一链顶时，把更深那条链的链顶跳到它的父节点，直到同一链，最后返回深度较小的点
后序遍历（先孩子后自己）。
- mn[x]：子树内所有叶子（或所有子孙中）"sum 前缀权值和"的最小值。
- ln / rn：按节点编号与重儿子的关系（v < son[x] 归到 ln，v > son[x] 归到 rn）分别收集左右子树的最小 mn。
叶子节点 mn[x] = sum[x]（叶子自己就是终点）。
这里再次体现节点编号有序：ln（编号比重儿子小的孩子儿子集合的最小值）、rn（编号比重儿子大的）
通用 ST 表（稀疏表）实现 RMQ 最小值。
get()：预处理 lg2 和每层区间最小值。
find(l,r)：返回 [l,r] 区间最小值（O(1)），越界返回 inf。
声明了三张 ST 表：stt、sl、sr
d = sum[x]，ans 初始为 inf。
把 x 相对 [l,r] 的范围进行修正（用编号比较）。然后取 xl=LCA(x,l)、xr=LCA(x,r)
利用树上距离公式：dist(x,y) = sum[x]+sum[y]-2*sum[LCA(x,y)]。所以 d + (子树的某 sum) - sum[x]*2 就是在计算从 x 到某个点的距离。
stt.find(...) 取 x 子树中 dfn 在 [l,r] 范围内叶子的最小 sum，再用距离公式累计候选答案。
通过重链剖分 + LCA 逐步上跳，用 sl / sr（左右两侧预处理的"距离转换值"）来 O(1) 求区间最小距离，并在每段尝试更新 ans。
不断把 x 上移到链顶父亲，直到 xl、xr 都归 0
整体目的：在值域区间 [l,r] 对应的节点集合里，找出距离 x 最近（距离最小）的点
读入 n, q；读每个节点的父节点 fa[i] 和权值 w[i]，建树。
对每个节点的邻接表按编号排序（因为后续 min 判断基于编号大小）。
三次 DFS 完成预处理（sum/dep/sz/son、重链 dfn/tp、子树最小 mn/ln/rn）。
构建三张 ST 表：
stt：dfn 位置对应节点若是叶子则值为 sum[i]，否则 inf —— 用于查"区间内叶子的最小 sum"。
sl：ln[st[i]] - sum[st[i]]*2 —— 把距离公式中的 sum[y]-2*sum[x] 部分预处理好，便于 O(1) 求左区间最近距离。
sr：同理右区间。
最后对每个询问调用 solve 并输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define rep1(i,n) for (int i = 1; i <= n; i++)
#define ll long long
using namespace std;

constexpr int N = 5e5+5;
constexpr ll inf = 1e18;

ll sum[N];
int w[N], dep[N], sz[N], son[N];
vector<int> g[N];
void dfs(int x, int f) {
    sum[x] = sum[f] + w[x]; dep[x] = dep[f] + 1; sz[x] = 1;
    rep(i,g[x].size()) {
        int v = g[x][i];
        if (v == f) continue;
        dfs(v, x);
        sz[x] += sz[v];
        if (sz[v] > sz[son[x]]) son[x] = v;
    }
}

int dfn[N], tim, st[N], tp[N], fa[N];
void dfs2(int x, int f) {
    dfn[x] = ++tim; st[tim] = x; tp[x] = f;
    if (son[x]) dfs2(son[x], f);
    rep(i,g[x].size()) {
        int v = g[x][i];
        if (v == fa[x] || v == son[x]) continue;
        dfs2(v, v);
    }
}
int LCA(int x, int y) {
    while (tp[x] != tp[y]) {
        if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
        x = fa[tp[x]];
    }
    if (dep[x] < dep[y]) return x;
    return y;
}

ll mn[N], ln[N], rn[N];
void dfs3(int x) {
    mn[x] = ln[x] = rn[x] = inf;
    rep(i,g[x].size()) {
        int v = g[x][i];
        dfs3(v);
        mn[x] = min(mn[x], mn[v]);
        if (v < son[x]) ln[x] = min(ln[x], mn[v]);
        if (v > son[x]) rn[x] = min(rn[x], mn[v]);
    }
    if (g[x].size() == 0) mn[x] = sum[x];
}

int n;
struct ST {
    int lg2[N];
    ll st[N][20];
    void get() {
        for (int i = 2; i <= n; i++) lg2[i] = lg2[i>>1]+1;
        rep1(j,lg2[n]) rep1(i,n)
            st[i][j] = min(st[i][j-1],st[min(n,i+(1<<(j-1)))][j-1]);
    }
    ll find(int l, int r) {
        if (l > r) return inf;
        int k = lg2[r-l+1];
        return min(st[l][k],st[r-(1<<k)+1][k]);
    }
} stt, sl, sr;

ll solve(int x, int l, int r) {
    ll d = sum[x], ans = inf;
    if (x < l) x = LCA(x,l);
    if (x > r) x = LCA(x,r);
    int xl = LCA(x,l), xr = LCA(x,r);
    bool f = 0;
    while (xl || xr) {
        ans = min(ans,stt.find(max(l,x),min(x+sz[x]-1,r))+d-sum[x]*2);
        if (xl == x) xl = 0;
        if (xr == x) xr = 0;
        if (f == 0) { f = x != tp[x], x = fa[x]; continue; }
        int v = tp[x];
        if (dep[v] <= dep[xl]) v = st[dfn[xl]+1];
        if (dep[v] <= dep[xr]) v = st[dfn[xr]+1];
        if (xl) ans = min(ans,d+sl.find(dfn[v],dfn[x]));
        if (xr) ans = min(ans,d+sr.find(dfn[v],dfn[x]));
        x = fa[v]; f = 0;
    }
    return ans;
}

int q;
int main() {
    fast;
    cin >> n >> q;
    for (int i = 2; i <= n; i++) cin >> fa[i] >> w[i], g[fa[i]].push_back(i);
    rep1(i,n) ranges::sort(g[i]);
    dfs(1,0); dfs2(1,1); dfs3(1);
    rep1(i,n) stt.st[i][0] = g[i].empty()?sum[i]:inf;
    rep1(i,n) sl.st[i][0] = ln[st[i]]-sum[st[i]]*2, sr.st[i][0] = rn[st[i]]-sum[st[i]]*2;
    stt.get(); sl.get(); sr.get();
    rep1(i,q) {
        int x, l, r; cin >> x >> l >> r;
        cout << solve(x,l,r) << '\n';
    }
    return 0;
}