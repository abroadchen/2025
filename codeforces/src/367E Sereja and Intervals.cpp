//
// Created by Psy.C on 2026/1/21.
//
/**
 * n（选择数量）、m（总数）、x（特殊位置）
 *
 *如果n > m，无法选择，直接输出0
*dp[i][j][p]：考虑前i个元素，选择了j个，奇偶性为p的方案数
初始化dp[0][0][0]=1：什么都不选的方案数为1
*k：当前考虑的元素（1到m）
i：当前考虑选择的元素数量
j：实际选择的元素数量
p = k&1：k的奇偶性（0或1）
*当k=x时（特殊位置）
dp[i][j][p] = 0：初始化为0
if (i > j)：不选择第k个元素
if (i&&j)：选择第k个元素
*dp[i][j][p] = dp[i][j][p^1]：继承上一状态
if (i > j)：不选择当前元素
if (i&&j)：选择当前元素
if (j)：其他转移（可能涉及排列）
 *将结果乘以n!
 *
 *O(m × n²)：三重循环嵌套
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 330
#define mod 1000000007
using namespace std;


int main() {
    fast;
    int n, m, x; cin >> n >> m >> x;
    if (n > m) return cout << "0\n", 0;
    int dp[N][N][2]={}; dp[0][0][0]=1;
    //位置
    for (int k = 1; k <= m; ++k) for (int i = 0; i <= min(n, m); ++i) {//左括号
        for (int j = 0; j <= i; ++j) {//右括号
            const int p = k&1;
            if (k == x) {
                dp[i][j][p] = 0;
                if (i > j) (dp[i][j][p] += dp[i-1][j][p^1]) %= mod;//左
                if (i&&j) (dp[i][j][p] += dp[i-1][j-1][p^1]) %= mod;//左+右
            } else {
                dp[i][j][p] = dp[i][j][p^1];
                if (i > j) (dp[i][j][p] += dp[i-1][j][p^1]) %= mod;
                if (i&&j) (dp[i][j][p] += dp[i-1][j-1][p^1]) %= mod;
                if (j) (dp[i][j][p] += dp[i][j-1][p^1]) %= mod;//右
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        dp[n][n][m&1] = static_cast<int>(1ll * dp[n][n][m&1] * i % mod);
    cout << dp[n][n][m&1] << '\n';
    return 0;
}