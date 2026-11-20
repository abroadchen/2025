//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
N 是点数上限（2×10^5）；M=34 是每个数最多能被分解出的质因子个数上限。
edge 是邻接表边结构（to 目标点、nxt 下一条边），存双向边所以数组开 N<<1。
对每个点的权值做质因数分解：
fac[pos][j] 存第 pos 个点权值的第 j 个不同质因子；
cnt[pos] 记录它有几种不同的质因子；
内层 while 把相同质因子除净，保证 fac 里存的是互不相同的质因子；
最后若还剩 x > 1（本身是大质数），把它也存进去
邻接表加边（无向，双向各加一次）。
两个 DP 数组，第二维是质因子编号：
f[u][i]：以点 u 为根的子树中，经过 u 且首尾都在 u 的质因子 i 这条链上的最长垂直路径长度（从 u 往下的一条链）；
g[u][i]：以 u 为根的子树中，穿过 u 的、两端可用质因子 i 相连的直径（即既往下又往上的"横穿"路径）
树形 DFS（递归子树）。

对每个子节点 v 处理完后，遍历 u 的所有质因子 i 和 v 的所有质因子 j：

仅当 u 和 v 共享同一质因子（fac[u][i] == fac[v][j]）时才能在同一条"质因子链"上连通；
g[u][i] = max(g[u][i], f[u][i] + f[v][j])：用"u 这边已有的最长链 + v 那边的一条链"拼出一条穿过 u 的路径，更新直径；
f[u][i] = max(f[u][i], f[v][j] + 1)：把 v 的链 +1（即过了边 u-v）作为 u 向下伸出的链。
这就是树上求直径的标准 DP，只是把「是否连通」限定为「共享同一质因子」
读入 n 个点的权值并做质因数分解；
读入 n-1 条边建无向图；
把每个点每种质因子的 f、g 都初始化为 1（单个点长度为 1）；
从根 1 开始 DFS（父节点 0）；
扫描所有点的所有质因子，取 g 的最大值作为答案输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e5+5, M = 34;

struct edge { int to, nxt; } e[N<<1];

int fac[N][M], cnt[N];
void init(int x, int pos) {
    for (int i = 2; i*i <= x; i++) {
        if (x%i == 0) fac[pos][++cnt[pos]] = i;
        while (x%i == 0) x /= i;
    }
    if (x > 1) fac[pos][++cnt[pos]] = x;
}
int tot, head[N];
void add(int u, int v) { e[++tot].to = v; e[tot].nxt = head[u]; head[u] = tot; }

int g[N][M], f[N][M];
void dfs(int u, int fa) {
    for (int k = head[u]; k; k = e[k].nxt) {
        int v = e[k].to;
        if (v != fa) {
            dfs(v, u);
            rep(i,cnt[u]) rep(j,cnt[v]) if (fac[u][i] == fac[v][j]) {
                g[u][i] = max(g[u][i], f[u][i]+f[v][j]);
                f[u][i] = max(f[u][i], f[v][j]+1);
            }
        }
    }
}

int n, w[N], ans;
int main() {
    fast;
    cin >> n;
    rep(i,n) { cin >> w[i]; init(w[i],i); }
    int u, v;
    rep(i,n-1) { cin >> u >> v; add(u, v), add(v, u); }
    rep(i,n) rep(j,cnt[i]) f[i][j] = g[i][j] = 1;
    dfs(1,0);
    rep(i,n) rep(j,cnt[i]) ans = max(ans, g[i][j]);
    cout << ans << '\n';
    return 0;
}