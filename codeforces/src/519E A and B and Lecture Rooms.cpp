//
// Created by Psy.C on 2026/3/1.
//
/**

计算路径中点数
k：LCA，d：距离
如果距离为奇数，返回0
如果距离为0，返回n
如果路径对称：计算去除两个子树后的节点数
如果路径不对称：找到中点并计算相应子树大小

k：u和v的最近公共祖先
d：u到v的路径长度 = dep[u] + dep[v] - 2*dep[k]
如果路径长度为奇数，不存在中点，返回0
因为中点必须距离两端点距离相等
如果u == v（距离为0），整棵树都是"中点"，返回n
同时向上移动u和v，直到它们相邻（中间就是中点）
u和v最终停在LCA的儿子节点上
中点数 = 总节点数 - u子树节点数 - v子树节点数
确保u比v离LCA更远
便于统一处理
d/2：从u到中点需要向上移动的步数
d/2 - 1：但需要先移动到中点的父亲，所以-1
mid = u：从u开始向上移动
二进制分解移动：将t = d/2 - 1分解为2的幂次之和
fa[mid][0]：中点的父亲节点
siz[fa[mid][0]] - siz[mid]：中点所在子树的节点数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+1, M = 32;
struct node { int v, nxt; } e[N<<1];

int cnt, head[N];
inline void add(const int u, const int v) {
    e[++cnt] = {v, head[u]}, head[u] = cnt;
    e[++cnt] = {u, head[v]}, head[v] = cnt;
}

int siz[N], fa[N][M], dep[N];
void dfs(const int u, const int f) {
    siz[u] = 1; fa[u][0] = f; dep[u] = dep[fa[u][0]] + 1;
    for (int i = 1; i < M-1; ++i) fa[u][i] = fa[fa[u][i-1]][i-1];
    for (int i = head[u]; i; i = e[i].nxt) {
        const int v = e[i].v;
        if (v == f) continue;
        dfs(v, u);
        siz[u] += siz[v];
    }
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    int t = dep[v] - dep[u];//v需要向上移动的步数
    for (int j = 0; t; ++j, t >>= 1)
        if (t&1) v = fa[v][j];
    if (u == v) return u;//u是v的祖先
    for (int j = M-2; j >= 0 && u != v; --j)
        if (fa[u][j] != fa[v][j])//还可以向上跳跃而不相遇
            u = fa[u][j], v = fa[v][j];
    return fa[u][0];//父节点就是LCA
}

int solve(int u, int v, const int n) {
    const int k = lca(u, v), d = dep[u] + dep[v] - dep[k]*2;
    if (d&1) return 0;
    if (d == 0) return n;
    if (dep[u] - dep[k] == dep[v] - dep[k]) {
        for (int j = M-2; j >= 0 && u != v; --j)
            if (fa[u][j] != fa[v][j])
                u = fa[u][j], v = fa[v][j];
        return n - siz[u] - siz[v];
    }
    if (dep[u] - dep[k] < dep[v] - dep[k]) swap(u, v);//确保u比v离LCA更远
    int t = d/2 - 1, mid = u;
    for (int j = 0; t; ++j, t >>= 1)
        if (t&1) mid = fa[mid][j];
    return siz[fa[mid][0]] - siz[mid];
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v; add(u, v);
    }
    dfs(1, 1);
    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        const int res = solve(u, v, n);
        cout << res << '\n';
    }
    return 0;
}