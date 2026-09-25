//
// Created by Psy.C on 2026/9/24.
//
/**
E[]：存边，含两端点、权值、原始编号 id。
cmp：按权值排序（用于 Kruskal 建 MST）。
cmp2：按 id 排序（用于最终输出）
标准并查集（带路径压缩）
anc[u][i]：u 向上跳 2^i 步的祖先。
dep[u]：深度。
w[u][i]：u 向上跳 2^i 步这段路径上的最大边权。
e[v]：边 (v 到其父节点) 的原始编号（用于后续给树边赋值答案）。
to[u]/W[u]：邻接表，W 存边编号。
预处理：DFS 建立倍增表，w[u][0] = 到父边权，逐级取 max
标准 LCA + 路径最大值查询（先拉平深度，再一起上跳），返回 u-v 路径上的最大边权，lca 通过引用带出
这条函数用于处理树边的答案：对所有"被某条非树边覆盖"的树上边，更新 ans。
用并查集做路径压缩跳跃：从 u 一路向上到 v（lca），对每条经过的树边 e[u] 赋 ans = val - 1，然后利用并查集把这条边"跳过"（下次不再重复访问），保证每条树边只会被赋值一次（由权值最小的覆盖它的非树边决定）。这就实现了"取最小值"

读入所有边，记 id。
Kruskal 建 MST：按权值升序，用并查集把能连通的边加入（to/W 建树），加入 MST 失败的边放进 NT（非树边）。
按 id 恢复原顺序。
dfs(1,1) 建倍增表（路径最大边权）。
重置并查集。
对每条非树边 t：
求它在 MST 树上路径的最大边权，则 ans[t] = 最大边权 - 1（非树边必须比路径上最大边小才能替换）。
调用 modify 把这条非树边对路径上所有树边的影响应用上：树边的 ans 更新为 该非树边权值 - 1（因为是按非树边权值从小到大处理，并用并查集跳过已赋值树边，保证每个树边取到的是最小的覆盖它的非树边权值 − 1）。
最后输出：ans 仍为初始值 inf（即从未被赋值）的边输出 -1，否则输出 ans。
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5+5, M = 17, inf = 0x3f3f3f3f;

struct edge { int u, v, w, id; } E[N];

inline bool cmp(const edge& a, const edge& b) {
    return a.w < b.w;
}
inline bool cmp2(const edge& a, const edge& b) {
    return a.id < b.id;
}
int fa[N];
inline int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int anc[N][M+3], dep[N], w[N][M], e[N];
vector<int> to[N], W[N];
void dfs(int u, int f) {
    anc[u][0] = f; dep[u] = dep[f] + 1;
    for (int i = 1; i < M; ++i) {
        anc[u][i] = anc[anc[u][i-1]][i-1];
        w[u][i] = max(w[u][i-1], w[anc[u][i-1]][i-1]);
    }
    int sz = to[u].size();
    for (int i = 0; i < sz; ++i) {
        int v = to[u][i];
        if (v == f) continue;
        e[v] = W[u][i]; w[v][0] = E[W[u][i]].w;
        dfs(v, u);
    }
}

int query(int u, int v, int& lca) {
    if (dep[u] < dep[v]) swap(u, v);
    int ret = -inf, d = dep[u] - dep[v];
    for (int i = 0; d; d >>= 1, ++i)
        if (d&1) {
            ret = max(ret, w[u][i]);
            u = anc[u][i];
        }
    if (u == v) { lca = u; return ret; }
    for (int i = M-1; i >= 0; --i) {
        if (anc[u][i] != anc[v][i]) {
            ret = max(ret, w[u][i]);
            ret = max(ret, w[v][i]);
            u = anc[u][i]; v = anc[v][i];
        }
    }
    ret = max(ret, w[u][0]);
    ret = max(ret, w[v][0]);
    lca = anc[u][0];
    return ret;
}

int ans[N];
void modify(int u, int v, int val) {
    u = find(u);
    if (dep[u] < dep[v]) return;
    while (dep[u] > dep[v]) {
        ans[e[u]] = val-1;
        int nxt = find(anc[u][0]);
        fa[find(u)] = nxt;
        u = nxt;
    }
}


int n, m;
vector<int> NT;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].w);
        E[i].id = i;
    }
    sort(E+1, E+m+1, cmp);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) {
        int u = E[i].u, v = E[i].v;
        int fx = find(u), fy = find(v);
        if (fx != fy) {
            fa[fx] = fy;
            to[u].push_back(v); to[v].push_back(u);
            W[u].push_back(E[i].id);
            W[v].push_back(E[i].id);
        } else NT.push_back(E[i].id);
    }
    sort(E+1, E+m+1, cmp2);
    memset(w, 0x3f, sizeof w);
    memset(ans, 0x3f, sizeof ans);
    dfs(1, 1);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    int sz = NT.size();
    for (int i = 0; i < sz; ++i) {
        int t = NT[i], lca;
        ans[t] = query(E[t].u, E[t].v, lca) - 1;
        modify(E[t].u, lca, E[t].w);
        modify(E[t].v, lca, E[t].w);
    }
    for (int i = 1; i <= m; ++i) {
        if (ans[i] >= inf-1) printf("-1 ");
        else printf("%d ", ans[i]);
    }
    return 0;
}