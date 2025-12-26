//
// Created by Psy.C on 2025/12/26.
//
/*
* head[u]：以u为起点的第一条边的编号
nxt[i]：第i条边的下一条边
to[i]：第i条边的终点
cap[i]：第i条边的容量
val[i]：第i条边的费用
tot：边的总数，初始化为1（保留0号边）
 *
*fl[i]：到节点i的路径上最小容量
pre[i]：节点i的前驱节点
lst[i]：到达节点i的边编号
dis[i]：到节点i的最短距离（最小费用）
返回是否能找到从s到t的路径
 *
*ans：累计最小费用
不断找最短路直到无法增广
fl[t]：当前增广路的流量
dis[t]：当前增广路的单位费用
更新正向边和反向边的容量
lst[cur]^1：利用异或操作快速找到反向边
 *
*每个点拆成两个节点：原节点i和副本节点i+n
从源点到每个原节点容量为2，从每个副本节点到汇点容量为1
 *
*如果点i的y坐标大于点j的y坐标，从点i到点j+n连边
容量为1，费用为两点间距离
 */
#include <iostream>
#include <queue>
#include <cmath>
#include <iomanip>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000001
#define inf 1000000001
using namespace std;

struct node {
    int x, y;
    bool operator<(const node rhs) const { return y > rhs.y; }//y值大的优先
} p[N];
int head[N], nxt[N], to[N], cap[N], tot = 1;
double val[N];
void add(const int u, const int v, const int z, const double k) {
    nxt[++tot] = head[u], to[tot] = v, cap[tot] = z, val[tot] = k, head[u] = tot;
}
void add_edge(const int u, const int v, const int z, const double k) {
    add(u, v, z, k); add(v, u, 0, -k);
}
double calc(const int u, const int v) {
    return sqrt((p[u].x - p[v].x) * (p[u].x - p[v].x) +
        (p[u].y - p[v].y) * (p[u].y - p[v].y));
}

int s, t, fl[N], pre[N], lst[N];
double dis[N];
bool vis[N];
bool spfa() {
    queue<int> q;
    for (int i = 1; i <= t; ++i) fl[i] = inf, dis[i] = inf, vis[i] = false;
    q.push(s); vis[s] = true; dis[s] = 0; pre[t] = -1;
    while (!q.empty()) {
        const int u = q.front(); q.pop(); vis[u] = false;
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (cap[i] && dis[v] > dis[u] + val[i]) {
                dis[v] = dis[u] + val[i], pre[v] = u, lst[v] = i;
                fl[v] = min(fl[u], cap[i]);
                if (!vis[v]) vis[v] = true, q.push(v);
            }
        }
    }
    return pre[t] != -1;
}

double ans;
int mc_mf() {
    int sum = 0;
    while (spfa()) {
        int cur = t;
        sum += fl[t], ans += fl[t] * dis[t];
        while (cur != s) {
            cap[lst[cur]] -= fl[t];
            cap[(lst[cur]^1)] += fl[t];
            cur = pre[cur];
        }
    }
    return sum;
}


int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;
    sort(p + 1, p + n + 1);
    s = n<<1|1, t = (n<<1) + 2;
    for (int i = 1; i <= n; ++i) add_edge(s, i, 2, 0), add_edge(i+n,t,1,0);
    for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) {
        if (p[i].y > p[j].y) add_edge(i,j+n,1,calc(i,j));
    }
    if (mc_mf() != n - 1) cout << "-1\n"; else cout << fixed << setprecision(6) << ans << '\n';
    return 0;
}