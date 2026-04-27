//
// Created by Psy.C on 2026/4/27.
//
/**
dp[u][j]：在节点u的子树中，距离u不超过j的节点被染色的方案数
k：题目参数（距离限制）
f[N]：临时数组，用于转移过程
g[N]：邻接表，存储树的边
u：当前节点，fa：父节点
dp[u][0] = 1：距离为0时，只有u节点本身被考虑，方案数为1
dp[u][k+1] = 1：距离超过k时，无约束，方案数为1
遍历u的所有子节点
跳过父节点防止重复访问
递归处理子节点v
清空临时数组f
二重循环枚举u和v的贡献组合
1ll*...%mod：强制转为long long避免溢出
当j+p ≤ 2*k时，更新f[min(p+1, j)]
当j+p > 2*k时，更新f[max(p+1, j)]
将临时结果复制回dp数组
累加根节点距离为0到k的所有方案数
O(n × k²)，其中n为节点数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 107, mod = 1e9+7;

int dp[N][N], k, f[N];
vector<int> g[N];
void dfs(int u, int fa) {
    dp[u][0] = 1; dp[u][k+1] = 1;
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (v == fa) continue;
        dfs(v, u);
        memset(f, 0, sizeof f);
        for (int j = 0; j <= 2*k; ++j)
            for (int p = 0; p <= 2*k; ++p) {
                if (j + p <= 2*k) {
                    f[min(p+1, j)] += 1ll*dp[u][j]*dp[v][p]%mod;
                    f[min(p+1, j)] %= mod;
                } else {
                    f[max(p+1, j)] += 1ll*dp[u][j]*dp[v][p]%mod;
                    f[max(p+1, j)] %= mod;
                }
            }
        for (int j = 0; j <= 2*k; ++j) dp[u][j] = f[j];
    }
}

int n;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        g[x].push_back(y); g[y].push_back(x);
    }
    dfs(1, 1);
    int ans = 0;
    for (int i = 0; i <= k; ++i)
        ans = (ans + dp[1][i]) % mod;
    cout << ans << '\n';
    return 0;
}