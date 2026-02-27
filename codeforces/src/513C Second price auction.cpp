//
// Created by Psy.C on 2026/2/27.
//
/**
n：区间数量
l[N], r[N]：每个区间的左右端点
m：最大右端点值
dp[N][N]：动态规划数组，dp[i][j]表示前i个区间中有j个区间包含值的概率
s[M]：前缀概率和数组
ans：最终答案

外层循环：对每个可能的值x（1到m）
p = 1.*max(r[i] - max(l[i], x) + 1, 0)/(r[i]-l[i]+1)：
计算第i个区间包含值x的概率
max(l[i], x)是区间与x的交集左端点
r[i] - max(l[i], x) + 1是交集大小
如果x不在区间内，则为0
内层DP：dp[i][j] = dp[i-1][j-1]*p + dp[i-1][j]*(1.-p)
前i个区间中j个包含x的概率 =
前i-1个区间中j-1个包含x × 第i个区间包含x的概率 +
前i-1个区间中j个包含x × 第i个区间不包含x的概率
s[x] += dp[n][i]：计算至少2个区间包含x的概率

期望值的计算公式：E[X] = Σ P(X ≥ i)
s[i]是至少2个区间包含值≥i的概率
s[i] - s[i+1]是恰好值为i的概率
加权求和得到期望值

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
using namespace std;
constexpr int N = 6, M = 1e4+1;
int n, l[N], r[N], m;
ld dp[N][N], s[M], ans;
int main() {
    fast;
    cin >> n; dp[0][0] = 1.;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i];
        m = max(m, r[i]);
    }
    for (int x = 1; x <= m; ++x) {
        for (int i = 1; i <= n; ++i) {
            const ld p = 1.*max(r[i] - max(l[i], x) + 1, 0)/(r[i]-l[i]+1);
            for (int j = 0; j <= i; ++j)
                dp[i][j] = dp[i-1][j-1]*p + dp[i-1][j]*(1.-p);
        }
        for (int i = 2; i <= n; ++i) s[x] += dp[n][i];
    }
    for (int i = 1; i <= m; ++i) ans += (s[i] - s[i+1])*i;
    printf("%.10Lf", ans);
    return 0;
}