//
// Created by Psy.C on 2026/2/2.
//
/**
 * n（元素数量），k（位数参数）
 *
*对于每个位置 i 和状态 j：

分支1：当 val[i] ≠ 4 时
状态转移：y = min(1<<k, j + 2)
更新操作：dp[i+1][y] += dp[i][j]
含义：执行某种操作，状态增加2（不超过上限）
分支2：当 val[i] ≠ 2 时
情况1：如果 j == 1<<k（达到上限），y = j（保持不变）
情况2：如果 j & 2（j的第2位为1），y = 4（重置为4）
情况3：否则，y = min(j+4, 1<<k)（增加4，不超过上限）
更新操作：dp[i+1][y] += dp[i][j]
 *
 *输出：位置 n、状态 2^k 的方案数
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2010
#define mod 1000000007
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    int val[N], dp[N][(1<<11)|1];
    for (int i = 0; i < n; ++i) cin >> val[i]; dp[0][0] = 1;//初始状态有1种方案
    for (int i = 0; i < n; ++i) for (int j = 0; j <= 1<<k; ++j) {
        const int x = i + 1;
        int y;
        if (val[i] != 4) {
            y = min(1<<k, j + 2);
            dp[x][y] = (dp[i][j] + dp[x][y]) % mod;
        }
        if (val[i] != 2) {
            if (j == 1<<k) y = j;
            else if (j&2) y = 4;
            else y = min(j+4, 1<<k);
            dp[x][y] = (dp[i][j] + dp[x][y]) % mod;
        }
    }
    cout << dp[n][1<<k];
    return 0;
}