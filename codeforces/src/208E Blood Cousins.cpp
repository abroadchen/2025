//
// Created by Psy.C on 2025/12/6.
//
/*
*head[]存储每个节点的第一条边的索引
e[]存储边的信息
*siz[u]：以u为根的子树大小
son[u]：u的重儿子（子树最大的儿子）
fa[u][i]：u的第2^i个祖先（倍增）
dep[u]：u的深度
 *e2[idx]存储所有需要在节点idx处处理的查询
 *
*sum[dep[u]] += c：在深度dep[u]处增加c个节点
vis[]数组用于标记避免重复访问
 *
*树链剖分 + 启发式合并处理查询
先递归处理轻儿子（f=1表示需要清理）
递归处理重儿子（f=0表示不需要清理）
处理当前节点u
处理在节点u上的所有查询
如果需要清理，则清除当前节点的贡献
 *
 *时间复杂度：O(n log n + m log n)，空间复杂度：O(n)
 *
 */
#include <iostream>
#include <cstring>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+10, M = 20;
int n, head[N], cnt, ans[N];

struct edge { int to, nxt; } e[N<<1];
void add(const int u, const int v) {
    e[cnt].to = v; e[cnt].nxt = head[u]; head[u] = cnt++;
    e[cnt].to = u; e[cnt].nxt = head[v]; head[v] = cnt++;
}

int siz[N], son[N], fa[N][M], dep[N];
void dfs(const int u) {
    siz[u] = 1; son[u] = 0;
    for (int i = 1; i < M; ++i) fa[u][i] = fa[fa[u][i-1]][i-1];
    for (int i = head[u]; ~i; i = e[i].nxt) {
        if (e[i].to != fa[u][0]) {
            fa[e[i].to][0] = u;
            dep[e[i].to] = dep[u] + 1;
            dfs(e[i].to);
            if (siz[e[i].to] > siz[son[u]]) son[u] = e[i].to;
            siz[u] += siz[e[i].to];
        }
    }
}

int get(int u, const int d) {//从节点u向上走d步到达的节点
    for (int i = 0; i < M; ++i) {
        if (d >>i & 1) u = fa[u][i];
    }
    return u;
}

struct ex { int x, c; };//查询的编号（索引） 深度值
vector<ex> e2[N];


int vis[N], sum[N];
void dfs1(const int u, const int c) {//统计深度为特定值的节点数量
    sum[dep[u]] += c;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        if (e[i].to != fa[u][0] && !vis[e[i].to])
            dfs1(e[i].to, c);
    }
}

void dfs2(const int u, const int f) {
    for (int i = head[u]; ~i; i = e[i].nxt) {
        if (e[i].to != fa[u][0] && e[i].to != son[u])
            dfs2(e[i].to, 1);
    }
    if (son[u]) { dfs2(son[u], 0); vis[son[u]] = 1; }
    dfs1(u, 1);
    const int sz = static_cast<int>(e2[u].size());
    for (int i = 0; i < sz; ++i) {
        ans[e2[u][i].x] = sum[e2[u][i].c];
    }
    if (son[u]) vis[son[u]] = 0;
    if (f) dfs1(u, -1);
}

int main() {
    fast;
    cin >> n;
    memset(head, -1, sizeof(head)); cnt = 0;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        add(i, x);
    }
    dfs(0);
    int m; cin >> m;
    for (int i = 0, x, y; i < m; ++i) {
        cin >> x >> y;
        if (dep[x] - y <= 0) { ans[i] = 1; continue; }
        const int idx = get(x, y);
        e2[idx].push_back({i, dep[x]});
    }
    dfs2(0, 0);
    for (int i = 0; i < m; ++i)
        cout << ans[i] - 1 << " \n"[i == m - 1];
    return 0;
}