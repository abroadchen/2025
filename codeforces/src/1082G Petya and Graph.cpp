//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
链式前向星（邻接表）存边，cnt 为边计数。
注意 e[N<<1]：每条正向边配一条反向边（容量 0），用 i^1 互为反向边（因为 add 每连一条真边就 cnt++ 两次）。这是 Dinic + i^1 反向增广的基础。
加入一条正向边（u→v，容量 cap）和反向边（v→u，容量 0），便于后续增广时退还流量
1. bfs() —— 分层

建层次图：从源点 sp 出发，deg[] 存每个节点的层次（算法里叫 deg，实为 level/depth）。
只沿容量>0 的边扩展；到汇点 tp 即返回 1（说明还有增广路）。
初始化 deg 为 -1，deg[sp]=0。
2. dfs(u, flow) —— 多路增广

带当前弧优化 cur[]：每轮 bfs 后把 cur= head，dfs 时用引用 &i 跳过已流满的边。
递归向 deg[v]==deg[u]+1 且 cap>0 的邻点送流量。
用 e[i^1].cap += f 更新反向边（撤销操作）。
若该点已无路（res==0），置 deg[u]=-1 剪枝。
返回该点实际送出的流量 f
重复「分层 → 多路增广」直到无增广路，累加流量得最大流
项目 j（右部 1+n..n+m）‍：由源点 sp 连入，容量 = 该项目价值 x（add(sp,j,x)）。
资源/左部点 i（1..n）‍：连到汇点 tp，容量 = 该点的上限/成本 x（add(i,tp,x)）。
约束 INF 边：每个项目 j 连到它依赖的 u、v 两个点，容量 INF，强制"若割掉左边（不选项目）则必须同时把右边（资源）包含在 S 侧"之类的最小割性质。
sum 累加所有项目价值
答案 = 项目价值总和 − 最小割（即最大流）
为什么？这是最小割=最大流定理 + 最大权闭合 / project selection 建模。最小割把图分成 S、T 两侧：割掉的边总和 = 损失（放弃某些项目价值 + 承担某些资源成本）。最小化割 = 最大化净收益。INF 约束避免"无代价违约"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+5, inf = 0x3f3f3f3f;
constexpr ll INF = 1e16;

struct node { ll v, nxt, cap; } e[N<<1];

ll cnt, head[N];
void add(ll u, ll v, ll cap) {
    e[cnt].v = v; e[cnt].cap = cap; e[cnt].nxt = head[u]; head[u] = cnt++;
    e[cnt].v = u; e[cnt].cap = 0; e[cnt].nxt = head[v]; head[v] = cnt++;
}
void init() { cnt = 0; memset(head, -1, sizeof(head)); }

ll deg[N], sp, tp;
ll bfs() {
    memset(deg, -1, sizeof(deg)); deg[sp] = 0;
    queue<ll> q; q.push(sp);
    while (!q.empty()) {
        ll u = q.front();
        if (u == tp) return 1; q.pop();
        for (ll i = head[u]; ~i; i = e[i].nxt) {
            ll v = e[i].v, cap = e[i].cap;
            if (deg[v] == -1 && cap) { deg[v] = deg[u] + 1; q.push(v); }
        }
    }
    return 0;
}

ll cur[N];
ll dfs(ll u, ll flow) {
    if (u == tp || flow == 0) return flow;
    ll res = 0, f;
    for (ll &i = cur[u]; ~i; i = e[i].nxt) {
        ll v = e[i].v, cap = e[i].cap;
        if (deg[v] == deg[u] + 1 && (f = dfs(v, min(flow-res, cap))) > 0) {
            e[i].cap -= f; e[i^1].cap += f; res += f;
            if (res == flow) return flow;
        }
    }
    if (!res) deg[u] = -1;
    return res;
}
ll dinic() {
    ll ans = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        ans += dfs(sp, inf);
    }
    return ans;
}

ll n, m, sum;
int main() {
    fast;
    cin >> n >> m; sp = 0, tp = n+m+1; init();
    for (ll i = 1, x; i <= n; i++) { cin >> x; add(i, tp, x); }
    for (ll i = 1, j = i+n, u, v, x; i <= m; i++, j++) {
        cin >> u >> v >> x; add(sp,j,x); sum += x;
        add(j,u, INF); add(j,v, INF);
    }
    cout << sum-dinic() << '\n';
    return 0;
}