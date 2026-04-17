//
// Created by Psy.C on 2026/4/16.
//
/**
f[N]：记忆化数组，存储从每个节点到其子树的最大深度
l[N]：存储给每个节点带来最大深度的孩子节点
g[N]：存储从每个节点通过不同分支获得的第二最大深度
G[N]：邻接表表示的树
rt：当前正在处理的根节点/节点
fa：父节点，避免回到父节点
如果已经计算过(f[rt] != -1)，返回缓存的结果
如果是叶子节点(G[rt].empty())，返回0
找到给孩子最大深度的那个孩子节点(m)
在l[rt]中存储达到这个最大值的孩子节点
找到第二高的路径长度，但不经过与最大值相同的那个孩子
g[rt]存储第二最大深度
返回从此节点出发的最大深度

用-1初始化记忆化数组
处理所有连通分量（以防输入的是森林）
对于每个节点，计算f[i] + g[i]，这表示通过该节点的最长路径
输出找到的最大路径长度（树的直径）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

int f[N], l[N], g[N];
vector<int> G[N];
int dfs(int rt, int fa) {
    if (f[rt] != -1) return f[rt];
    if (G[rt].empty()) return f[rt] = 0;
    int ans = rt, m = 0, mm = 0;
    for (int i = 0; i < G[rt].size(); ++i) {
        int u = G[rt][i];
        if (u == fa) continue;
        if (dfs(u, rt) + 1 > m) {
            m = f[u] + 1;
            ans = u;
        }
    }
    l[rt] = ans;
    for (int i = 0; i < G[rt].size(); ++i) {
        int u = G[rt][i];
        if (f[u] + 1 > mm && u != l[rt]) mm = f[u] + 1;
    }
    g[rt] = mm;
    return f[rt] = m;
}

int n, m, u, v;
int main() {
    fast;
    cin >> n >> m;
    while (m--) {
        cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }
    memset(f, -1, sizeof(f));
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (f[i] == -1) dfs(i, -1);
    for (int i = 1; i <= n; ++i) ans = max(ans, f[i]+g[i]);
    cout << ans << '\n';
    return 0;
}