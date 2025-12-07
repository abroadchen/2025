//
// Created by Psy.C on 2025/12/6.
//
/*
*N = 405：最大节点数
M = 1e4+5：最大边数
n, m：左右两部分的节点数（二分图）
k：边数
t：每种颜色最多使用的次数限制
u[M], v[M]：存储边的两个端点
deg[N]：每个节点的度数
id[N]：节点的新编号映射
tot：新节点编号计数器
res[M]：存储每条边的颜色结果
vis[M*5][N]：记录节点在某种颜色下的邻接边
 *
*x：当前节点
s：原颜色
t1：新颜色
找到使用颜色s的边e，将其颜色改为t1
如果邻接节点y也有使用颜色t1的边，则递归处理
 *
*当节点度数达到t的倍数时，为其分配新编号
这样做是为了控制每种颜色的使用次数
 *
*找到两个端点的可用颜色t1和t2
如果颜色相同，直接使用该颜色
如果颜色不同，可能需要调整已有边的颜色（通过DFS）
 *
*ans：需要的颜色种类数（度数不是t倍数的节点数）
res[i]：每条边的颜色
 *时间复杂度约为O(k×t)，空间复杂度O(k×t)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 405, M = 1e4+5;
int n, m, k, t, u[M], v[M], deg[N], id[N], tot, res[M];
int vis[M*5][N];

int find(const int x) {//寻找节点x可用的颜色（在1到t范围内第一个未被使用过的颜色）
    for (int i = 1; i <= t; ++i) if (!vis[x][i]) return i;
    return 0;
}

void dfs(const int x, const int s, const int t1) {
    const int e = vis[x][s], y = x == u[e] ? v[e] : u[e];
    vis[x][s] = vis[y][s] = 0;
    if (vis[y][t1]) dfs(y, t1, s);
    vis[x][t1] = vis[y][t1] = e, res[e] = t1;
}

int main() {
    fast;
    cin >> n >> m >> k >> t;
    for (int i = 1; i <= k; ++i) {
        cin >> u[i] >> v[i]; v[i] += n;//将右侧节点编号偏移n，使左右节点编号不冲突
        if (deg[u[i]] % t == 0) id[u[i]] = ++tot;
        if (deg[v[i]] % t == 0) id[v[i]] = ++tot;
        ++deg[u[i]], ++deg[v[i]];
        u[i] = id[u[i]], v[i] = id[v[i]];
        const int t1 = find(u[i]), t2 = find(v[i]);
        if (t1 == t2) vis[u[i]][t1] = vis[v[i]][t1] = i, res[i] = t1;
        else {
            if (vis[u[i]][t2]) dfs(u[i], t2, t1);
            vis[u[i]][t2] = vis[v[i]][t2] = i, res[i] = t2;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n + m; ++i) if (deg[i] % t) ++ans;
    cout << ans << '\n';
    for (int i = 1; i <= k; ++i) cout << res[i] << ' ';
    cout << '\n';
    return 0;
}
