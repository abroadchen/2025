//
// Created by Psy.C on 2026/4/20.
//
/**
使用SPFA算法在残留网络中找最短增广路
d[N]: 距离数组
inc[N]: 到达每个点的最小剩余容量
pre[N]: 前驱边
update(): 沿增广路更新残量图
mnc_mxf(): 持续增广直到无法找到路径
m: 边数
u[i], v[i], c[i], f[i]: 边的起点、终点、容量、流量
L[N], R[N]: 节点的需求量统计
ans: 答案偏移量
L[v[i]] += f[i]: 节点v[i]的需求
R[u[i]] += f[i]: 节点u[i]的供应
S: 超级源点
T: 超级汇点
R[i] - L[i] > 0: 节点i有多余供应，连向汇点
R[i] - L[i] < 0: 节点i有需求，从源点连入
情况1：f[i] <= c[i]
可以减少流量：add(u[i], v[i], c[i]-f[i], 1)
可以增加流量：add(u[i], v[i], inf, 2)
可以反向流动：add(v[i], u[i], f[i], 1)
情况2：f[i] > c[i]
必须减少超出容量的流量：ans += f[i] - c[i]
只能反向或减少：添加相应边
ans: 必须付出的代价
mnc_mxf(): 最小费用最大流的费用
O(FE): F是流量，E是边数


添加从节点n到节点1的无限容量、零费用边
这是环边，用于连接首尾节点，形成环形结构
通常用于处理环上的流量平衡问题
add(u[i], v[i], c[i]-f[i], 1):
从u[i]到v[i]添加容量为c[i]-f[i]的边
费用为1（单位增流成本）
表示还可以向这条边增加c[i]-f[i]的流量
add(u[i], v[i], inf, 2):
从u[i]到v[i]添加无限容量的边
费用为2（较高的增流成本）
表示可以大幅增加流量，但成本更高
add(v[i], u[i], f[i], 1):
从v[i]到u[i]（反向）添加容量为f[i]的边
费用为1（单位退流成本）
表示可以减少这条边的流量，最多减到0
ans += f[i] - c[i]:
累加f[i] - c[i]到答案
这是必须付出的代价，因为流量超出了容量限制
add(u[i], v[i], inf, 2):
从u[i]到v[i]添加无限容量边
费用为2
表示可以增加流量到容量上限
add(v[i], u[i], f[i]-c[i], 0):
从v[i]到u[i]添加容量为f[i]-c[i]的边
费用为0
表示必须减少f[i]-c[i]的流量才能满足容量限制
add(v[i], u[i], c[i], 1):
从v[i]到u[i]添加容量为c[i]的边
费用为1
表示可以进一步减少流量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1007, M = 2e6+7, inf = 0x3f3f3f3f;
int n;
namespace grf {
    int cnt = 1, to[M], nxt[M], head[N], cap[M], cost[M];
    void add(int u, int v, int _fl, int _c) {
        to[++cnt] = v, cap[cnt] = _fl, cost[cnt] = _c, nxt[cnt] = head[u], head[u] = cnt;
        to[++cnt] = u, cap[cnt] = 0, cost[cnt] = -_c, nxt[cnt] = head[v], head[v] = cnt;
    }

    queue<int> q;
    int S, T, d[N], inc[N], pre[N];
    bool vis[N];
    bool spfa() {
        for (int i = min(1, S); i <= max(n, T); ++i) d[i] = inf;
        memset(vis, 0, sizeof vis); q.push(S); d[S] = 0; vis[S] = true; inc[S] = inf;
        while (!q.empty()) {
            int u = q.front(); vis[u] = false; q.pop();
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if (!cap[i]) continue;
                if (d[v] > d[u] + cost[i]) {
                    d[v] = d[u] + cost[i];
                    inc[v] = min(inc[u], cap[i]);
                    pre[v] = i;
                    if (!vis[v]) vis[v] = true, q.push(v);
                }
            }
        }
        if (d[T] == inf) return false;
        return true;
    }

    int mnc, mxf;
    void update() {
        int x = T;
        while (x != S) {
            int i = pre[x];
            cap[i] -= inc[T];
            cap[i^1] += inc[T];
            x = to[i^1];
        }
        mxf += inc[T];
        mnc += d[T]*inc[T];
    }
    int mnc_mxf() {
        while (spfa()) update();
        return mnc;
    }
}
using namespace grf;

int m, u[N], v[N], c[N], f[N], L[N], R[N], ans;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> u[i] >> v[i] >> c[i] >> f[i];
        L[v[i]] += f[i]; R[u[i]] += f[i];
    }
    S = n + 1, T = n + 2;
    for (int i = 1; i <= n; ++i) {
        if (R[i] - L[i] > 0) add(i, T, R[i]-L[i], 0);
        else add(S, i, L[i]-R[i], 0);
    }
    add(n, 1, inf, 0);
    for (int i = 1; i <= m; ++i) {
        if (f[i] <= c[i]) {//当前流量不超过容量
            add(u[i], v[i], c[i]-f[i], 1);
            add(u[i], v[i], inf, 2);
            add(v[i], u[i], f[i], 1);
        } else {
            ans += f[i] - c[i];
            add(u[i], v[i], inf, 2);
            add(v[i], u[i], f[i]-c[i], 0);
            add(v[i], u[i], c[i], 1);
        }
    }
    cout << ans + mnc_mxf() << '\n';
    return 0;
}