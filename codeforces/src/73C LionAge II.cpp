//
// Created by Psy.C on 2025/11/3.
//
/*
*l：允许的最大修改次数
cost[N][N]：二维数组，cost[i][j]表示将字母i改为字母j的代价
dp[N][M][N]：三维DP数组，dp[i][j][k]表示处理前i个字符，第i个字符是j，修改k次时的最大收益
 *
 *读取代价规则的数量q
 *读取换行符，为后续字符输入做准备
 *读取源字符u，目标字符v，以及转换代价c
 *将字符转换为0-25的数字索引，存储转换代价
 *如果不是最后一条规则，读取换行符
 *
*初始化第一个字符的状态：
对于每个可能的字符i(0-25)
如果i与原字符相同，修改次数为0，收益为0
如果i与原字符不同，修改次数为1，收益为0
 *
*状态转移方程：
从前一状态dp[i-1][k][x]转移到当前状态dp[i][j][x+add]
收益为前一状态收益加上从字符k转换到字符j的代价cost[k][j]
取最大值更新当前状态
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 110, M = 26, inf = -0x3f3f3f3f;
char s[N];
int l, cost[N][N], dp[N][M][N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    scanf("%s%d", s, &l);
    int q; scanf("%d", &q);
    memset(cost, 0, sizeof(cost));
    scanf("\n");
    while (q--) {
        char u, v;
        int c;
        scanf("%c %c %d", &u, &v, &c);
        cost[u - 'a'][v - 'a'] = c;
        if (q != 0) scanf("\n");
    }
    int n = strlen(s);
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < M; ++j) {
            for (int k = 0; k <= l; ++k) {
                dp[i][j][k] = inf;
            }
        }
    }
    for (int i = 0; i < M; ++i) dp[1][i][(s[0] - 'a') != i] = 0;
    for (int i = 2; i <= n; ++i) {//从第二个字符开始进行动态规划（i从2到n）
        char c = s[i - 1];//获取当前位置的原始字符（注意索引偏移）
        for (int j = 0; j < M; ++j) {//遍历当前位置可能的目标字符j(0-25)
            int add = (((c - 'a') == j) ? 0 : 1);//计算是否需要修改：如果当前字符与目标字符相同则add=0，否则add=1
            for (int k = 0; k < M; ++k) {//遍历前一位置的所有可能字符k(0-25)
                for (int x = 0; x <= l - add; ++x) {//遍历前一位置的所有可能修改次数x(0到l-add)
                    if (dp[i - 1][k][x] == inf) continue;//如果前一状态不可达，跳过
                    dp[i][j][x + add] = max(dp[i - 1][k][x] + cost[k][j], dp[i][j][x + add]);
                }
            }
        }
    }
    int ans(inf);
    for (int j = 0; j < M; ++j) {//遍历所有可能的最终状态，找到最大的收益值
        for (int k = 0; k <= l; ++k) ans = max(ans, dp[n][j][k]);
    }
    cout << ans << endl;
    return 0;
}