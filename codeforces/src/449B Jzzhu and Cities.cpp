//
// Created by Psy.C on 2026/2/9.
//
/**
n：节点数，m：边数，k：特殊需求数量
s[N]：特殊节点，y[N]：期望距离

时间复杂度：O((V+E)log V)，其中V是节点数，E是边数
空间复杂度：O(V+E)
 */
#include <iostream>
#include <queue>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
#define inf 1<<30
#define ii pair<int,int>
using namespace std;

//起点u、终点v、权重w、下一条边的索引nxt
struct edge { int u, v, w, nxt; } e[N];

int cnt, head[N];//以u为起点的第一条边的索引
void add(const int u, const int v, const int w) {
    e[cnt].u = u; e[cnt].v = v; e[cnt].w = w;
    e[cnt].nxt = head[u]; head[u] = cnt++;
}

bool used[N];//节点是否已确定最短距离
int d[N], in[N];//到各节点的最短距离 到达各节点的最短路径数量
void dijkstra(int s) {
    memset(used, 0, sizeof(used));
    fill_n(d, N, inf);
    priority_queue<ii, vector<ii>, greater<>> q;
    q.emplace(d[s] = 0, s);
    while (!q.empty()) {
        auto [fst, snd] = q.top(); q.pop();//距离和节点
        const int u = snd;
        if (used[u]) continue;
        used[u] = true;
        for (int i = head[u]; i != -1; i = e[i].nxt) {
            if (int v = e[i].v, w = e[i].w; d[v] > d[u] + w) {
                d[v] = d[u] + w;
                q.emplace(d[v], v);
                in[v] = 1;//重置路径数
            }
            else if (d[v] == d[u] + w) ++in[v];//路径数增加
        }
    }
}


int n, m, k, s[N], y[N];
int main() {
    fast;
    memset(head, -1, sizeof(head)); cnt = 0;
    cin >> n >> m >> k;
    for (int i = 1, a, b, c; i <= m; ++i) {
        cin >> a >> b >> c;
        add(a, b, c); add(b, a, c);
    }
    //为每个特殊节点s[i]添加与节点1的双向边，权重为y[i]
    for (int i = 1; i <= k; ++i) {
        cin >> s[i] >> y[i];
        add(1, s[i], y[i]); add(s[i], 1, y[i]);
    }
    dijkstra(1);
    int ans = 0;
    for (int i = 1; i <= k; ++i) {
        if (d[s[i]] < y[i]) ++ans;
        else if (d[s[i]] == y[i] && in[s[i]] > 1)//有多条最短路径
            --in[s[i]], ++ans;//使用一条路径
    }
    cout << ans << '\n';
    return 0;
}