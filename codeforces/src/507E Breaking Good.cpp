//
// Created by Psy.C on 2026/2/26.
//
/**
起点、终点和权重z
重载小于运算符实现最小堆
e：边的列表
g[N]：邻接表，存储每个节点的边索引
将边添加到边列表
在邻接表中记录边的索引
如果边有权重z=1，增加sum计数

d[N]：最短距离数组
f[N]：某种费用/权值数组
p[N]：前驱边数组
used[N]：访问标记数组
起点距离为0
起点费用为sum/2
起点前驱为-1（表示无前驱）

取出距离最小的节点
如果已访问过则跳过
松弛操作：
如果找到更短路径，更新距离和费用
根据边的权重z调整费用
记录前驱边
距离相等时的费用优化

BFS标记路径上的边：
从终点向前追溯到起点
标记路径上的所有边

输出需要修改的边：
路径上的非权重边改为权重边
非路径上的权重边改为非权重边
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+1;

struct Edge { int from, to, z; };
struct node {
    int u, d;
    bool operator<(const node &o) const {
        return d > o.d;
    }
};

vector<Edge> e;
vector<int> g[N];
int sum;
void add(const int from, const int to, const int z) {
    e.push_back({from, to, z});
    const int k = e.size();
    g[from].push_back(k-1);
    if (z) sum++;
}

int d[N], f[N], p[N];
bool used[N];
void dijkstra(const int s) {
    priority_queue<node> q;
    d[s] = 0; f[s] = sum/2; p[s] = -1; q.push({s, 0});
    while (!q.empty()) {
        auto [u1, d1] = q.top(); q.pop();
        const int u = u1;
        if (used[u]) continue;
        used[u] = true;
        for (int i = 0; i < g[u].size(); ++i) {
            if (const auto v = e[g[u][i]]; d[v.to] > d[u] + 1) {
                d[v.to] = d[u] + 1;
                if (v.z) f[v.to] = f[u] - 1;
                else f[v.to] = f[u] + 1;
                p[v.to] = g[u][i];
                q.push({v.to, d[v.to]});
            }
            else if (d[v.to] == d[u] + 1) {
                int k;
                if (v.z) k = f[u] - 1;
                else k = f[u] + 1;
                if (f[v.to] > k) {
                    f[v.to] = k;
                    p[v.to] = g[u][i];
                }
            }
        }
    }
}

int vis[N<<1];
void bfs(const int n) {
    if (n == -1) return;
    vis[n] = 1;
    bfs(p[e[n].from]);
}

int n;
void init() {
    memset(vis, 0, sizeof(vis));
    memset(used, 0, sizeof(used));
    memset(d, 99, sizeof(d));
    memset(f, 0, sizeof(f));
    for (int i = 0; i <= n; ++i) g[i].clear();
    e.clear();
    sum = 0;
}

int m;
int main() {
    fast;
    cin>>n>>m; init();
    for (int i = 0, x, y, z; i < m; ++i) {
        cin>>x>>y>>z;
        add(x, y, z); add(y, x, z);
    }
    dijkstra(1); bfs(p[n]);
    cout << f[n] << '\n';//终点的费用值
    for (int i = 0; i < 2*m; i += 2) {
        if ((vis[i] || vis[i+1]) && !e[i].z)
            cout << e[i].from << ' ' << e[i].to << " 1\n";
        else if (!vis[i] && !vis[i+1] && e[i].z)
            cout << e[i].from << ' ' << e[i].to << " 0\n";
    }
    return 0;
}