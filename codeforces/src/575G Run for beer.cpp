//
// Created by Psy.C on 2026/3/14.
//
/**
目标节点to、下一个同起点边的索引nxt、权重w
cnt: 边的数量计数器
head[i]: 节点i的第一条边在to数组中的索引
添加从u到v权值为w的边
将新边插入到以u为起点的边链表头部
n: 图中节点总数
dis[i]: 从源点到节点i的距离
vis[i]: 标记节点i是否已访问
d[i]: 存储第一次Dijkstra的结果
q: 优先队列，存储{-距离, 节点}对
初始化所有距离为无穷大，源点距离为0
将源点加入优先队列
循环取出距离最小的未访问节点
更新其邻居节点的距离
将结果保存到d数组

从节点n开始，在只考虑权重为0的边的情况下运行Dijkstra算法
计算每个可达节点到终点n的无权距离
找到与这些节点相关的原始距离的最小值并更新

从节点n开始BFS遍历权重为0的连通分量
标记访问过的节点
如果当前节点有非零权重边且未被处理，则将其加入队列s[1]

进行BFS搜索，交替使用两个队列s[0]和s[1]
在每一步寻找最小权重的边
输出路径上的边权重
最后输出路径上节点编号（减去1转换回原编号）

u++,v++将编号从0开始转为1开始


循环从1到d[n]（从节点1到节点n的最短距离）
这个循环模拟了在最短路径上的每一步操作
x = t&1: 获取t的最低位，当t为奇数时x=1，偶数时x=0
y = x^1: y是x的相反，即x和y总是不同（0和1交替）
mn = inf: 初始化当前步骤的最小边权重为无穷大
清空队列s[y]，为存储下一步的候选节点做准备
由于使用双队列交替处理，y代表下一阶段使用的队列
当前队列为s[x]，获取队首元素并弹出
u包含三个字段：a（节点id）、b（当前总代价）、c（父节点）
如果对于节点u.a已经存在更优或相等的解，则跳过当前节点
这是一种剪枝优化，避免重复处理较差的方案
更新节点u.a的最优解为u.b
设置节点u.a的前驱节点为u.c
遍历节点u.a的所有邻接节点
只处理那些在最短路径树上的节点（距离比当前节点少1）
如果发现更小的边权重：
清空下一阶段队列（因为找到了更优的权重）
更新最小权重mn为当前边权重
将新的候选节点{目标节点, 总代价, 当前节点}加入下一阶段队列
如果边权重等于当前最小值，同样加入下一阶段队列
这样可以保留所有具有相同最小权重的选项
输出当前步骤找到的最小边权重
如果从1到n的最短距离为0（即两节点相同）
输出"0"和路径长度p+1
如果最短距离不为0，换行
从最终状态队列中找出最优解res
输出res+1作为最终结果
通过fr数组追踪从节点1到节点n的路径
输出路径上每个节点的编号（减1是为了还原原始编号）
最后输出终点n-1

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5, inf = 1e9+7;

struct node { int to, nxt, w; } to[N<<1|1];

int cnt, head[N+1];
void add(int u, int v, int w) {
    to[++cnt] = {v, head[u], w}, head[u] = cnt;
}

int n, dis[N+1], vis[N+1], d[N+1];
priority_queue<ii> q;
void dijkstra(int s) {
    for (int i = 1; i <= n; ++i) { dis[i] = inf; vis[i] = 0; }
    dis[s] = 0; q.emplace(0, s);
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = to[i].nxt) {
            int v = to[i].to;
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                q.emplace(-dis[v], v);
            }
        }
    }
    for (int i = 1; i <= n; ++i) d[i] = dis[i];
}

int d2[N+1];
void pre() {
    int s = n;
    for (int i = 1; i <= n; ++i) { dis[i] = inf; vis[i] = 0; }
    dis[s] = 0; q.emplace(0, s);
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; i; i = to[i].nxt) {
            if (to[i].w != 0) continue;
            int v = to[i].to;
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                q.emplace(-dis[v], v);
            }
        }
    }
    for (int i = 1; i <= n; ++i) d2[i] = dis[i];
    int mn = inf;
    for (int u = 1; u <= n; ++u) {
        if (d2[u] == inf) continue;
        mn = min(mn, d[u]);
    }
    for (int u = 1; u <= n; ++u) {
        if (d2[u] == inf) continue;
        d[u] = mn;
    }
}

struct node2 { int a, b, c; };
queue<node2> s[2];
queue<int> g;
int use[N+1], fr[N+1], u2[N+1];
void fd() {
    g.push(n);
    while (!g.empty()) {
        int u = g.front(); g.pop();
        int k = 0; use[u] = 1;
        for (int i = head[u]; i; i = to[i].nxt) {
            if (to[i].w == 0 && use[to[i].to] == 0) {
                use[to[i].to] = 1;
                g.push(to[i].to);
                fr[to[i].to] = u;
            }
            if (to[i].w != 0) k = 1;
        }
        if (k == 1 && u2[u] == 0) {
            u2[u] = 1;
            s[1].push({u, d2[u]+d[u], fr[u]});
        }
    }
}

int ans[N+1];
void bfs() {
    for (int i = 1; i <= n; ++i) ans[i] = inf;
    for (int t = 1; t <= d[n]; ++t) {
        int x = t&1, y = x^1, mn = inf;
        while (!s[y].empty()) s[y].pop();
        while (!s[x].empty()) {
            auto u = s[x].front(); s[x].pop();
            if (ans[u.a] <= u.b) continue;
            ans[u.a] = u.b; fr[u.a] = u.c;
            for (int i = head[u.a]; i; i = to[i].nxt) {
                if (d[to[i].to] != d[u.a] - 1) continue;
                if (to[i].w < mn) {
                    while (!s[y].empty()) s[y].pop();
                    mn = to[i].w;
                    s[y].push({to[i].to, u.b, u.a});
                } else if (to[i].w == mn) {
                    s[y].push({to[i].to, u.b, u.a});
                }
            }
        }
        cout << mn;
    }
    if (d[n] == 0) {
        cout << "0\n";
        int p = 0;
        for (int i = 1; i != n; i = fr[i]) p++;
        cout << p + 1 << '\n';
    } else {
        cout << '\n';
        int x = (d[n]&1)^1, res = inf;
        while (!s[x].empty()) {
            if (s[x].front().b < res) {
                res = s[x].front().b;
                fr[1] = s[x].front().c;
            }
            s[x].pop();
        }
        cout << res + 1 << '\n';
    }
    for (int i = 1; i != n; i = fr[i]) cout << i - 1 << ' ';
    cout << n - 1;
}

int m;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; ++i) {
        cin >> u >> v >> w; u++, v++;
        add(u, v, w); add(v, u, w);
    }
    dijkstra(1); pre(); fd(); bfs();
    return 0;
}