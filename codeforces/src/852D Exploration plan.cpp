//
// Created by Psy.C on 2026/9/29.
//
/**
存图数组：e 边终点、head 链表头、nxt 下一条边、c 容量。
add(u,v,w) 加一条带容量 w 的有向边并附带一条容量 0 的反向边（用于最大流退流），idx 成对递增——这是最大流网络的标准建边方式
dis[M][M] 存全源最短路（M=605 意味着 n ≤ 约 600）。
对每个点 s 依次跑一次 dijkstra(s)，得到任意两点间最短距离 dis[i][j]。
n=1e6 的数组其实主要给图边/流量网络用的
bfs 建立分层图 d[]（距离），同时初始化当前弧 cur[]。
dfs 在分层图上多路增广，用 cur 当前弧优化；c[i^1] 是反向边流量回退（因为 add 成对建边，i^1 即反向边）。
dinic 反复直到没有增广路，返回最大流值
构建了一个二分图网络：
左部（源点供给）‍：节点 i（pd[i] 表示该点作为"供给点"的供应量，add(S,i,pd[i]) 从源点给容量 pd[i]）。
右部（需求点）‍：节点 i+n，每个经 add(i+n,T,1) 连到汇点，容量 1（每个目标最多被一个供给点覆盖一次）。
供需匹配边：若 dis[i][j] ≤ x（供给点在最大距离 x 内能覆盖目标点 j），连 i → j+n，容量很大。
那么最大流 = 在距离限制 x 下最多能覆盖多少个目标点。
check(x) 返回 最大流 ≥ k，即能否在"最大距离 ≤ x"的前提下覆盖至少 k 个目标。
读入：n 个点、m 条边、p 个候选供给点、目标 k。
pd[g[i]]++：p 个"供给点"计数（同一个点可以计数多次 → 容量）。
建无向图 G，然后对每个点跑 dijkstra 求出 dis。
之后在距离上限 x 上二分：check(x) 表示"在最大允许距离 x 内能否覆盖至少 k 个目标"。
找最小的可行 x 作为答案 ans；若始终不可行输出 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e6+5, M = 605, inf = 1731312;

int e[N], head[N], idx, nxt[N], c[N];
static void add(int u, int v, int w) {
    e[idx] = v, c[idx] = w, nxt[idx] = head[u], head[u] = idx++;
    e[idx] = u, c[idx] = 0, nxt[idx] = head[v], head[v] = idx++;
}

struct node {
    int u, d;
    node(int u, int d) : u(u), d(d) {}
    bool operator<(const node& o) const {
        return d > o.d;
    }
};

int n, dis[M][M];
bool vis[N];
vector<ii> G[N];
static void dijkstra(int s) {
    for (int i = 1; i <= n; ++i) vis[i] = 0; dis[s][s] = 0;
    priority_queue<node> q; q.emplace(s, 0);
    while (!q.empty()) {
        int u = q.top().u; q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto [fst, snd] : G[u]) {
            if (dis[s][fst] > dis[s][u] + snd) {
                dis[s][fst] = dis[s][u] + snd;
                q.emplace(fst, dis[s][fst]);
            }
        }
    }
}

int T, d[N], cur[N], S = 0;
static bool bfs() {
    for (int i = 0; i <= T; ++i) d[i] = cur[i] = -1;
    queue<int> q; q.push(S); d[S] = 0, cur[S] = head[S];
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = nxt[i]) {
            int j = e[i];
            if (c[i] > 0 && d[j] == -1) {
                d[j] = d[u] + 1;
                cur[j] = head[j];
                if (j == T) return 1;
                q.push(j);
            }
        }
    }
    return 0;
}

static int dfs(int u, int lim) {
    if (u == T) return lim;
    int sum = 0;
    for (int i = cur[u]; ~i&&sum < lim; i = nxt[i]) {
        cur[u] = i;
        int j = e[i];
        if (c[i] > 0 && d[j] == d[u] + 1) {
            int w = dfs(j, min(c[i], lim-sum));
            if (!w) d[j] = -1;
            sum += w; c[i] -= w; c[i^1] += w;
        }
    }
    return sum;
}

static int dinic() {
    int res = 0;
    while (bfs()) {
        int p;
        while ((p = dfs(S, INT_MAX))) res += p;
    }
    return res;
}

int pd[N], k;
static bool check(int x) {
    for (int i = 0; i <= T+5; ++i) head[i] = -1;
    idx = 0;
    for (int i = 1; i <= n; ++i) {
        if (!pd[i]) continue;
        for (int j = 1; j <= n; ++j) {
            if (dis[i][j] <= x)
                add(i, j+n, INT_MAX);
        }
        add(S, i, pd[i]);
    }
    for (int i = 1; i <= n; ++i) add(i+n, T, 1);
    return dinic() >= k;
}

int m, p, g[N];
int main() {
    fast;
    memset(head, -1, sizeof(head));
    memset(dis, 0x3f, sizeof(dis));
    cin >> n >> m >> p >> k; T = n+n+1;
    for (int i = 1; i <= p; ++i) cin >> g[i], pd[g[i]]++;
    for (int i = 1, u, v, w; i <= m; ++i) {
        cin >> u >> v >> w;
        G[u].emplace_back(v, w); G[v].emplace_back(u, w);
    }
    for (int i = 1; i <= n; ++i) dijkstra(i);
    int l = 0, r = inf, ans = -1;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (check(mid)) ans = mid, r = mid-1;
        else l = mid+1;
    }
    cout << ans << '\n';
    return 0;
}