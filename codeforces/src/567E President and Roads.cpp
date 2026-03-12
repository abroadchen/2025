//
// Created by Psy.C on 2026/3/12.
//
/**
最小堆优先队列，存储边的距离和节点编号
n表示图中节点数量
e是邻接表，存储图的边信息（目标节点，边权）

从节点v出发，结果存储在数组d中
初始化距离数组d，所有节点距离设为无穷大
起始节点v的距离设为0，并将{0,v}加入优先队列
当优先队列不为空时循环
取出距离最小的节点t
遍历t的所有邻接节点，如果发现更短路径则更新
将更新后的距离和节点加入优先队列

idx时间戳计数器
dfn[i]节点i的访问时间戳
low[i]节点i能到达的最小时间戳
vis[i]标记边是否被访问过
bg[i]标记边是否为桥

Tarjan算法找桥边，初始化节点x的时间戳
遍历x的所有邻接边，跳过已访问的边
标记当前边为已访问
如果邻接节点未访问过，递归调用tarjan
更新当前节点的low值
如果发现桥边（dfn[x] < low[邻接节点]），标记这条边为桥
否则更新low值为较小的时间戳

m: 边的数量
s: 起始点
t: 终点
a,b: 存储边的起点和终点
l: 存储边的长度
d1,d2: 两次Dijkstra算法的距离数组

构建有向图（正向）
从s开始运行Dijkstra，求到各点最短距离
清空图
构建反向图
从t开始运行Dijkstra，求t到各点最短距离
再次清空图
构建新图，只保留最短路径上的边（这些边满足：起点到a[i] + 边长 + b[i]到终点 = 总最短距离）
在最短路径图上运行Tarjan算法，找出桥边
对每条边进行判断：
如果是桥边，输出"YES"（必须经过此边）
如果不是桥边，但减少一定权值后仍能保证最短路不变，输出"CAN 新权重"
否则输出"NO"

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pll pair<ll, ll>
using namespace std;
constexpr int N = 1e5+5;
constexpr ll inf = 1e18;
priority_queue<pll, vector<pll>, greater<>> q;
ll n;
vector<pll> e[N];
void dijkstra(ll v, ll *d) {
    for (ll i = 1; i <= n; ++i) d[i] = inf;
    d[v] = 0; q.push({0, v});
    while (!q.empty()) {
        ll t = q.top().second; q.pop();
        for (ll i = 0; i < e[t].size(); ++i)
            if (d[e[t][i].first] > d[t] + e[t][i].second) {
                d[e[t][i].first] = d[t] + e[t][i].second;
                q.push({d[e[t][i].first], e[t][i].first});
            }
    }
}

ll idx, dfn[N], low[N], vis[N], bg[N];
void tarjan(ll x) {
    dfn[x] = low[x] = ++idx;
    for (ll i = 0; i < e[x].size(); ++i) {
        if (vis[e[x][i].second]) continue;
        vis[e[x][i].second] = 1;
        if (!dfn[e[x][i].first]) {
            tarjan(e[x][i].first);
            low[x] = min(low[x], low[e[x][i].first]);
            if (dfn[x] < low[e[x][i].first])
                bg[e[x][i].second] = 1;
        }
        else
            low[x] = min(low[x], dfn[e[x][i].first]);
    }
}

ll m, s, t, a[N], b[N], l[N], d1[N], d2[N];
int main() {
    fast;
    cin >> n >> m >> s >> t;
    for (ll i = 0; i < m; ++i) cin >> a[i] >> b[i] >> l[i];
    for (ll i = 0; i < m; ++i) e[a[i]].push_back({b[i], l[i]});
    dijkstra(s, d1);
    for (ll i = 1; i <= n; ++i) e[i].clear();
    for (ll i = 0; i < m; ++i) e[b[i]].push_back({a[i], l[i]});
    dijkstra(t, d2);
    for (ll i = 1; i <= n; ++i) e[i].clear();
    for (ll i = 0; i < m; ++i)
        if (d1[a[i]] + l[i] + d2[b[i]] == d1[t]) {
            e[a[i]].push_back({b[i], i});
            e[b[i]].push_back({a[i], i});
        }
    tarjan(s);
    for (ll i = 0; i < m; ++i) {
        if (bg[i]) cout << "YES\n";
        else if (d1[t] - d1[a[i]] - d2[b[i]] - 1 > 0)
            cout << "CAN " << l[i] - (d1[t] - d1[a[i]] - d2[b[i]] - 1) << '\n';
        else cout << "NO\n";
    }
    return 0;
}