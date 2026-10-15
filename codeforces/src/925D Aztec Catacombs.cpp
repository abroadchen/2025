//
// Created by Psy.C on 2026/10/15.
//
/**
n：节点数。
p[]：BFS 时记录的前驱（用来回溯打印路径）。
dfs(x)：递归打印从 x 走向 n 的路径（沿前驱数组 p）
无向图建邻接表 g。
从 n 出发做 BFS，d[t] 存 t 到 n 的最短距离（步数），p[t] 记前驱。
最终 d[1] 就是 1 → n 的最短路长度
情况 A：最短路 ≤ 4 步
若 d[1] ≤ 4（最短路径 ≤ 4 条边，即点数 ≤ 5），直接输出边数 t-1 并打印路径，结束。
这里的 p 变量（初值 -1）其实未被后续使用，是冗余声明
情况 B：找长度为 4（5 个点 4 条边）的路径
目标是找路径 1 - x - y - 1 - n（长度 4，5 个点）。
先标记 1 的所有邻居进 vis。
遍历 1 的每个邻居 x，看它的邻居 y：若 y 不是 1 的邻居（!vis[y]，保证 y 不在第一层）且 y≠1，则构成 1-x-y-1-n 合法简单路径，输出长度 4 并打印这条路径。
关键点：y 必须是"非 1 的邻居"，这样才能让 y-1 这条边不会把路径变成自环/重复节点，且保证路径简单无重复
情况 C：找长度为 5（6 个点 5 条边）的路径
目标是找路径 1 - x - y - z - x - n（长度 5，6 个点）。

外层遍历 1 的每个邻居 x：

先把 x 的所有邻居 y 打上标记 vis[y]=x（表示"y 与 x 相邻"）。
再对每个 y，遍历 y 的邻居 z：若 z 不与 x 相邻（vis[z]!=x）且 z≠1、z≠x，则构成 1 - x - y - z - x - n。
关键是 z-x 这条边：z 必须不是 x 的邻居……等等，路径里 z 后面要接 x（...z-x-n），所以需要 z 与 x 相连。
这里其实有个细节需要核对——代码判断 vis[z] != x 即"z 不在 x 的邻居集"，但路径中 z 之后要连 x。这意味着：此处的约束可能依赖 x 与 z 的边，或依赖题目里对路径类型的特殊定义。该分支的图论正确性需结合原题题意确认。

找到就输出长度 5 与对应路径
若三种情况（最短路 ≤ 4、长度 4、长度 5）都失败，输出 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 3e5+5, inf = 1e9;

int n, p[N];
void dfs(int x) {
    cout << x << ' ';
    if (x != n) dfs(p[x]);
}

int m, u, v, d[N], vis[N];
vector<int> g[N];
queue<int> q;
int main() {
    fast;
    cin >> n >> m;
    while (m--) {
        cin >> u >> v;
        g[u].emplace_back(v); g[v].emplace_back(u);
    }
    d[n] = 1; q.push(n);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int t : g[x])
            if (!d[t]) d[t] = d[x] + 1, p[t] = x, q.push(t);
    }
    int t = inf;
    if (d[1] != 0) t = d[1];
    if (t <= 4) { cout << t-1 << '\n'; dfs(1); return 0; }
    for (int x : g[1]) vis[x] = 1;
    for (int x : g[1]) for (int y : g[x]) if (y != 1 && !vis[y]) {
        cout << 4 << '\n';
        cout << 1 << ' ' << x << ' ' << y << ' ' << 1 << ' ' << n << '\n';
        return 0;
    }
    for (int x : g[1]) {
        for (int y : g[x]) vis[y] = x;
        for (int y : g[x]) if (y != 1)
            for (int z : g[y]) if (vis[z] != x && z != 1 && z != x) {
                cout << 5 << '\n';
                cout << 1 << ' ' << x << ' ' << y << ' ' << z << ' ' << x << ' ' << n << '\n';
                return 0;
            }
    }
    cout << "-1\n";
    return 0;
}