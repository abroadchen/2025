//
// Created by Psy.C on 2026/1/5.
//
/**
* d: 距离数组
b: 标记数组（是否在队列中）
q: 队列数组（大小扩大8倍防止溢出）
pre: 前驱节点
ed: 到达当前节点的边
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 64010 //最大节点数
#define L 90 //网格最大边长
#define M (L*4+N*4) //最大边数
#define inf 2139062143
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

//目标节点、容量、费用、下一条边
int e[M], nxt[M], wt[M], cost[M], siz = 1, head[N];//从1开始计数（便于处理反向边）
void add(const int u, const int v, const int w, const int c) {
    e[++siz] = v; wt[siz] = w; cost[siz] = c; nxt[siz] = head[u]; head[u] = siz;
}
void add_edge(const int u, const int v, const int w, const int c) {
    add(u,v,w,c); add(v,u,0,-c);
}

int m;
int get(const int i, const int j) { return (i - 1) * m + j; }//转换为一维节点编号

int d[N], b[N], q[N<<3], pre[N], ed[N];
bool spfa(const int s, const int t) {
    memset(d,127,sizeof(d));
    memset(b,0,sizeof(b));
    d[(q[1] = s)] = 0; b[s] = 1;
    int l = 1, r = 1;
    while (l <= r) {
        const int cur = q[l++];//遍历当前节点的所有出边
        for (int p = head[cur]; p; p = nxt[p]) {
            const int& v = e[p];
            if (wt[p] && d[cur] + cost[p] < d[v]) {//边有容量且可以松弛，则更新距离
                d[v] = d[cur] + cost[p];
                if (!b[v]) b[v] = 1, q[++r] = v;
                pre[v] = cur, ed[v] = p;
            }
        }
        b[cur] = 0;//出队时标记为不在队列中
    }
    return d[t] < d[0];
}


int calc(const int s, const int t) {
    int tot = 0;
    while (spfa(s, t)) {
        int flow = inf;
        for (int x = t; x ^ s; x = pre[x]) flow = min(flow, wt[ed[x]]);//找到路径上的最小容量
        tot += flow * d[t];//流量 × 源点到汇点的最短距离
        for (int x = t; x ^ s; x = pre[x]) wt[ed[x]] -= flow, wt[ed[x]^1] += flow;
    }
    return tot;
}

int main() {
    fast;
    int n; cin >> n >> m;
    const int s = n * m + 1, t = n * m + 2;
    int a[L][L];
    rep(i,n) rep(j,m) cin >> a[i][j];
    rep(i,n) rep(j,m) {
        if (i + j & 1) add_edge(s, get(i, j), 1, 0);//奇数坐标和的点连接源点
        else add_edge(get(i, j), t, 1, 0);//偶数的连接汇点
        if (j < m) {//与右边邻居连接 值不同费用为1，否则为0
            if (i + j & 1) add_edge(get(i, j), get(i, j+1), 1, a[i][j]!=a[i][j+1]);
            else add_edge(get(i, j+1), get(i, j), 1, a[i][j]!=a[i][j+1]);
        }
        if (i < n) {//与下边邻居连接
            if (i + j & 1) add_edge(get(i, j), get(i+1, j), 1, a[i][j]!=a[i+1][j]);
            else add_edge(get(i+1, j), get(i, j), 1, a[i][j]!=a[i+1][j]);
        }
    }
    cout << calc(s, t) << '\n';
    return 0;
}