//
// Created by Psy.C on 2026/3/10.
//
/**
vis[u] = c: 给节点u染色c
遍历邻接点：
如果邻接点未访问且满足约束条件，继续DFS
如果邻接点已访问，检查是否违反约束条件
t为1表示相同颜色，t为0表示不同颜色

w=1表示两点必须同色，w=0表示两点必须异色
遍历所有连通分量
对每个未访问的节点执行DFS
如果某个连通分量不是有效的二分图，输出0并结束
否则增加连通分量计数

减1是因为第一个连通分量的颜色选择固定
时间复杂度：O(n + m)，每个节点和边最多访问一次
空间复杂度：O(n + m)，存储图的邻接表
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, mod = 1e9+7;

struct node { int to, w; };

int ksm(int a, int b) {
    int ans = 1;
    while (b) {
        if (b&1) ans = 1ll*ans*a%mod;
        a = 1ll*a*a%mod;
        b >>= 1;
    }
    return ans;
}

int vis[N];
vector<node> e[N];
bool dfs(const int u, const int c) {
    vis[u] = c;
    for (auto [to, w] : e[u]) {
        if (int v = to, t = w; vis[v] == -1) {
            if (t && !dfs(v, c)) return false;
            if (!t && !dfs(v, !c)) return false;
        } else {
            if (t && vis[v] != c) return false;
            if (!t && vis[v] == c) return false;
        }
    }
    return true;
}

int n, m;
int main() {
    fast;
    cin >> n >> m;
    memset(vis, -1, sizeof vis);
    for (int i = 1, u, v, w; i <= m; ++i) {
        cin >> u >> v >> w;
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (vis[i] == -1) {
            if (dfs(i, 0)) ans++;
            else return cout << "0", 0;
        }
    }
    cout << ksm(2, ans-1) << '\n';
    return 0;
}