//
// Created by Psy.C on 2025/12/9.
//
/*
*m: 网格行数
n: 网格列数
x: 连续相同颜色段的最小长度
y: 连续相同颜色段的最大长度
 *
*外层循环遍历行（i从0到m-1）
内层循环遍历列（j从0到n-1）
读入每个字符ch
如果是'#'，则cnt[j][1]加1（第j列的'#'数量）
否则是'.'，则cnt[j][0]加1（第j列的'.'数量）
 *
*i: 当前列
j: 当前连续段的长度
k: 当前段的颜色（0表示'.', 1表示'#'）
 *
 *遍历每一列（i从0到n-1）
*如果是第一列（i=0）：
对于两种颜色k（0和1）：
dp[0][1][k] = cnt[0][k]（第一列长度为1的段的成本就是该列该颜色的数量）
*遍历可能的连续段长度j（从1到min(i+1, y)）：
连续段长度最多为i+1（因为只有i+1列）
连续段长度最多为y（题目限制）
*如果当前段长度为1（新开始一段）：
遍历前一列所有合法的连续段长度k（从x到y）
dp[i][1][0] = min(dp[i][1][0], dp[i-1][k][1] + cnt[i][0])
当前列段为'.'，前一列段为'#'的成本加上当前列'.'的数量
dp[i][1][1] = min(dp[i][1][1], dp[i-1][k][0] + cnt[i][1])
当前列段为'#'，前一列段为'.'的成本加上当前列'#'的数量
*如果当前段长度大于1（延续当前段）：
dp[i][j][0] = dp[i-1][j-1][0] + cnt[i][0]
延续'.'段的成本
dp[i][j][1] = dp[i-1][j-1][1] + cnt[i][1]
延续'#'段的成本
 *
*时间复杂度：O(n×y²)
空间复杂度：O(n×y)
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1005
#define inf 0x3f3f3f3f
using namespace std;


int main() {
    fast;
    int m, n, x, y; cin >> m >> n >> x >> y;
    int cnt[N][2];//统计每列中'#'和'.'的数量
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            char ch; cin >> ch;
            if (ch == '#') cnt[j][1]++;
            else cnt[j][0]++;
        }
    }
    int dp[N][N][2];
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; ++i) {
        if (i == 0) for (int k = 0; k < 2; ++k) {
            dp[i][1][k] = cnt[i][k];
        }
        for (int j = 1; j <= i + 1 && j <= y; ++j) {
            if (j == 1) for (int k = x; k <= y; ++k) {
                dp[i][j][0] = min(dp[i][j][0], dp[i-1][k][1]+cnt[i][0]);
                dp[i][j][1] = min(dp[i][j][1], dp[i-1][k][0]+cnt[i][1]);
            } else {
                dp[i][j][0] = dp[i-1][j-1][0]+cnt[i][0];
                dp[i][j][1] = dp[i-1][j-1][1]+cnt[i][1];
            }
        }
    }
    int ans = inf;
    for (int i = x; i <= y; ++i) {
        ans = min(ans, dp[n-1][i][0]);
        ans = min(ans, dp[n-1][i][1]);
    }
    cout << ans << '\n';
    return 0;
}