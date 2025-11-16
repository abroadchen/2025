//
// Created by Psy.C on 2025/11/16.
//
/*
*i: 第一种元素的数量
j: 第二种元素的数量
type: 最后一个元素的类型(0表示第一种，1表示第二种)
*n: 第一种元素的数量
m: 第二种元素的数量
k1: 第一种元素连续出现的最大次数
k2: 第二种元素连续出现的最大次数
 *
 *0个第一种元素和0个第二种元素的排列数为1（两种结尾状态）
 *双重循环遍历所有可能的第一种和第二种元素数量组合
*计算以第一种元素结尾的排列数：
枚举连续k个第一种元素(1≤k≤min(k1,i))
这k个元素之前必须是以第二种元素结尾的排列
状态转移：dp[i][j][0] += dp[i-k][j][1]
*计算以第二种元素结尾的排列数：
枚举连续k个第二种元素(1≤k≤min(k2,j))
这k个元素之前必须是以第一种元素结尾的排列
状态转移：dp[i][j][1] += dp[i][j-k][0]
 *
*输出结果：n个第一种元素和m个第二种元素的所有合法排列数
结果等于以第一种元素结尾的排列数加上以第二种元素结尾的排列数
 *
*dp[i][j][0]: 使用i个第一种元素和j个第二种元素，且以第一种元素结尾的合法排列数
dp[i][j][1]: 使用i个第一种元素和j个第二种元素，且以第二种元素结尾的合法排列数
 *
 *
 *O(n × m × (k1 + k2))
 *
 */
#include <cstdio>
#include <cstring>
#define rep(i,n) for(int i=0;i<=(n);++i)
#define mod 100000000
using namespace std;

const int N = 101, M = 2;
int dp[N][N][M];

int main() {
    int n, m, k1, k2;
    while (scanf("%d%d%d%d", &n, &m, &k1, &k2) == 4) {
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = dp[0][0][1] = 1;
        rep(i,n) rep(j,m) {
            for (int k = 1; k <= k1 && k <= i; ++k) {
                dp[i][j][0] += dp[i - k][j][1];
                dp[i][j][0] %= mod;
            }
            for (int k = 1; k <= k2 && k <= j; ++k) {
                dp[i][j][1] += dp[i][j - k][0];
                dp[i][j][1] %= mod;
            }
        }
        printf("%d\n", (dp[n][m][0] + dp[n][m][1]) % mod);
    }
    return 0;
}