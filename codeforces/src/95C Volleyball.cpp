//
// Created by Psy.C on 2025/11/10.
//
/*
 *g存储原始图，g2存储转换后的图
*used：Dijkstra算法中记录节点是否已访问
d[N][N]：存储所有点对之间的最短距离
cost[N]：存储从起点到各点的最小费用
 *
*起点s
距离数组d
图g
节点数n
 *
*遍历当前节点的所有邻接点：
更新到邻接点的最短距离
将更新的节点加入优先队列（使用负值因为priority_queue默认是大顶堆）
 *
 *节点数n、边数m、起点x、终点y
*读取m条边，构建无向图：
每条边连接节点u和v，权重为w
*对每个节点运行Dijkstra算法，计算该节点到所有其他节点的最短距离
结果存储在d[i][j]中
*读取每个节点的传输塔参数（时间限制t和费用c）
构建新图g2：如果节点i到j的距离不超过t，则在g2中添加费用为c的边
 *在新图g2上从起点x运行Dijkstra算法，计算最小费用
 *如果无法到达终点，输出-1；否则输出最小费用
 *
 *
 */
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
const int N = 1e3+5;
const ll inf = 1e18;

vector<pii> g[N], g2[N];
bool used[N];
ll d[N][N], cost[N];

void dijkstra(int s, ll *d, vector<pii> *g, int n) {
    for (int i = 0; i < n + 1; ++i) { used[i] = false; d[i] = inf; }
    priority_queue<pii> q;
    d[s] = 0;//起点距离设为0
    q.push({0, s});//将起点加入优先队列
    while (!q.empty()) {
        int u = q.top().second; q.pop();//取出距离最小的节点
        if (used[u]) continue;
        used[u] = true;
        for (auto x : g[u]) {
            int v = x.first, w = x.second;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                q.push({-d[v], v});
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, x, y; cin >> n >> m >> x >> y;
    for (int i = 0, u, v, w; i < m; ++i) {
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    for (int i = 1; i < n + 1; ++i) dijkstra(i, d[i], g, n);
    for (int i = 1, t, c; i < n + 1; ++i) {
        cin >> t >> c;
        for (int j = 1; j < n + 1; ++j) {
            if (d[i][j] <= t)
                g2[i].push_back({j, c});
        }
    }
    dijkstra(x, cost, g2, n);
    if (cost[y] == inf) cout << -1 << '\n';
    else cout << cost[y] << '\n';
    return 0;
}