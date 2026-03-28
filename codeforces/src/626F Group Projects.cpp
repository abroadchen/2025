//
// Created by Psy.C on 2026/3/28.
//
/**
dp[t][j][v] 表示：
t: 当前考虑的阶段（滚动数组索引）
j: 当前有j个活跃元素
v: 当前总成本为v的方案数

初始状态：0个活跃元素，成本为0的方案数为1
对每个元素进行处理，并清空当前DP状态
情况1: 不选择当前元素，成本增加j*d（因为已有j个元素受到影响）
情况2: 选择当前元素并立即删除，成本增加j*d，方案数乘以j（可选择删除任意一个活跃元素）
情况3: 如果有活跃元素(j>0)，选择当前元素与之前的活跃元素配对，活跃数变为j-1
情况4: 选择当前元素并保持活跃，活跃数变为j+1
所有成本状态下，活跃元素数为0的方案总数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 205, M = 1e3+5, mod = 1e9+7;
int n, k, a[N];
ll dp[2][N][M];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1); a[0] = a[1];
    int u = 0; dp[u][0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        u^=1;
        memset(dp[u], 0, sizeof dp[u]);
        for (int j = 0; j <= n; ++j) {
            int d = a[i] - a[i-1];
            for (int v = 0; v <= k; ++v) {
                if (!dp[u^1][j][v]) continue;//之前状态不存在
                if (v+j*d > k) break;//新成本超出限制
                dp[u][j][v+j*d] = (dp[u][j][v+j*d]+dp[u^1][j][v])%mod;
                dp[u][j][v+j*d] = (dp[u][j][v+j*d]+dp[u^1][j][v]*j%mod)%mod;
                if (j > 0) dp[u][j-1][v+j*d] = (dp[u][j-1][v+j*d]+dp[u^1][j][v]*j%mod)%mod;
                dp[u][j+1][v+j*d] = (dp[u][j+1][v+j*d]+dp[u^1][j][v])%mod;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i <= k; ++i) ans = (ans + dp[u][0][i])%mod;
    cout << ans << '\n';
    return 0;
}