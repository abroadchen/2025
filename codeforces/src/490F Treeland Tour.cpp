//
// Created by Psy.C on 2026/2/18.
//
/**
a[N]: 存储每个节点的权值
dp[N]: 动态规划数组，表示以每个节点为起点的最长递增路径长度

寻找从节点u出发，在不经过fa的前提下，所有满足a[x] < val的节点x中dp[x]的最大值
如果当前节点u的值小于目标值val，则返回dp[u]，否则返回0

后序遍历：先处理子节点，再处理当前节点
dp[u] = dfs(u, fa, a[u]) + 1: 计算以u为终点的最长递增路径长度
更新全局最优解ans

遍历所有子节点，尝试以不同路径通过当前节点
临时保存并恢复dp值，避免影响后续计算
计算跨越当前节点的最长路径
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 6e3+1;
vector<int> e[N];
void add(const int u, const int v) {
    e[u].push_back(v); e[v].push_back(u);
}

int a[N], dp[N];
int dfs(const int u, const int fa, const int& val) {
    int ret = a[u] < val ? dp[u] : 0;
    for (const int v : e[u]) if (v != fa)
        ret = max(ret, dfs(v, u, val));
    return ret;
}

int ans = 0;
void dfs2(const int u, const int fa) {
    for (const int v : e[u]) if (v != fa) dfs2(v, u);
    dp[u] = 0;
    dp[u] = dfs(u, fa, a[u]) + 1;
    ans = max(ans, dp[u]);
}

void dfs3(const int u, const int fa) {
    for (const int v : e[u]) if (v != fa) {
        const int t1 = dp[u];
        dp[u] = 0;
        dp[u] = dfs(u, v, a[u]) + 1;
        const int t2 = dp[v];
        dp[v] = 0;
        dp[v] = dfs(v, 0, a[v]) + 1;
        ans = max(ans, dp[v]);
        dfs3(v, u);
        dp[u] = t1;
        dp[v] = t2;
    }
}

inline int read() {
    int x = 0; char c = getchar(); bool f = 0;
    while (c < '0' || c > '9') c == '-' ? f = 1, c = getchar() : c = getchar();
    while (c >= '0' && c <= '9') x = (x<<3)+(x<<1)+(c&15), c = getchar();
    return f ? -x : x;
}

int n;
int main() {
    fast;
    n = read();
    for (int i = 1; i <= n; ++i) a[i] = read();
    for (int i = 0; i < n-1; ++i) add(read(), read());
    dfs2(1, 0); dfs3(1, 0);//第一次计算以各节点为端点的路径，第二次计算经过各节点的路径
    cout << ans << '\n';
    return 0;
}