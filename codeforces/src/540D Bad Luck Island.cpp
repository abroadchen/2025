//
// Created by Psy.C on 2026/3/6.
//
/**
r, s, p: 三种生物的初始数量（Rocks, Scissors, Papers）
dp[N][N][N]: 三维动态规划数组，dp[i][j][k]表示状态(i,j,k)的概率

逆向DP过程：
从大到小遍历状态空间
sum = i*j + i*k + k*j: 所有可能的对决组合数
转移概率：
i*k: Rock vs Paper的组合数，Rock获胜，Paper减少 → dp[i-1][j][k]
i*j: Rock vs Scissors的组合数，Scissors获胜，Rock减少 → dp[i][j-1][k]
j*k: Scissors vs Paper的组合数，Paper获胜，Scissors减少 → dp[i][j][k-1]
每种对决的概率 = 对决数/总对决数
a1: Rocks获胜的概率（只剩下Rocks和Scissors，最终只剩Rocks）
a2: Scissors获胜的概率（只剩下Scissors和Papers，最终只剩Scissors）
a3: Papers获胜的概率（只剩下Papers和Rocks，最终只剩Papers）
时间复杂度：O(rsp)，空间复杂度O(rsp)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;
int r, s, p;
double dp[N][N][N];
int main() {
    fast;
    cin >> r >> s >> p;
    memset(dp, 0, sizeof dp); dp[r][s][p] = 1.;
    for (int i = r; i >= 1; --i)
        for (int j = s; j >= 1; --j)
            for (int k = p; k >= 1; --k) {
                const int sum = i*j + i*k + k*j;
                dp[i-1][j][k] += dp[i][j][k] * (i*k*1./sum);
                dp[i][j-1][k] += dp[i][j][k] * (i*j*1./sum);
                dp[i][j][k-1] += dp[i][j][k] * (j*k*1./sum);
            }
    double a1 = 0, a2 = 0, a3 = 0;
    for (int i = 1; i <= N-5; ++i)
        for (int j = 0; j <= N-5; ++j) {
            a1 += dp[i][j][0]; a2 += dp[0][i][j]; a3 += dp[j][0][i];
        }
    printf("%.10f %.10f %.10f\n", a1, a2, a3);
    return 0;
}