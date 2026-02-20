//
// Created by Psy.C on 2026/2/20.
//
/**
v: 目标节点
c: 边权
n: 下一条边的索引
cnt: 节点数量
sum: 距离和
sqr: 距离平方和
u, v: 查询的两个节点
lca: 最近公共祖先
h[u]: 节点u的邻接边链表头
fa[N]: 并查集父节点
pre[N]: 树上父节点
dis[N]: 到根节点的距离
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int B = 1e5, N = B+1, M = (B<<2)+1, mod = 1e9+7;

struct edge { int v, c, n; } e[M];
struct node { int cnt, sum, sqr; } dp[N], tot[N];
struct qr { int u, v, lca; } q[N];

int cnt;///边的计数器
void add(const int u, const int v, const int c, int h[]) {
    e[cnt] = {v, c, h[u]}; h[u] = cnt++;
}

int fa[N], pre[N], dis[N];
int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int head[N];///存储每个节点的邻接边链表头
void dfs(const int u) {
    dp[u] = {1, 0, 0};
    for (int i = head[u]; ~i; i = e[i].n) {
        const int v = e[i].v, c = e[i].c;
        if (v == pre[u]) continue;
        pre[v] = u;//设置父节点，更新距离，递归处理子树
        dis[v] = (dis[u] + c) % mod;
        dfs(v);
        //合并子树信息到当前节点
        dp[u].cnt = (dp[u].cnt+dp[v].cnt) % mod;
        dp[u].sum = (dp[u].sum+dp[v].sum+1ll*dp[v].cnt*c) % mod;
        dp[u].sqr = (dp[u].sqr+dp[v].sqr+2ll*dp[v].sum*c+1ll*dp[v].cnt*c%mod*c)%mod;
    }
}

void dfs2(const int u) {//节点u去掉子树v后剩余部分的信息
    for (int i = head[u]; ~i; i = e[i].n) {
        const int v = e[i].v, c = e[i].c;
        if (v == pre[u]) continue;
        node t{};
        t.cnt = ((tot[u].cnt-dp[v].cnt)%mod+mod)%mod;
        t.sum = ((tot[u].sum-dp[v].sum-1ll*c*dp[v].cnt)%mod+mod)%mod;
        t.sqr = ((tot[u].sqr-dp[v].sqr-2ll*dp[v].sum*c-1ll*dp[v].cnt*c%mod*c)%mod+mod)%mod;
        //将子树信息与剩余部分合并，更新tot[v]
        tot[v].cnt = (dp[v].cnt+t.cnt)%mod;
        tot[v].sum = (dp[v].sum+t.sum+1ll*c*t.cnt)%mod;
        tot[v].sqr = (dp[v].sqr+t.sqr+2ll*t.sum*c+1ll*t.cnt*c%mod*c)%mod;
        dfs2(v);
    }
}

int vis[N], Q[N];
void dfs3(const int u) {
    fa[u] = u; vis[u] = 1;
    for (int i = head[u]; ~i; i = e[i].n) {
        const int v = e[i].v;
        if (v == pre[u]) continue;
        dfs3(v);//递归处理子树
        fa[v] = u;//更新并查集
    }
    for (int i = Q[u]; ~i; i = e[i].n) {
        if (const int v = e[i].v; vis[v])
            q[e[i].c].lca = find(v);
    }
}

void init() {
    cnt = 0;
    pre[1] = 0; dis[1] = 0;
    memset(head, -1, sizeof(head));
    memset(Q, -1, sizeof(Q));
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < N; ++i) fa[i] = i;
}

int n, qq;
int main() {
    fast; cin >> n; init();
    int u, v, c;
    for (int i = 1; i < n; ++i) {
        cin >> u >> v >> c;
        add(u, v, c, head); add(v, u, c, head);
    }
    cin >> qq;
    for (int i = 0; i < qq; ++i) {
        cin >> u >> v; q[i] = {u, v};
        add(u, v, i, Q); add(v, u, i, Q);
    }
    dfs(1); tot[1] = dp[1];
    dfs2(1); dfs3(1);
    for (int i = 0; i < qq; ++i) {
        u = q[i].u, v = q[i].v;
        const int f = q[i].lca, d = ((dis[u]+dis[v]-2*dis[f])%mod+mod)%mod;
        if (f != v) {
            const int t = (dp[v].sqr+2ll*dp[v].sum*d+1ll*dp[v].cnt*d%mod*d)%mod;
            cout << ((2ll*t-tot[u].sqr)%mod+mod)%mod << '\n';
        } else {
            node t{};
            t.cnt = ((tot[v].cnt-dp[v].cnt)%mod+mod)%mod;
            t.sum = ((tot[v].sum-dp[v].sum)%mod+mod)%mod;
            t.sqr = ((tot[v].sqr-dp[v].sqr)%mod+mod)%mod;
            const int tmp = (t.sqr+2ll*d*t.sum+1ll*t.cnt*d%mod*d)%mod;
            cout << ((tot[u].sqr-2ll*tmp)%mod+mod)%mod << '\n';
        }
    }
    return 0;
}