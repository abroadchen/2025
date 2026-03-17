//
// Created by Psy.C on 2026/3/16.
//
/**
n:节点数，m:选择的节点数
判断x的二进制表示中是否有恰好m个1
遍历每一位 如果该位为1，计数加1
k:边数，a[]:节点权值，val[][]:边权，dp[][]:动态规划数组
u, v 边
初始化单个节点的状态
dp[mask][i]  // mask:已访问的节点集合，i:最后停在的节点


时间复杂度：O(n² × 2ⁿ)
空间复杂度：O(n × 2ⁿ)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 20;

ll n, m;
bool ok(ll x) {
    int res = 0;
    for (ll i = 1; i <= 1<<n; i <<= 1)
        if (i&x) res++;
    if (res == m) return true;
    return false;
}

ll k, a[N], val[N][N], dp[1<<18][N];
int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (ll i = 1, u, v; i <= k; ++i) cin >> u >> v >> val[u][v];
    memset(dp, -1, sizeof dp);
    for (int i = 1; i <= n; ++i) dp[(1<<(i-1))][i] = a[i];
    for (int x = 0; x <= (1<<n)-1; ++x)
        for (int i = 1; i <= n; ++i) {//遍历当前最后一个节点
            if (dp[x][i] == -1) continue;
            for (int j = 1; j <= n; ++j)//尝试添加下一个节点
                if (i != j && (x&1<<(j-1)) == 0)//j不在当前集合中
                    dp[x|1<<(j-1)][j] = max(dp[x][i] + a[j] + val[i][j],
                        dp[x|1<<(j-1)][j]);
        }
    ll mx = 0;
    for (int x = 0; x <= (1<<n)-1; ++x) if (ok(x))
        for (int i = 1; i <= n; ++i)
            mx = max(mx, dp[x][i]);
    cout << mx << '\n';
    return 0;
}