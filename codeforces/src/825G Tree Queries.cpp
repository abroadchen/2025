//
// Created by Psy.C on 2026/9/23.
//
/**
e[i]：存储第 i 条边，x, y 为端点，w 为边权
标准并查集（带路径压缩），用于 Kruskal 算法中判断连通性、以及合并连通块
在重构树上做第一次 DFS：
sz：子树大小
dep：深度
p：父节点
son：重儿子（子树最大的儿子）
为树链剖分做准备
第二次 DFS，把树剖分成重链：top[x] 是 x 所在重链的链顶。
重儿子继续当前链，轻儿子各开新链
标准的基于重链剖分的 LCA：
不断把链顶更深的点跳到链顶的父亲。
直到两点在同一链上，深度浅的就是 LCA。
单次 LCA 复杂度 O(log n)。
读入边，边权 w = min(x, y)（两个端点编号的较小值）。
按边权 从大到小排序（构造最大生成树 → 对应"最大值瓶颈"的 Kruskal 重构树）
重构树关键性质：图中每条原边合并时新建一个"中间点"，权值为该边边权，作为两端连通块根的父亲。这样最终得到一棵 n + (n-1) = 2n-1 个节点的二叉树（Kruskal 重构树）。
在这棵树上，任意两个原节点的 LCA 的 val，就等于原图中连接这两个节点的路径上某条边的最大/最小"瓶颈值"（这里因为从大到小排序，就是最小值最大意义下的瓶颈，即最大生成树上的最小边...实际对应的是"路径上边权最小值"——取决于排序方向）。这里 val = min(x,y) 且从大到小建，LCA 的 val 恰为两节点路径上边权的最小值中的最大值（最大瓶颈）‍这一语义
真正的查询编号是 (lst + x) % n + 1，必须依赖上一次的输出，无法离线处理，所以叫"强制在线"。

操作 1（op==1）：
维护一个当前点 t，不断和 x 取 LCA。由于多次 LCA 取并，等价于求所有这些点 LCA 的"祖先集合的交"——即逐步求它们的 LCA。

操作 2（op==2）：
求当前 t 与 x 的 LCA 的权值 val，作为答案输出，并更新 lst 用于下一次在线变换
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e6+10;
struct node { int x, y, w; } e[N];

int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int sz[N], dep[N], p[N], son[N];
vector<int> eg[N];
void dfs(int x) {
    sz[x] = 1;
    for (auto v : eg[x]) {
        dep[v] = dep[x] + 1; p[v] = x;
        dfs(v);
        sz[x] += sz[v];
        if (sz[v] > sz[son[x]]) son[x] = v;
    }
}

int top[N];
void dfs2(int x, int t) {
    top[x] = t;
    if (son[x]) dfs2(son[x], t);
    for (auto v : eg[x])
        if (v != son[x]) dfs2(v, v);
}

int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = p[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
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

int n, m, val[N];
int main() {
    fast;
    read(n, m);
    for (int i = 1; i < n; ++i)
        read(e[i].x, e[i].y), e[i].w = min(e[i].x, e[i].y);
    sort(e+1, e+n, [&](const node& x, const node& y) {
        return x.w > y.w;
    });
    int tot = n;
    //初始：每个原节点是自己的连通块，val=自身编号
    for (int i = 1; i <= n; ++i) fa[i] = val[i] = i;
    for (int i = 1; i < n; ++i) {
        int x = e[i].x, y = e[i].y, w = e[i].w;
        x = find(x), y = find(y);
        ++tot; //新建一个"虚点"
        val[tot] = w;//该虚点权值 = 这条边权
        eg[tot].push_back(x); eg[tot].push_back(y);//虚点为两连通块的父亲
        fa[x] = fa[y] = fa[tot] = tot;// 合并连通块
    }
    dfs(tot); dfs2(tot, tot);
    int lst = 0, t = 0;
    while (m--) {
        int op, x; read(op, x);
        x = (lst + x) % n + 1;
        if (op == 1) {
            if (!t) t = x; else t = LCA(t, x);
        } else {
            lst = val[LCA(t, x)];
            cout << lst << '\n';
        }
    }
    return 0;
}