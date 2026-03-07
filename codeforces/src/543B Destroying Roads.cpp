//
// Created by Psy.C on 2026/3/7.
//
/**
nxt（下一条边的索引），to（目标节点）
e[N*N]：存储所有边
cnt：边的计数器
head[N]：每个节点的第一条边
s1,t1,l1：第一对起点、终点、最大距离
s2,t2,l2：第二对起点、终点、最大距离
check(x,y)：检查路径s1→x→y→t1和s2→x→y→t2是否都满足距离限制
check2(x,y)：检查路径s1→x→y→t1和t2→x→y→s2是否都满足距离限制

枚举所有可能的节点对(i,j)
如果满足第一种路径条件，更新答案（删除的边数 = 总边数 - 使用的边数）
如果满足第二种路径条件，更新答案
考虑不需要额外路径的独立路径情况
输出最多可以删除的边数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e3+5, inf = 0x3f3f3f3f;
struct node { int nxt, to; } e[N*N];
int cnt, head[N];
void add(int u, int v) {
    e[++cnt] = {head[u], v}, head[u] = cnt;
}

queue<int> q;
int dis[N][N];
void bfs(int st) {//从起点st到所有其他节点的最短距离
    while (!q.empty()) q.pop(); q.push(st); dis[st][st] = 0;//起点到自己的距离为0
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (dis[st][v] != inf) continue;//已访问过
            dis[st][v] = dis[st][u] + 1;
            q.push(v);
        }
    }
}

int s1, t1, l1, s2, t2, l2;
bool check(int x, int y) {
    return dis[s1][x] + dis[x][y] + dis[y][t1] <= l1 &&
        dis[s2][x] + dis[x][y] + dis[y][t2] <= l2;
}
bool check2(int x, int y) {
    return dis[s1][x] + dis[x][y] + dis[y][t1] <= l1 &&
        dis[t2][x] + dis[x][y] + dis[y][s2] <= l2;
}

int n, m;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v; add(u, v); add(v, u);
    }
    cin >> s1 >> t1 >> l1 >> s2 >> t2 >> l2;
    memset(dis, inf, sizeof dis);
    for (int i = 1; i <= n; ++i) bfs(i);//计算所有点对之间的最短距离
    int ans = -1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            if (check(i, j))
                ans = max(ans, m-dis[s1][i]-dis[s2][i]-dis[i][j]-dis[j][t1]-dis[j][t2]);
            if (check2(i, j))
                ans = max(ans, m-dis[s1][i]-dis[t2][i]-dis[i][j]-dis[j][t1]-dis[j][s2]);
        }
    if (dis[s1][t1] <= l1 && dis[s2][t2] <= l2)
        ans = max(ans, m-dis[s1][t1]-dis[s2][t2]);
    cout << ans << '\n';
    return 0;
}