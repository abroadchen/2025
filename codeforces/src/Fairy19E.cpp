//
// Created by Psy.C on 2025/9/18.
//
/*
*n, m: 图的顶点数和边数
h[maxn]: 邻接表的头数组，h[u]指向顶点u的第一条边
e[maxn]: 边数组，存储边的终点
idx: 边的索引计数器
ne[maxn]: next数组，用于邻接表，ne[i]指向下一条边
vis[maxn]: 访问标记数组
dep[maxn]: 每个顶点的深度（在DFS树中）
odd[maxn], even[maxn]: 用于统计奇环和偶环的计数
ans[maxn], anscnt: 存储答案边的数组和计数器
 *
*u, v: 边的两个端点
trEdge: 标记是否为DFS树中的边（树边）
odd, even: 该边参与的奇环和偶环数量
 *
 *对于树边（第一次访问的边），标记为trEdge = true
 *i >> 1是因为无向图中每条边存储两次（正向和反向）
 *
 *
*处理非树边（后向边）：
如果深度差为奇数，形成偶环
如果深度差为偶数，形成奇环
更新相关顶点的计数器
统计奇环总数cnt
 *
 *
 *
 *
*对于树边：参与所有奇环且不参与偶环
对于非树边：当只有一个奇环时，参与该奇环
 *
 *
 *
 *
 *
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 1000010
using namespace std;
int n, m, h[maxn], e[maxn], idx, ne[maxn];
bool vis[maxn];
int dep[maxn], odd[maxn], even[maxn];
int ans[maxn], anscnt;

struct Edge {
    int u, v;
    bool trEdge;
    int odd, even;
} edge[maxn];

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int u, int d) {
    vis[u] = true;
    dep[u] = d;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (!vis[v]) {
            edge[i >> 1].trEdge = true;
            dfs(v, d + 1);
        }
    }
}

void dfs_count(int u) {
    vis[u] = true;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (!vis[v]) {
            dfs_count(v);
            odd[u] += odd[v];
            even[u] += even[v];
            edge[i >> 1].odd += odd[v];//累加子树的统计信息
            edge[i >> 1].even += even[v];
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof(h));
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &edge[i].u, &edge[i].v);
        add(edge[i].u, edge[i].v);
        add(edge[i].v, edge[i].u);
    }

    for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i, 1);

    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (edge[i].trEdge) continue;
        int u = edge[i].u, v = edge[i].v;
        if (dep[u] > dep[v]) swap(u, v);
        if ((dep[u] - dep[v]) & 1) even[u]--, even[v]++;
        else odd[u]--, odd[v]++, edge[i].odd++, cnt++;
    }
    if (!cnt) {
        printf("%d\n", m);
        for (int i = 0; i< m; ++i) printf("%d ", i + 1);
    } else {
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; ++i) if (!vis[i]) dfs_count(i);
        anscnt = 0;
        for (int i = 0; i < m; ++i) {
            if (edge[i].trEdge) {
                if (!edge[i].even && edge[i].odd == cnt)
                    ans[anscnt++] = i + 1;
            } else if (cnt == 1 && edge[i].odd)
                ans[anscnt++] = i + 1;
        }
        printf("%d\n", anscnt);
        for (int i = 0; i < anscnt; ++i) printf("%d ", ans[i]);
    }
    return 0;
}