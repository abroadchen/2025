//
// Created by Psy.C on 2026/2/28.
//
/**
终点v和权重w
maxx：更新x为max(x, y)
f[N], g[N]：动态规划数组，f存储最大值，g存储次大值
update：更新节点u的g值，如果g[u] > f[u]则交换
从根节点向下DFS
计算每个节点向下路径的最大值
f[u]：以u为起点向下的最长路径
g[u]：以u为起点向下的次长路径
按照f值排序，相等时按节点编号排序

向下传递信息，计算向上路径
up[N]：记录每个节点的最优父节点
更新v节点，考虑从u传来的路径

w[N]：权重数组，p[N]：排序后的节点数组
对于给定的距离差d，找到满足条件的最大连通块
双指针扫描，维护连通块大小
w[fa[p[i]] = up[p[i]]] += w[p[i]]：合并到最优父节点

 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 2e5+1;
struct node { int v, w; };
vector<node> e[N];
void add(const int f, const int t, const int w) {
    e[f].push_back({t, w});
    e[t].push_back({f, w});
}

void maxx(ll& x, const ll y) { x < y ? x = y : x; }
ll g[N], f[N];
void update(const int u, const ll d) {
    maxx(g[u], d), g[u] > f[u] ? swap(g[u], f[u]) : void();
}

void dfs(const int u, const int fa) {
    for (int i = 0, v; i < e[u].size(); ++i)
        if ((v=e[u][i].v) != fa)
            dfs(v, u), update(u, f[v]+e[u][i].w);
}

bool cmp(const int u, const int v) {
    return f[u] == f[v] ? u < v : f[u] < f[v];
}

int up[N];
void dfs2(const int u, const int fa) {
    for (int i = 0, v; i < e[u].size(); ++i) {
        if ((v=e[u][i].v) == fa) continue;
        update(v, e[u][i].w+(f[v]+e[u][i].w == f[u] ? g[u] : f[u]));
        dfs2(v, u);
    }
    for (int i = 0, v; i < e[u].size(); ++i)
        cmp(u, v=e[u][i].v) ? up[v] = u : up[u] = v;
}

int fa[N];
int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int n, w[N], p[N];
void out(const ll d) {
    int res = 0;
    for (int i = 1; i <= n; ++i) fa[i] = i, w[i] = 1;
    for (int i = n, j = n; i >= 1; --i) {
        while (f[p[j]] > f[p[i]] + d) --w[find(p[j--])];
        res = max(res, w[p[i]]), w[fa[p[i]] = up[p[i]]] += w[p[i]];
    }
    printf("%d\n", res);
}

constexpr int SIZE = 1<<22;
char buf[SIZE], *S = buf, *T = buf;
#define gc \
    (S == T ? T = ((S = buf) + fread(buf, 1, SIZE, stdin)), \
    (S == T ? EOF : *S++) : *S++)
ll read() {
    ll x = 0, sgn = 1; char c = gc;
    while (!isdigit(c)) sgn = (c == '-') ? -1 : sgn, c = gc;
    while (isdigit(c)) x = (x<<1)+(x<<3)+(c&15), c = gc;
    return x*sgn;
}

int q;
int main() {
    n = read();
    for (int i = 1, u, v; i < n; ++i)
        u = read(), v = read(), add(u, v, read());
    dfs(1, 0), dfs2(1, 0), q = read();
    for (int i = 1; i <= n; ++i) p[i] = i;
    sort(p + 1, p + n + 1, cmp);
    while (q--) out(read());
    return 0;
}