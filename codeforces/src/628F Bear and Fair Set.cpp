//
// Created by Psy.C on 2026/3/28.
//
/**
rev: 反向边在终点邻接表中的索引
G[][]: 邻接表表示的网络流图 G[i]: 存储从节点i出发的所有边
添加容量为cap的正向边
添加容量为0的反向边（用于增广路算法）
rev字段记录反向边的索引，方便反向流量更新
构建分层图（level graph）
d[v]表示节点v到源点的距离
只考虑还有剩余容量的边
使用Dinic算法计算最大流
重复构建层次图和寻找增广路
当无法到达汇点时，达到最大流

源点s
时间段节点[0,q]
具体时刻节点[q+1, q+b]
星期几桶节点[b+q+1, b+q+5]（假设一周5天）
汇点t
流量约束
从源点到时间段：容量为该时间段的需求数量
从时间段到具体时刻：容量为1，表示一个事件发生在特定时刻
从具体时刻到星期几：容量为1，按模5分配
从星期几到汇点：容量为n/5，确保分布均匀

从源点到时间段节点i添加容量为tmp的边
对于时间段i内的每个时刻j
从时间段i到具体时刻节点q+j添加容量为1的边
从具体时刻j到星期几桶j%5+b+q+1添加容量为1的边（按星期分类）
对5个星期几桶，每个到汇点添加容量为n/5的边
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e4+5, inf = 0x3fffffff;

struct node { int to, cap, rev; };
vector<node> G[N<<1];

void add(int fr, int to, int cap) {
    //此时G[to]还没有反向边，所以G[to].size()就是反向边在G[to]中的位置
    G[fr].push_back(node(to, cap, G[to].size()));
    G[to].push_back(node(fr, 0, G[fr].size()-1));//G[fr].size()-1: 正向边在G[fr]中的位置
}

int d[N<<1], s;
void bfs() {
    memset(d, -1, sizeof(d));
    queue<int> q; d[s] = 0; q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int i = 0; i < G[v].size(); ++i) {//遍历节点v的所有出边
            auto &e = G[v][i];//获取第i条边的引用
            if (e.cap > 0 && d[e.to] < 0) {//边有剩余容量且目标节点未访问
                d[e.to] = d[v] + 1;//目标节点距离为当前节点距离+1
                q.push(e.to);//目标节点加入队列
            }
        }
    }
}

int t, st[N<<1];//每个节点上次访问到哪条边（当前弧优化）
int dfs(int v, int f) {
    if (v == t) return f;//当前路径上的最小剩余容量
    //从上次访问的位置开始遍历（当前弧优化）
    for (int &i = st[v]; i < G[v].size(); ++i) {//修改i会同时修改st[v]
        auto &e = G[v][i];
        if (e.cap > 0 && d[v] < d[e.to]) {//沿着层次图的方向前进
            int tf = dfs(e.to, min(f, e.cap));//递归寻找增广路径，流量限制为min(f, e.cap)
            if (tf > 0) {//如果找到了增广路径
                e.cap -= tf;//正向边容量减少
                G[e.to][e.rev].cap += tf;//反向边容量增加（用于后续退流）
                return tf;//返回找到的流量
            }
        }
    }
    return 0;//没找到增广路径，返回0
}
int mxf() {
    int flow = 0;
    for (;;) {
        bfs();
        if (d[t] < 0) return flow;
        memset(st, 0, sizeof(st));
        int f;
        while ((f=dfs(s, inf)) > 0)
            flow += f;//累加找到的流量
    }
}
///b: 上界
int q, b, n;
ii u[N];///查询对
int get() {
    for (int i = 0; i <= q; ++i) {
        int tmp = u[i].second - u[i-1].second;
        if (tmp < 0) return 0;//不可能的情况
        if (tmp > u[i].first - u[i-1].first) return 0;//超出范围
        add(s, i, tmp);//从源点到时间段i的边
        for (int j = u[i-1].first+1; j <= u[i].first; ++j) {
            add(i, q+j, 1);//时间段i到具体时刻j
            add(q+j, j%5+b+q+1, 1);//具体时刻j到星期几
        }
    }
    for (int i = 0; i < 5; ++i)
        add(i+b+q+1, t, n/5);//星期几桶到汇点
    return mxf() == n;//是否能达到最大流量n
}

int main() {
    fast;
    cin >> n >> b >> q;
    for (int i = 0, x, y; i < q; ++i) {
        cin >> x >> y;
        u[i] = {x, y};
    }
    sort(u, u+q); u[q] = {b, n};
    s = q + b + 6, t = s + 1;
    if (get()) cout << "fair\n";
    else cout << "unfair\n";
    return 0;
}