//
// Created by Psy.C on 2026/9/18.
//
/**
node：边节点，存 to（终点）、dis（边权）、nxt（下一条边的下标，链式前向星）。
add(x,y,z)：在 x 的邻接链头部插入一条边 (x→y, 权 z)。
N<<1 是因为无向图每条边存两次
vis[]：防止在树中回走（因为是树，等价于父节点标记）。
对每个未访问邻居 to，递归求 dfs(to) + 边权 dis，取最大值。
返回从 x 出发能走到的最远距离（最深分支距离）。
注意：这里 vis 在当前版本下在整个树上只置位不回溯（vis[x]=1 且没有撤销）。因为输入是树，从某个点出发 DFS 天然不会走"回头路"，所以即便不回溯也不会误判——前提是图确实是树（n-1 条边连通）。若存在环，这个不回溯的写法会漏走某些分支，结果可能不是真最大值
读入 n，读 n-1 条边（n 个节点、n-1 条边 → 一棵树），每条边加双向。
从根节点 0 出发 dfs(0)，输出从 0 出发的最远距离
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3;

struct node { int to, dis, nxt; } a[N<<1];
int tot, head[N+1];
void add(int x, int y, int z) {
    a[++tot].to = y; a[tot].dis = z; a[tot].nxt = head[x]; head[x] = tot;
}

int vis[N+1];
int dfs(int x) {
    int ans = 0;
    vis[x] = 1;
    for (int i = head[x]; i; i = a[i].nxt)
        if (!vis[a[i].to])
            ans = max(ans, a[i].dis+dfs(a[i].to));
    return ans;
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        add(u, v, w); add(v, u, w);
    }
    cout << dfs(0);
    return 0;
}