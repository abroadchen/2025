//
// Created by Psy.C on 2026/11/7.
//

/**
真正学会的起点..
e[]：原图邻接表。
r[]：圆方树（round-square tree），大小开到 n（圆点）+ 块数（方点），所以是 N<<1。
st：Tarjan 用的栈。
dfn[]、low[]、tim：Tarjan 时间戳。
cnt：当前节点/方点编号计数（初始 cnt=n，每个点双对应一个新"方点"）
这是「点双连通分量 → 圆方树」的标准写法：

圆点 = 原图的点（编号 1..n）。
方点 = 每个点双连通分量（编号 n+1..），cnt 从 n 开始自增。
当 low[v] == dfn[u] 时，说明 u 是割点，且从 u 到 v 这条子树路径构成了一个新的点双：
弹栈直到 v，这一段的点都属于该点双；
将它们与新方点 cnt 连边（圆点—方点相连）；
最后把割点 u 也连进这个方点。
方点与圆点之间用 r[] 连接，形成一棵树（圆方树）。
圆方树的经典性质：原图中两个圆点之间的"必经割点/桥梁"，对应圆方树上它们之间路径中的方点序列。
main 里 rep(i,n) if(dfn[i]==0) dfs(i), st.clear(); 处理多连通分量（图可能不连通）
rdep[]：普通树深度（用于 LCA 的倍增对齐）。
fa[][20]：倍增跳表。
dep[] 是关键：dep[v] = dep[u] + (v > n)，即只有走到方点时 dep 才 +1，走到圆点不加。
含义：dep 记录的是从根到该点路径上经过的方点（即点双/关键枢纽）个数。
这样设计是为了后续回答：dep 的差值恰好给出路径上必经的"割点终节点"数量
标准倍增 LCA，基于 rdep 深度对齐。无额外内容。

cnt=n：方点从 n+1 开始编号。
读 m 条边建原图。
对每个未访问的点跑 Tarjan（图可能不连通），把整个图建成圆方树。
dfs2(1)：从 1 号圆点做树上的 dep/rdep/倍增初始化。
对每个查询 (u,v)

dep[u] + dep[v]：两点到根方点数之和；
- dep[l]：减 LCA 的一次；
- dep[fa[l][0]]：再减 LCA 父亲那一段（避免重复计割点归属），最终得到路径上方的方点个数。
这个值恰好等于：原图中 u 到 v 的路径上必须经过的割点（关键点）的数量
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define per(i,n) for (int i=n; i>=0; i--)
using namespace std;

constexpr int N = 1e5+10;

vector<int> st, e[N], r[N<<1];
int dfn[N], low[N], tim, cnt;
void dfs(int u) {
    st.push_back(u); dfn[u] = low[u] = ++tim;
    for (int v : e[u]) {
        if (dfn[v]) { low[u] = min(low[u], dfn[v]); continue; }
        dfs(v);
        low[u] = min(low[u], low[v]);
        if (low[v] == dfn[u]) {
            cnt++;
            while (st.back() != v) {
                r[cnt].push_back(st.back());
                r[st.back()].push_back(cnt); st.pop_back();
            }
            r[cnt].push_back(st.back());
            r[st.back()].push_back(cnt); st.pop_back();
            r[cnt].push_back(u), r[u].push_back(cnt);
        }
    }
}

int rdep[N<<1], fa[N<<1][20], dep[N<<1], n;
void dfs2(int u, int fa=0) {
    rdep[u] = rdep[fa] + 1;
    ::fa[u][0] = fa;
    rep(i,19) ::fa[u][i] = ::fa[::fa[u][i-1]][i-1];
    for (int v : r[u]) {
        if (v == fa) continue;
        dep[v] = dep[u] + (v > n);
        dfs2(v, u);
    }
}

int LCA(int u, int v) {
    if (rdep[u] < rdep[v]) swap(u, v);
    per(i,19) if (rdep[fa[u][i]] >= rdep[v]) u = fa[u][i];
    if (u == v) return u;
    per(i,19) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int m, q;
int main() {
    fast;
    read(n,m,q); cnt = n;
    rep(i,m) {
        int u, v; read(u, v);
        e[u].push_back(v); e[v].push_back(u);
    }
    rep(i,n) if (dfn[i] == 0) dfs(i), st.clear();
    dfs2(1);
    rep(i,q) {
        int u, v; read(u, v);
        int l = LCA(u, v);
        write(dep[u]+dep[v]-dep[l]-dep[fa[l][0]]), putchar('\n');
    }
    return 0;
}