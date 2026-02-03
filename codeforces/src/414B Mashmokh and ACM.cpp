//
// Created by Psy.C on 2026/2/3.
//
/**
* 外层循环：i 从1到K-1，表示当前处理的层数
中层循环：j 从1到n，表示前一层的起始值
内层循环：k 从j开始，以步长j递增到n k是j的倍数
状态转移：dp[i+1][k] += dp[i][j]，将 dp[i][j] 的值加到 dp[i+1][k]
模运算：每次加法后取模防止溢出
 *将最后一层的所有状态值累加到 ans
 *
 *dp[i][j] 表示第i层以j结尾的方案数
 *
 *时间复杂度：O(K×n×log n)，内层循环的k变化是按j的倍数增长的
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2005
#define mod 1000000007
#define rep(i,n) for (i=1; i<=n; ++i)
using namespace std;


int main() {
    fast;
    int n, K, i, j, dp[N][N]={}, ans = 0; cin >> n >> K;
    rep(i,n) dp[1][i] = 1;//第一层DP值全部设为1，表示长度为1的序列的方案数
    rep(i,K-1) rep(j,n) for (int k = j; k <= n; k += j)
        dp[i+1][k] += dp[i][j], dp[i+1][k] %= mod;
    rep(i,n) ans += dp[K][i], ans %= mod;
    cout << ans;
    return 0;
}