//
// Created by Psy.C on 2025/10/26.
//
/*
*定义图节点结构体Node，包含顶点号、代价和前驱节点
构造函数初始化成员变量
重载<运算符实现最小堆（通过反向比较实现）
声明邻接表v[N]存储图
 *
*定义三元组结构体triplet，用于存储禁止的路径序列
重载<运算符实现字典序比较（降序）
声明map存储禁止的三元组
 *
 *声明二维父节点数组，用于路径追踪
 *Dijkstra算法函数，从源点s开始搜索
 *创建优先队列，将起始节点加入队列
*初始化距离数组为无穷大(1e17)
初始化父节点数组为(-1,-1)
设置起点距离为0
*当队列不为空时循环处理：
取出队列首元素的顶点、前驱和代价
如果当前距离不匹配则跳过（处理延迟删除）
*遍历当前节点的所有邻居：
获取邻居节点和边权
构造三元组(u_prev, u, nd)
如果该三元组在禁止列表中则跳过
*如果找到更短路径：
更新距离
将新节点加入队列
更新父节点信息
 *
*路径追踪函数：
如果父节点无效，打印当前节点并返回
递归打印父路径
打印当前节点
 *
 *主函数开始，读取节点数n、边数edges和禁止三元组数k
 *读取所有边，构建无向图（每条边权重为1）
 *读取禁止的三元组序列，存入map中
 *从节点1开始运行修改版Dijkstra算法
 *寻找到达终点n的最短路径及对应的前驱节点
*如果无法到达终点输出-1
否则输出最短距离和路径
 */
#include <vector>
#include <cstdio>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
typedef pair<ll, ll> pll;

const int N = 3e3+5;
ll a, b, c, w, n, edges, k, dist[N][N];

struct Node {
    ll ver, cost, prev;
    Node(ll v, ll w, ll u) : ver(v), cost(w), prev(u) {}
    bool operator<(const Node& o) const { return cost > o.cost; }
};
vector<Node> v[N];


struct triplet {
    ll a, b, c;
    triplet(ll a, ll b, ll c) : a(a), b(b), c(c) {}
    bool operator<(const triplet& o) const {
        if (a != o.a) return a > o.a;
        if (b != o.b) return b > o.b;
        return c > o.c;
    }
};
map<triplet, ll> m;
pll fa[N][N];

void dij(ll s) {
    priority_queue<Node> q; q.push(Node(s, 0, 0));
    for (int i = 1; i <= n; ++i) { for (int j = 1; j <= n; ++j) dist[i][j] = ll(1e17); }
    for (int i = 1; i <= n; ++i) { for (int j = 1; j <= n; ++j) fa[i][j] = {-1, -1}; }
    dist[s][0] = 0;

    while (!q.empty()) {
        ll u = q.top().ver, u_prev = q.top().prev, cost = q.top().cost; q.pop();
        if (dist[u][u_prev] != cost) continue;
        for (int i = 0; i < v[u].size(); ++i) {
            ll nd = v[u][i].ver, weight = v[u][i].cost;
            triplet t = triplet(u_prev, u, nd);
            if (m.count(t)) continue;
            if (dist[u][u_prev] + weight < dist[nd][u]) {
                dist[nd][u] = dist[u][u_prev] + weight;
                q.push(Node(nd, dist[nd][u], u));
                fa[nd][u] = pll(u, u_prev);
            }
        }
    }
}

void track_parent(ll u, ll prev) {
    if (fa[u][prev].first <= 0) {
        printf("%lld\n", u);
        return;
    }
    pll p = fa[u][prev];
    track_parent(p.first, p.second);
    printf("%lld\n", u);
}


int main() {
    scanf("%lld %lld %lld", &n, &edges, &k);
    for (int i = 1; i <= edges; ++i) {
        scanf("%lld %lld", &a, &b);
        v[a].push_back(Node(b, 1, 0));
        v[b].push_back(Node(a, 1, 0));
    }
    for (int i = 0; i < k; ++i) {
        scanf("%lld %lld %lld", &a, &b, &c);
        triplet idx = triplet(a, b, c);
        m[idx] = 1;
    }
    dij(1);
    ll mn(1e17), pre(-1);
    for (int i = 1; i <= n; ++i) {
        if (dist[n][i] < mn) pre = i;
        mn = min(mn, dist[n][i]);
    }

    if (mn == 1e17) puts("-1");
    else {
        printf("%lld\n", mn);
        track_parent(n, pre);
        puts("");
    }
    return 0;
}