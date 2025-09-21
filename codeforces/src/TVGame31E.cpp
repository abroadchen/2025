//
// Created by Psy.C on 2025/9/21.
//

#include <algorithm>
#include <cstdio>
using namespace std;
typedef unsigned long long ull;

char s[40];
ull pw[20], dp[40][20];// pw是10的幂次数组，dp是动态规划表;

int main() {

    int i, j, k, n; scanf("%d%s", &n, s + 1);
    pw[0] = 1;// 预计算10的幂次
    for (i = 1; i <= n; ++i) pw[i] = pw[i - 1] * 10;

    for (i = n * 2; i >= 1; --i) {
        for (j = 0; j <= n && j <= n * 2 - i + 1; ++j) {// j表示高位部分的位数
            k = n * 2 - i + 1 - j; // k表示低位部分的位数
            // 1. 将当前数字分配给高位部分
            if (j) dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + pw[j] * (s[i] - '0'));
            // 2. 将当前数字分配给低位部分
            if (k) dp[i][j] = max(dp[i][j], dp[i + 1][j] + pw[k] * (s[i] - '0'));
        }
    }
    // 重构最优解的分配方案
    for (i = 1, j = n; i <= n * 2; ++i) {
        if (j && dp[i][j] == dp[i + 1][j - 1] + pw[j] * (s[i] - '0')) {
            printf("H");// 分配给高位
            j--;// 高位剩余位数减1
        } else printf("M");
    }
    return 0;
}