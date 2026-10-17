//
// Created by Psy.C on 2026/10/17.
//
/**
N=1e5+5：点数上限；inf=1e18 无穷大。
vis[N]：DFS 访问标记。
g[N]：原图的邻接表（存边）
从某个点出发，沿着 g 的边把所有可达点打上 vis。
这里 dfs(S) 用来找到起点 S 出发能到达的点集（后面只在这些可达点里判断拓扑是否成环）
n：点数。
Deg[N]：G 图上的入度数组。
q：BFS/拓扑用的队列。
G[N]：在可达点集内部重新建的有向图（用于判环）
把所有可达 (vis[i]) 且入度为 0 的点入队。
Kahn 算法拓扑排序：不断弹出队首，把其出边指向的点入度减 1，入度变 0 就入队。
结束后，若仍然存在 vis 且 Deg>0 的点 → 说明可达点集里有环，返回 true。
有环 = 游戏可能无限循环 → 平局（Draw）。这是判断"平局"的关键
经典的 0/1 状态 BFS（双状态最短路）‍，在有向图上。
dis[i][0] / dis[i][1]：到点 i，且当前"轮到谁走"的状态（0 或 1，表示奇偶/当前玩家）的最短步数。
pre[i][0/1]：前驱点，用于最终回溯路径。
转移规则：
从状态 (u,0) 走到 (x,1)：dis[u][0]+1 < dis[x][1] 则更新；
从状态 (u,1) 走到 (x,0)：dis[u][1]+1 < dis[x][0] 则更新。
即状态在 0↔1 之间交替（每走一步，轮到对方，玩家状态翻转）。
这是典型的"两个玩家轮流走、判断哪方能强制把棋子送到终点"的 BFS。dis 两层对应"当前该走的玩家"

读入点数 n、边数 m（其实边数似乎通过 deg 逐点给出）。
对每个点 i：先读入出度 deg[i]，再读入 deg[i] 个出边并压入 g[i]。
读入起点 S，执行上述双状态 BFS。
遍历所有出度为 0（终点/死胡同）‍的点 i。
若 dis[i][1] != inf（即从 S 出发、当前轮到对方走时能到达这个终点，且是奇数步状态 1，说明对方被逼/我方可通过奇数步取胜），则记录 T=i 并 goto end → 直接输出 Win 路径。
这是"找到必胜终点"：当终点在状态 1（我方走完后的偶数步/他人状态）可达时→我方可强制获胜。
注意 deg 在此时还是原始出度（前面只改了 Deg 大写那个用于拓扑）
没找到必胜终点：
dfs(S) 找出从 S 出发可达的所有点（vis）。
只保留两端都可达的边，建新图 G 并统计入度 Deg（在可达子图内）。
topp() 判断可达子图内是否有环：
有环 → 平局 Draw（可以无限循环，谁都无法强制获胜）。
无环 → Lose（可达集是无环 DAG，且没有必胜终点，说明先手必败）
这是获胜时的路径回溯：
now=1 表示从终点 T 往回走时当前状态。
循环：把当前点 T 存入 ans；若 dis[T][now]==0（回到起点状态 0 深度 0）就停止；否则 T = pre[T][now] 跳到前驱，并把 now 取反（^=1，在 0/1 间翻转）。
由于是从终点倒着存，最后 for 从 tot 到 1 倒序输出，得到从 S 到 T 的正向合法路径
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 1e5+5, inf = 1e18;

bool vis[N];
vector<int> g[N];
inline void dfs(int x) {
    vis[x] = true;
    for (auto u : g[x])
        if (!vis[u]) dfs(u);
}

int n, Deg[N];
queue<int> q;
vector<int> G[N];
inline bool topp() {
    for (int i = 1; i <= n; ++i)
        if (vis[i] && Deg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto x : G[u]) {
            --Deg[x];
            if (Deg[x] == 0) q.push(x);
        }
    }
    for (int i = 1; i <= n; ++i)
        if (Deg[i] && vis[i]) return true;
    return false;
}

int S, dis[N][2], pre[N][2];
inline void bfs() {
    q.push(S);
    for (int i = 1; i <= n; ++i) dis[i][0] = dis[i][1] = inf;
    dis[S][0] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto x : g[u]) {
            if (dis[u][0] + 1 < dis[x][1]) {
                q.push(x);
                pre[x][1] = u;
                dis[x][1] = dis[u][0] + 1;
            }
            if (dis[u][1] + 1 < dis[x][0]) {
                q.push(x);
                pre[x][0] = u;
                dis[x][0] = dis[u][1] + 1;
            }
        }
    }
}

int m, deg[N], T, ans[N], tot;
signed main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> deg[i];
        for (int j = 1, u; j <= deg[i]; ++j) {
            cin >> u; g[i].push_back(u);
        }
    }
    cin >> S; bfs();
    for (int i = 1; i <= n; ++i) {
        if (deg[i] == 0) {
            if (dis[i][1] != inf) { T = i; goto end; }
        }
    }
    dfs(S);
    for (int i = 1; i <= n; ++i) {
        for (auto j : g[i]) {
            if (vis[i] && vis[j]) {
                ++Deg[j]; G[i].push_back(j);
            }
        }
    }
    if (topp()) cout << "Draw"; else cout << "Lose";
    return 0;
    end:;
    int now = 1;
    cout << "Win\n";
    while (true) {
        ans[++tot] = T;
        if (dis[T][now] == 0) break;
        T = pre[T][now];
        now ^= 1;
    }
    for (int i = tot; i; --i) cout << ans[i] << ' ';
    return 0;
}