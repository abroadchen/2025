//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
每条边记录：u,v 两个端点、权重 w、编号 d。
按 w 排序（Kruskal 用）。
N<<1：需要约 2n 条"区间端点边"。
add(u,v,w,d) 只是入边
递归遍历树（以 1 为根）。
每个节点 u 维护它子树覆盖的"区间" [l[u], r[u]]。
叶子节点分配一个新的区间下标 ++cur（l=r=cur），用于当作图里的"点"。
每个节点向图里加入一条横跨整个子树区间的边：(l[u], r[u]+1)，权重 w[u]。
这一步把"原树上每个点 u 连接到其子树区间内的所有点"压缩成一条区间边，从而把 O(n²) 的连边优化成 O(n)
把所有权值相同的边先收集成一组（lst..now）。
在并（union）之前预先判断每条等权边是否"两端点当前不在同一集合"——满足则把对应原边 d 标记进 b[]（b[i]=1）。
然后再对这组边做实际的 union，累加 res
读入树的点权 w[i] 和树边。
dfs(1,0) 生成区间边。
跑分组 Kruskal 得到 res（MST 总权）并标记必选边。
第一行输出 MST 权值和，第二行输出必选边条数，第三行输出这些边的编号
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define int long long
using namespace std;

constexpr int N = 2e5+10, inf = 1e18;

struct node {
    int u, v, w, d;
    bool operator<(const node& o) const { return w < o.w; }
} e[N<<1];

int cnt;
void add(int u, int v, int w, int d) { e[++cnt] = {u,v,w,d}; }

int l[N], r[N], cur, w[N];
vector<int> g[N];
void dfs(int u, int fa) {
    l[u] = inf;
    bool f = 1;
    for (int i = 0; i < g[u].size(); i++) {
        if (g[u][i] == fa) continue;
        f = 0;
        dfs(g[u][i], u);
        l[u] = min(l[u], l[g[u][i]]), r[u] = max(r[u], r[g[u][i]]);
    }
    if (f) l[u] = r[u] = ++cur;
    add(l[u], r[u]+1, w[u], u);
}
int fa[N<<1];
inline int find(int u) { return u == fa[u]? u : fa[u] = find(fa[u]); }

int n;
bool b[N];
int kruskal() {
    sort(e+1, e+cnt+1);
    rep(i,n) fa[i] = i;
    int res = 0;
    rep(i,cnt) {
        int lst = i, now = i;
        if (find(e[now].u) != find(e[now].v)) b[e[now].d] = 1;
        while (now < cnt && e[now+1].w == e[lst].w) {
            now++;
            if (find(e[now].u) != find(e[now].v)) b[e[now].d] = 1;
        }
        for (int j = lst; j <= now; j++)
            if (find(e[j].u) != find(e[j].v)) {
                res += e[j].w;
                fa[find(e[j].u)] = find(e[j].v);
            }
        i = now;
    }
    return res;
}

signed main() {
    fast;
    cin >> n;
    rep(i,n) cin >> w[i];
    rep(i,n-1) {
        int u, v; cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(1,0);
    cout << kruskal() << '\n';
    int t = 0;
    rep(i,n) if (b[i]) t++;
    cout << t << '\n';
    rep(i,n) if (b[i]) cout << i << ' ';
    return 0;
}