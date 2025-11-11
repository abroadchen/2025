//
// Created by Psy.C on 2025/11/10.
//
/*
*n：图中的节点数
m：图中的边数
q：查询数量
fa[N]：并查集(不相交集合)的父节点数组
dep[N]：每个节点在树中的深度
f[N][17]：倍增表，用于最近公共祖先(LCA)计算
a[N]：布尔数组，标记节点子树中是否有奇环
s[N]：前缀和数组，用于统计特殊节点
e[N]：图的邻接表表示
 *
*第一次DFS遍历处理图：
根据父节点设置当前节点的深度
对于节点u的每个邻居v：
如果v未访问过(dep[v] == 0)：
设置u为v的父节点
递归调用dfs1处理v
如果u和v在同一连通分量中，则根据a[v]更新a[u]
否则如果v是u的祖先(回边)：
如果环长度为奇数，则标记a[u] = 1
沿着路径压缩并查集结构
 *
*第二次DFS遍历计算前缀和：
将当前节点的a[u]值加到s[u]上
对于树中的每个子节点v：
如果v确实是子节点(深度 = u的深度+1)：
如果它们在同一连通分量中，则将a[u]传播给a[v]
设置s[v]等于s[u]
递归调用dfs2处理v
 *
*计算节点x和y的最近公共祖先(LCA)函数：
如有必要交换x和y，确保x更深
使用倍增法将x提升到与y同一层
如果此时x等于y，则返回x作为LCA
同时向上移动x和y直到相遇
返回相遇点的父节点
 *
 *填充f[i][j]，表示节点i的第2^j个祖先
 *节点 i 的第 2^j 个祖先 = 节点 i 的第 2^(j-1) 个祖先 的第 2^(j-1) 个祖先
 *
*从根到 u 的路径包含了：(根到 l) + (l 到 u)
从根到 v 的路径包含了：(根到 l) + (l 到 v)
两者的和包含了两次 (根到 l) 的部分
 *
 *
 */
#include <cstdio>
#include <algorithm>
#include <vector>
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int N = 1e5+5;
int n, m, q,
fa[N], dep[N], f[N][17], a[N], s[N];
vector<int> e[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void dfs1(int u) {
    dep[u] = dep[f[u][0]]+1;
    for (auto v : e[u]) {
        if (!dep[v]) {
            f[v][0] = u;
            dfs1(v);
            if (find(u) == find(v)) a[u] |= a[v];
        } else if (dep[v]+1 < dep[u]) {
            if ((dep[u]+dep[v]+1)&1) a[u] = 1;
            for (int x = find(u); dep[x] > dep[v]+1; x = find(x))
                fa[x] = f[x][0];
        }
    }
}

void dfs2(int u) {
    s[u] += a[u];
    for (auto v : e[u]) {
        if (dep[v] == dep[u]+1) {
            if (find(u) == find(v)) a[v] |= a[u];
            s[v] = s[u];
            dfs2(v);
        }
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 16; i >= 0; i--) {
        if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
    }
    if (x == y) return x;
    for (int i = 16; i >= 0; i--) {
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    }
    return f[x][0];
}

int main() {
    scanf("%d%d", &n, &m);
    rep(i,m) {
        int u, v; scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    rep(i,n) fa[i] = i;
    rep(i,n) if (!dep[i]) dfs1(i), dfs2(i);
    rep(j,16) rep(i,n) f[i][j] = f[f[i][j-1]][j-1];
    scanf("%d", &q);
    while(q--) {
        int u, v; scanf("%d%d", &u, &v);
        int l = lca(u, v);
        if (!l) puts("No");
        else if (((dep[u]+dep[v])&1) ||
            s[u] + s[v] - 2 * s[l]) puts("Yes");
        else puts("No");
    }
    return 0;
}