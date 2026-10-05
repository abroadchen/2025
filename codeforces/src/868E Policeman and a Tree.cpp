//
// Created by Psy.C on 2026/10/5.
//
/**
第一行 n：节点数。
接下来 n-1 行：树边 (u,v) 及边权 w，存邻接表 e[] 和边权矩阵 d[][]。
再读入 s、m：起点 s 和棋子数 m。
再读入 m 个节点 x[i]，标记 vis[x[i]]++（该节点放棋子）。注意 vis 记录的是每个节点有多少个棋子（可重复
vis[u]：节点 u 上的棋子数。
dfs(u, fa)：统计以 u 为根的子树内棋子总数放入 cnt。
f[u][v][flg][in]：记忆化 DP 状态。
d[u][v]：边权
u：当前所在节点。
v：相邻节点（要走过去的邻居）。
flg：当前子树内还剩余的棋子数。
in：当前处理的孩子子树中要"安放"的棋子分配数。
返回值：从当前局面出发的最小代价
叶子情况：全部棋子安放到该叶子，代价 = 进入叶子的边权 + 递归处理
分组背包 + min/max 博弈：把 in 个棋子分配到 v 的各个子树 p，g[i] 表示当前子树得到 i 个棋子时的"最坏情况下最小代价"。min(g[i-j], dfs2(...)+d) 和 max 的组合体现了一种对手博弈（玩家取 best，对手取 worst）的 min-max 结构，类似"游戏树/最坏情形下追赶的距离"
起点 s，枚举从 s 出发的每个方向（每个邻居子树），统计该子树内棋子数 cnt，调 dfs2(s, u, m, cnt) 计算把 m 个棋子全部在该方向"搞定"的最小代价，取所有方向的最小值

dfs2 的 min-max 结构：min(g[i-j], dfs2(v,p,flg,j)+d[u][v]) 里 min 表示"最坏那个子树决定总代价"，max 表示玩家选最优分配——这是典型的取舍博弈。
叶子返回 dfs2(v,u,flg-in,flg-in)+d[u][v]：走到叶子的代价
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 55, inf = 1e9;

int cnt, vis[N];
vector<int> e[N];
void dfs(int u, int fa) {
    cnt += vis[u];
    for (auto v : e[u])
        if (v^fa) dfs(v, u);
}

int f[N][N][N][N], d[N][N];
int dfs2(int u, int v, int flg, int in) {
    auto& ans = f[u][v][flg][in];
    if (~ans) return ans;
    if (!flg) return ans = 0;
    if (e[v].size() == 1)
        return ans = dfs2(v, u, flg-in, flg-in) + d[u][v];
    int g[N]; g[0] = inf;
    for (int i = 1; i <= flg; ++i) g[i] = -inf;
    for (auto p : e[v]) {
        if (p^u) {
            for (int i = in; i; --i)
                for (int j = 1; j <= i; ++j)
                    g[i] = max(g[i], min(g[i-j],
                        dfs2(v, p, flg, j)+d[u][v]));
        }
    }
    return ans = g[in];
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        e[u].push_back(v); e[v].push_back(u);
        d[u][v] = d[v][u] = w;
    }
    int s, m, x[N]; cin >> s >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> x[i]; vis[x[i]]++;
    }
    memset(f, -1, sizeof f);
    int ans = inf;
    for (auto u : e[s]) {
        cnt = 0;
        dfs(u, s);
        ans = min(ans, dfs2(s, u, m, cnt));
    }
    cout << ans << '\n';
    return 0;
}