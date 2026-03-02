//
// Created by Psy.C on 2026/3/2.
//
/**
N为节点数上限，M为倍增数组大小（19≈log₂(N)）
mx数组：线段树，每个节点存储{值, 位置}的pair
ln数组：按DFS序排列的节点
区间更新，给[L,R]区间内的所有值加上w

p数组：倍增祖先数组，p[i][u]表示u的2^i级祖先
dfn数组：节点的DFS序
tim：DFS时间戳
md数组：子树最大深度
low数组：子树中DFS序的最大值
倍增预处理：构建LCA查询所需的数据结构

第一次DFS：从节点1开始找直径一端
pre函数：以直径端点为根进行预处理

加密查询：使用上次结果x进行解密
v<<1：将步数乘以2
get函数：执行查询并更新x

dep[x]：祖先节点的深度
ans[y]-ans[y-1]：第y轮新增的贡献值
md[x]-dep[x]：从x到其子树最大深度的距离
p[0][j]：节点j的父节点（p[0][j]表示j的2⁰=1级祖先，即直接父亲）
dep[j]：节点j的深度（从根节点到j的距离）
dep[p[0][j]]：节点j的父亲的深度
dep[p[0][j]]-dep[j] 是负数（因为子节点深度 > 父节点深度）
在 modify 函数中，这会将区间 [dfn[j], low[j]]（节点j的子树）的所有值减少 weight(j, parent_of_j)
目的：当节点j不再是路径上的关键节点时，移除它对子树深度计算的影响

 */
#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+1, M = 19;

struct node { int v, nxt, w; } e[N<<1];
int head[N], cnt=1;
inline void add(const int u, const int v, const int w) {
    e[cnt] = {v, head[u], w}, head[u] = cnt++;
}

ii mx[N<<2];
void push_up(const int rt) {
    mx[rt] = max(mx[rt<<1], mx[rt<<1|1]);
}

int dep[N], ln[N];
void build(const int rt, const int l, const int r) {
    if (l == r) {
        mx[rt] = {dep[ln[l]], ln[l]};
        return;
    }
    const int mid = (l + r) >> 1;
    build(rt<<1, l, mid); build(rt<<1|1, mid+1, r);
    push_up(rt);
}

int tag[N<<2];
void modify(const int rt, const int l, const int r, const int L, const int R, const int w) {
    if (L <= l && r <= R) {
        mx[rt].first += w; tag[rt] += w;
        return;
    }
    const int mid = (l + r) >> 1;
    if (L <= mid) modify(rt<<1, l, mid, L, R, w);
    if (R > mid) modify(rt<<1|1, mid+1, r, L, R, w);
    push_up(rt);
    mx[rt].first += tag[rt];
}

int p[M][N], dfn[N], tim, md[N], low[N];
void dfs(const int u, const int fa) {
    p[0][u] = fa; ln[dfn[u]=++tim] = u; md[u] = dep[u];
    for (int i = 1; i < M; ++i) p[i][u] = p[i-1][p[i-1][u]];
    for (int i = head[u]; i; i = e[i].nxt) {
        const int v = e[i].v;
        if (v == fa) continue;
        dep[v] = dep[u] + e[i].w;
        dfs(v, u);
        md[u] = max(md[u], md[v]);
    }
    low[u] = tim;
}

int root, n, ans[N], vis[N];
void pre(const int rt) {
    root = rt;
    dfs(root, 0); build(1, 1, n);
    for (int i = 2; i <= n; ++i) {
        ans[i] = ans[i-1] + mx[1].first;
        for (int j = mx[1].second; j && !vis[j]; j = p[0][j])
            vis[j] = i, modify(1, 1, n, dfn[j], low[j], dep[p[0][j]]-dep[j]);
    }
}

///查询从节点x出发，在y步内能到达的最大深度
int get(int x, int y) {
    y = min(y, n);//不超过n
    if (vis[x] <= y) return ans[y];//节点x被"激活"或"影响"的最早查询轮次
    const int u = x;//保存原始节点
    for (int i = M-1; ~i; --i)
        if (vis[p[i][x]] > y) x = p[i][x];//在y轮之后才被激活 沿祖先方向向上跳跃
    x = p[0][x];//经过倍增查找后，再向上一步到达实际的祖先节点
    return ans[y] + md[u] - dep[x] - min(dep[x],
        min(ans[y]-ans[y-1], md[x]-dep[x]));
}

int mxv;//最大距离
void dfs(const int u, const int fa, const int dp) {//寻找树的直径
    if (dp > mxv) mxv = dp, root = u;//直径的一个端点
    for (int i = head[u]; i; i = e[i].nxt)
        if (e[i].v != fa)
            dfs(e[i].v, u, dp+e[i].w);
}

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int q, x;
int main() {
    n = read(); q = read();
    for (int i = 1, u, v, w; i < n; ++i)
        u = read(), v = read(), w = read(), add(u, v, w), add(v, u, w);
    mxv = 0; dfs(1, 0, 0); pre(root);
    while (q--) {
        const int u = (read() + x - 1) % n + 1, v = (read() + x - 1) % n + 1;
        printf("%d\n", x=get(u, v<<1));
    }
    return 0;
}