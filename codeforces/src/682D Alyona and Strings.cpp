//
// Created by Psy.C on 2026/4/15.
//
/**
i, j: 字符串s和t的当前位置
x: 到目前为止使用的组数(最多k个)
state: 当前位置是否处于一个组的末尾(0=未结束，1=已结束)

dp[i][j][x][0]: 当字符s[i]和t[j]匹配且属于现有组时的最大长度
dp[i][j][x][1]: 考虑最多x个组时的最大长度，可能结束一个组

当字符匹配时 (s[i] == t[j]):
更新dp[i][j][x][0]，要么延续之前的组，要么开始新组
dp[i-1][j-1][x][0]: 继续同一组
dp[i-1][j-1][x-1][1]: 开始新组(需要减少一个组计数)
对于所有位置:
更新dp[i][j][x][1]，考虑到达此状态的所有可能方式：
从字符串s跳过字符: dp[i-1][j][x][1]
从字符串t跳过字符: dp[i][j-1][x][1]
使用匹配结果: dp[i][j][x][0]
保持之前组状态: dp[i-1][j-1][x][1]
返回使用完整的字符串和所有k个组可实现的最大长度
 */
#include <bits/stdc++.h>
using namespace std;

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

constexpr int N = 1e3+5;
int n, m, k, dp[N][N][11][2];
char s[N], t[N];
int main() {
    rd(n); rd(m); rd(k);
    scanf("%s", s + 1); scanf("%s", t + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            if (s[i] == t[j]) {
                for (int x = 1; x <= k; ++x)
                    dp[i][j][x][0] = max(dp[i-1][j-1][x][0], dp[i-1][j-1][x-1][1]) +1;
            }
            for (int x = 1; x <= k; ++x)
                dp[i][j][x][1] = max(max(dp[i-1][j][x][1], dp[i][j-1][x][1]),
                    max(dp[i][j][x][0], dp[i-1][j-1][x][1]));
        }
    printf("%d\n", dp[n][m][k][1]);
    return 0;
}