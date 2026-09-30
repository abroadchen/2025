//
// Created by Psy.C on 2026/9/30.
//
/**
dp[i][j]：处理完前 i 件商品后，当前还剩 j 个"优惠单位"（0-M，M=30）时的最小累计花费
M=30：优惠额度的上界。
dp[0][0]=0（未显式设置，初始全 0？实际只对 i>0 的 j 置 inf，dp[0][0] 默认 0），dp[0][i>0]=inf 表示"没买东西就不可能有余额"
转移1（用优惠抵扣）‍：买前有 k 个优惠，买后剩 j 个（k>j），即花掉了 (k-j) 个优惠，每个优惠抵 100 元，所以实际支付 a[i] - (k-j)*100。k 从 min(M, j+a[i]/100) 往下枚举。

转移2（全价购买攒优惠）‍：不抵扣，全额付 a[i]，但攒下 a[i]/1000 个优惠 → 需要买前至少 j-a[i]/1000 个（j >= a[i]/1000），转移来源 dp[i-1][j-a[i]/1000]。

即：每消费 1000 攒 1 优惠点；每 1 优惠点可抵 100 元。这就是转移里的 a[i]/1000（攒）与 *100（抵）的来源
买完 n 件后，无论最后剩多少优惠都合法，取所有可能余额的最小花费
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+10, M = 30, inf = 1e9;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[N], i, j, k, dp[N][M+1], ans(inf);
int main() {
    fast;
    int n = rd();
    for (i = 1; i <= n; ++i) a[i] = rd();
    for (i = 1; i <= M; ++i) dp[0][i] = inf;
    for (i = 1; i <= n; ++i)
        for (j = 0; j <= M; ++j) {
            dp[i][j] = inf;
            for (k = min(M, j+a[i]/100); k > j; --k)
                dp[i][j] = min(dp[i][j], dp[i-1][k]+a[i]-(k-j)*100);
            if (j >= a[i]/1000)
                dp[i][j] = min(dp[i][j], dp[i-1][j-a[i]/1000]+a[i]);
        }
    for (i = 0; i <= M; ++i) ans = min(ans, dp[n][i]);
    cout << ans << '\n';
    return 0;
}
