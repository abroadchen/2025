//
// Created by Psy.C on 2025/11/20.
//
/*
*x: 起始位置
d: 长度
t: 通行时间
p: 价格
id: 编号
 *
*u: 起点
to: 终点
nxt: 链式前向星的下一条边
val: 边的权重
id: 边的编号
 *
*道路: 0 ----|------|====================|---- L
           ↑      ↑                    ↑
      进入点  特殊路段起点         特殊路段终点
    (x-p[i].p)   (x)              (x+p[i].d)
 *支付费用p[i].p才能进入
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

typedef long long ll;
const int N = 4e5+100, inf = 0x3f3f3f3f;

int n, tot(0), cnt(0),
head[N<<1], vis[N], pre[N];
ll L, dis[N], d[N];
struct node {
    ll x, d, t, p;
    int id;
} p[N];
struct edge { int u, to, nxt; ll val; int id; } e[N<<1];
void add(int u, int v, ll w, int id) {
    e[tot].u = u, e[tot].nxt = head[u], e[tot].to = v,
    e[tot].val = w, e[tot].id = id, head[u] = tot++;
}

struct node2 {//用于Dijkstra算法的优先队列节点
    int u; ll val;
    node2(int a, ll b) { u = a; val = b; }
    bool operator<(const node2& b) const { return val > b.val; }
};

void dijkstra() {
    priority_queue<node2> q;
    dis[1] = 0; pre[1] = -1;
    q.push({1, 0ll});
    while (q.size()) {
        int u = q.top().u; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = head[u]; ~i; i = e[i].nxt) {
            int to = e[i].to; ll w = e[i].val;
            if (dis[to] > dis[u] + w) {
                dis[to] = dis[u] + w;
                q.push({to, dis[to]});
                pre[to] = i;
            }
        }
    }
    cout << dis[cnt] << '\n';
    stack<int> s;
    for (int i = pre[cnt]; ~i; i = pre[e[i].u]) {
        if (e[i].id != -1) s.push(e[i].id);
    }
    cout << s.size() << '\n';
    while (s.size()) { cout << s.top() << ' '; s.pop(); }
}



int main() {
    cin.tie(0)->sync_with_stdio(0);
    scanf("%d%lld", &n, &L);
    memset(head, -1, sizeof(head));
    memset(dis, inf, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld%lld%lld", &p[i].x, &p[i].d, &p[i].t, &p[i].p);
        p[i].id = i;
        if (p[i].x - p[i].p < 0 || p[i].x + p[i].d > L) continue;//进入点不能为负，终点不能超过总长度
        d[++cnt] = p[i].x - p[i].p; d[++cnt] = p[i].x + p[i].d;
    }
    d[++cnt] = 0; d[++cnt] = L;//添加起点0和终点L，排序并去重
    sort(d + 1, d + cnt + 1); cnt = unique(d + 1, d + cnt + 1) - d - 1;
    int x, y; ll w;
    for (int i = 1; i <= n; ++i) {//为每个有效特殊路段添加边
        if (p[i].x - p[i].p < 0 || p[i].x + p[i].d > L) continue;
        x = lower_bound(d + 1, d + cnt + 1, p[i].x - p[i].p) - d;
        y = lower_bound(d + 1, d + cnt + 1, p[i].x + p[i].d) - d;
        add(x, y, p[i].p + p[i].t, p[i].id);
    }
    for (int i = 2; i <= cnt; ++i) {//添加相邻关键点之间的普通路径边
        x = i - 1, y = i;
        w = d[i] - d[i - 1];
        add(x, y, w, -1);
        add(y, x, w, -1);
    }
    dijkstra();
    return 0;
}