//
// Created by Psy.C on 2026/9/19.
//
/**
add(u,v,w,cs)：正向容量 w、费用 cs，反向容量 0、费用 -cs（用 i^1 配反向边）。
spfa()：从 S 跑最短路（费用为边权），松弛条件 c[i]>0 && dis[j] > dis[u]+sc[i]，并把 cur[j]=head[j] 设置当前弧起点。
dfs()：沿 dis[j]==dis[u]+sc[i] 的最短路径做多路增广，同时累加费用 sum += p*sc[i]。
dinic()：循环 spfa() 直到无可增广路，内层反复 dfs(S,inf) 累加流量
节点划分：

S = 0
第 i 个元素：i（左部）与 i+n（右部）
辅助汇 2*n+1
真正汇 T = 2*n+2
边：

S → i，容量 1，费用 0：源给每个左部元素 1 单位供应。
i → i+n，容量 1，费用 a[i]：选择第 i 个元素本身要付出代价 a[i]。
i+n → i+n+1，容量 inf，费用 0：相邻"可选段"之间可以连通（这是"连续取 k 段"或"从一个段流向下一个段"的关键边）。
i+n → 2*n+1，容量 1，费用 b[i]：把第 i 段接到辅助汇，代价 b[i]。
2*n+1 → T，容量 k，费用 0：总流量限制为 k
跑满费用流后，f.sum 累加了所有流经边的费用，输出即答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e5+5, inf = 4e18;

struct mcmf {
    int head[N];
    void init() { memset(head, -1, sizeof(head)); }
    int e[N], idx, c[N], sc[N], nxt[N];
    void add(int u, int v, int w, int cs) {
        e[idx] = v, c[idx] = w, sc[idx] = cs, nxt[idx] = head[u], head[u] = idx++;
        e[idx] = u, c[idx] = 0, sc[idx] = -cs, nxt[idx] = head[v], head[v] = idx++;
    }
    int S, T, dis[N], cur[N];
    bool vis[N];
    bool spfa() {
        for (int i = 0; i <= T; ++i) { dis[i] = inf, cur[i] = -1; }
        queue<int> q; q.push(S); dis[S] = 0; cur[S] = head[S];
        while (!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = 0;
            for (int i = head[u]; ~i; i = nxt[i]) {
                int j = e[i];
                if (c[i] > 0 && dis[j] > dis[u] + sc[i]) {
                    dis[j] = dis[u] + sc[i]; cur[j] = head[j];
                    if (!vis[j]) { vis[j] = 1; q.push(j); }
                }
            }
        }
        return dis[T] != inf;
    }
    int sum;
    int dfs(int u, int lim) {
        if (u == T) return lim;
        vis[u] = 1;
        int ans = 0;
        for (int i = cur[u]; ~i&&ans<lim; i = nxt[i]) {
            int j = e[i]; cur[u] = i;
            if (c[i] > 0 && dis[j] == dis[u] + sc[i] && !vis[j]) {
                int p = dfs(j, min(c[i], lim-ans));
                ans += p; c[i] -= p; c[i^1] += p;
                sum += p*sc[i];
            }
        }
        vis[u] = 0;
        return ans;
    }
    int dinic() {
        int ans = 0;
        while (spfa()) {
            int u;
            while ((u = dfs(S, inf))) ans += u;
        }
        return ans;
    }
} f;

int n, k, a[N], b[N];
signed main() {
    fast; f.init();
    cin >> n >> k; f.S = 0, f.T = 2*n+2;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        f.add(f.S, i, 1, 0);
        f.add(i, i+n, 1, a[i]);
    }
    for (int i = 1; i < n; ++i)
        f.add(i+n, i+n+1, inf, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        f.add(i+n, 2*n+1, 1, b[i]);
    }
    f.add(2*n+1, f.T, k, 0); f.dinic();
    cout << f.sum << '\n';
    return 0;
}