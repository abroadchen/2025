//
// Created by Psy.C on 2025/11/26.
//
/*
 *N=100005（节点数上限）和M=505（距离上限）
 *邻接表表示树结构：g[i]存储与节点i相邻的所有节点
 *dp[u][d]表示以节点u为根的子树中，到u距离为d的节点数
 *
*u: 当前节点
p: 父节点
k: 目标距离
 *节点u到自身的距离为0，所以dp[u][0] = 1
 *遍历u的所有子节点v（跳过父节点p）
 *递归处理子树v
*计算经过节点u的长度为k的路径数：
子树v中到v距离为k-1的节点数
这些节点通过边(u,v)到达u，形成长度为k的路径
*计算跨越两个不同子树的路径数：
dp[v][i]: 子树v中到v距离为i的节点数
dp[u][k-i-1]: 当前u子树中到u距离为k-i-1的节点数
两者组合形成长度为k的路径
*更新u的DP值：
子树v中到v距离为i-1的节点，在u看来距离为i
累加到dp[u][i]中
 *
*k：目标路径长度
i：已知一部分的长度
1：中间连接边的长度
k - i - 1：剩余部分需要的长度
 *
 *O(n × k)：每个节点最多访问k次
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;
constexpr int N = 1e5+5, M = 505;
vector<int> g[N];
int dp[N][M];
ll ans = 0;

void dfs(const int u, const int p, const int k) {
    dp[u][0] = 1;
    for (const auto v : g[u]) {
        if (v == p) continue;
        dfs(v, u, k);
        ans += dp[v][k - 1];
        for (int i = 0; i < k - 1; ++i)
            ans += dp[v][i] * dp[u][k - i - 1];
        for (int i = 1; i < k + 1; ++i)
            dp[u][i] += dp[v][i - 1];
    }
}

int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 0, u, v; i < n - 1; ++i) {
        cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(1, 0, k);
    cout << ans << '\n';
    return 0;
}