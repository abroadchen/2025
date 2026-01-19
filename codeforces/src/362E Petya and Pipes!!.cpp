//
// Created by Psy.C on 2026/1/19.
//
/**
 * N=100010（边数上限），M=51（节点数上限）
*v：目标节点
c：容量
w：费用
nxt：链式前向星的下一个边索引
*tot=1：边编号，从1开始（保留0作为空指针）
head[M]：邻接表头指针
insert：添加单向边
add：添加双向边（正向有容量c费用w，反向容量0费用-w）
*dis[M]：最短距离数组
pre[M]：路径前驱数组
cost：当前总费用
k：费用预算上限
flow：当前总流量
q：SPFA队列
vis[M]：节点在队列中标记
 *
*如果终点不可达，返回false
计算沿路径的最小残量
如果总费用超出预算k，计算还能增加多少流量，然后返回false
 *
*计算增广路径上的最小容量d
更新路径上的容量和反向边容量
更新总费用
增加总流量
 */
#include <iostream>
#include <queue>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
#define M 51
#define inf 0x3f3f3f3f
using namespace std;

struct node { int v, c, w, nxt; } e[N];

int tot = 1, head[M];
void insert(const int u, const int v, const int c, const int w) {
    e[++tot] = {v, c, w, head[u]};
    head[u] = tot;
}
void add(const int u, const int v, const int c, const int w) {
    insert(u, v, c, w);
    insert(v, u, 0, -w);
}

int dis[M], pre[M], cost, k, flow;
queue<int> q;
bool vis[M];
bool spfa(const int s, const int t) {
    memset(dis, 0x3f, sizeof(dis)); dis[s] = 0; q.push(s);
    while (!q.empty()) {
        const int u = q.front(); q.pop(); vis[u] = false;
        for (int i = head[u], v; i; i = e[i].nxt) {
            e[i].c && dis[v=e[i].v] > dis[u] + e[i].w ?
            dis[v] = dis[u] + e[i].w, pre[v] = i,
            !vis[v] ? q.push(v), vis[v] = true : 0 : 0;
        }
    }
    if (dis[t] >= inf) return false;
    int d = inf;
    for (int i = t; i != s; i = e[pre[i]^1].v) d = min(d, e[pre[i]].c);
    if (cost + d * dis[t] > k) {
        flow += (k - cost) / dis[t];
        return false;
    }
    return true;
}

void mcf(const int s, const int t) {
    int d = inf;
    for (int i = t; i != s; i = e[pre[i]^1].v) d = min(d, e[pre[i]].c);
    for (int i = t; i != s; i = e[pre[i]^1].v) {
        e[pre[i]].c -= d;
        e[pre[i]^1].c += d;
        cost += d * e[pre[i]].w;
    }
    flow += d;
}


int main() {
    fast;
    int n; cin >> n >> k;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        int x; cin >> x;
        if (x) add(i, j, x, 0), add(i, j, k, 1);
    }
    while (spfa(1, n)) mcf(1, n);
    cout << flow;
    return 0;
}