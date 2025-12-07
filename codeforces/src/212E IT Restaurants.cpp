//
// Created by Psy.C on 2025/12/6.
//
/*
*n：树的节点数
sz[N]：子树大小数组
a[N]：存储结果数组
tot：结果计数器
g[N]：邻接表表示树
dp[N]：动态规划数组
ok[N]：标记数组，记录哪些值是可能的
 *
*计算以节点u为根的子树大小：
sz[u] = 1：初始化当前节点
递归计算所有子节点的子树大小
累加到当前节点的子树大小中
 *
*对于节点u的每个子节点v
从大到小更新DP数组
dp[j] |= dp[j - sz[v]]：如果可以选出大小为j-sz[v]的节点集合，
那么也可以选出大小为j的集合
 *
 *O(n² × 背包大小) = O(n³)
 */
#include <iostream>
#include <cstring>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 5005
using namespace std;

int n, sz[N], a[N], tot;
vector<int> g[N];
bool dp[N], ok[N];

void dfs(const int u, const int fa) {
    sz[u] = 1;
    for (int i = 0, len = static_cast<int>(g[u].size()); i < len; ++i) {
        const int v = g[u][i];
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

void f(const int u) {
    for (const int v : g[u]) {
        for (int j = n - 1; j >= sz[v]; --j)
            dp[j] |= dp[j - sz[v]];
    }
}

int main() {
    fast;
    cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        memset(sz, 0, sizeof(sz));
        memset(dp, 0, sizeof(dp)); dp[0] = true;
        dfs(i, 0), f(i);
        for (int j = 1; j <= n - 2; ++j) if (dp[j]) ok[j] = true;
    }
    for (int i = 1; i <= n - 2; ++i) if (ok[i]) a[++tot] = i;
    cout << tot << '\n';
    for (int i = 1; i <= tot; ++i)
        cout << a[i] << ' ' << n - 1 - a[i] << '\n';
    return 0;
}