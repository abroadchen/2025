//
// Created by Psy.C on 2025/11/27.
//
/*
*N: 最大节点数(10000)
M: 最大边数(100000)
K: 辅助常量(3000)
inf: 无穷大值(约10亿)
*head[]: 链式前向星存储图的头指针数组
cnt: 边的计数器
*st: 开始时间
et: 结束时间
ct: 成本/收益
id: 任务ID
 *vv: 用于存储所有时间点的向量
 *mp: 时间点到离散化编号的映射
*to: 目标节点
nxt: 下一条边的索引(链式前向星)
cap: 容量
flow: 流量
cost: 费用
id: 边的ID
*添加正向边(u->v)：容量cap，费用cost
添加反向边(v->u)：容量0，费用-cost(负费用)
使用链式前向星存储图结构
返回当前边计数
*dis[]: SPFA算法中的距离数组
pre[]: 前驱边数组
vis[]: 访问标记数组
*SPFA算法实现，用于寻找最小费用路径：
s: 源点
t: 汇点
 *初始化：距离设为无穷大，访问标记设为false，前驱设为-1
 *设置源点距离为0，标记为已访问，加入队列
*取出队首节点u
遍历u的所有邻接边
如果边还有剩余容量且能找到更短路径，则更新距离和前驱
将更新的节点加入队列
*如果汇点t没有前驱，说明无法到达，返回false
否则返回true
 *
*费用流求解函数：
s: 源点
t: 汇点
cost: 引用参数，返回总费用
*初始化流量和费用为0
循环执行SPFA直到找不到增广路径
 *找到增广路径上的最小剩余容量
 *更新路径上各边的流量和总费用
*累加总流量
返回最大流
 *
 *id[]: 存储任务对应边的ID
 *建立时间点到离散化编号的映射
 *添加相邻时间节点之间的边，容量为m，费用为0
 *添加额外的辅助边
 *连接最后一个时间节点到一个中间辅助节点
 *连接中间辅助节点到最终汇点
 *
 *为每个任务添加对应的边，容量为1，费用为负的收益
 *调用费用流算法求解，源点为0，汇点为vv.size()+2
 *输出每个任务是否被选中(流量为1表示选中)
*id[i] = 2*i
id[i] - 2 = 2i - 2 = 2(i-1)
这正好是第i个任务对应的正向边的索引
 *
 */
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e4, M = 1e5, K = 3e3, inf = 0x3f3f3f3f;
int head[N], cnt;

struct node { int st, et, ct, id; } task[N];
vector<int> vv;
map<int, int> mp;

struct edge { int to, nxt, cap, flow, cost, id; } e[M];
int add(const int u, const int v, const int cap, const int cost, const int id) {
    e[cnt].to = v; e[cnt].cap = cap; e[cnt].cost = cost; e[cnt].flow = 0;
    e[cnt].nxt = head[u]; e[cnt].id = id; head[u] = cnt++;
    e[cnt].to = u; e[cnt].cap = 0; e[cnt].cost = -cost; e[cnt].flow = 0;
    e[cnt].nxt = head[v]; e[cnt].id = id; head[v] = cnt++;
    return cnt;
}

int dis[N], pre[N];
bool vis[N];
bool spfa(const int s, const int t) {
    queue<int> q;
    for (int i = 0; i < N; ++i) {
        dis[i] = inf;
        vis[i] = false;
        pre[i] = -1;
    }
    dis[s] = 0; vis[s] = true; q.push(s);
    while (!q.empty()) {
        const int u = q.front(); q.pop();
        vis[u] = false;
        for (int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            if (e[i].cap > e[i].flow && dis[v] > dis[u] + e[i].cost) {
                dis[v] = dis[u] + e[i].cost;
                pre[v] = i;
                if (!vis[v]) { vis[v] = true; q.push(v); }
            }
        }
    }
    if (pre[t] == -1) return false;
    return true;
}


int solve(const int s, const int t, int& cost) {
    int flow = 0; cost = 0;
    while (spfa(s, t)) {
        int mn = inf;
        for (int i = pre[t]; i != -1; i = pre[e[i^1].to]) {
            if (mn > e[i].cap - e[i].flow) mn = e[i].cap - e[i].flow;
        }
        for (int i = pre[t]; i != -1; i = pre[e[i^1].to]) {
            e[i].flow += mn;
            e[i^1].flow -= mn;
            cost += e[i].cost * mn;
        }
        flow += mn;
    }
    return flow;
}

int id[K];
int main() {
    fast;
    int n, m; cin >> n >> m; cnt = 0;
    for (auto& x : head) x = -1;
    for (int i = 1; i <= n; ++i) {
        cin >> task[i].st >> task[i].et >> task[i].ct;
        task[i].et += task[i].st - 1;//调整结束时间为实际结束时间
        task[i].id = i;
        vv.push_back(task[i].st); vv.push_back(task[i].et);
    }
    sort(vv.begin(), vv.end());//对时间点排序并去重
    vv.erase(unique(vv.begin(), vv.end()), vv.end());
    for (int i = 0; i < static_cast<int>(vv.size()); ++i) mp[vv[i]] = i + 1;
    for (int i = 1; i <= static_cast<int>(vv.size()); ++i) add(i - 1, i, m, 0, 0);
    add(static_cast<int>(vv.size()), static_cast<int>(vv.size() + 1), m, 0, 0);
    add(static_cast<int>(vv.size() + 1), static_cast<int>(vv.size() + 2), m, 0, 0);
    for (int i = 1; i <= n; ++i)
        id[i] = add(mp[task[i].st], mp[task[i].et] + 1, 1, -task[i].ct, i);
    int ans1 = 0, ans2 = 0;
    ans1 = solve(0, static_cast<int>(vv.size() + 2), ans2);
    for (int i = 1; i <= n; ++i) cout << e[id[i] - 2].flow << ' ';
    return 0;
}