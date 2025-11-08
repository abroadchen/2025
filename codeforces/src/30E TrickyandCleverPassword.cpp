//
// Created by Psy.C on 2025/9/21.
//

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 101000;
char s[N];
int n, r[N], g[N], K, f[N], w[N], ans, p;

int main() {
    scanf("%s", s + 1); n = strlen(s + 1);
    // 使用Manacher算法计算每个位置的回文半径
    for (int i = 1, j = 0, k; i <= n; i += k, j = max(1, j - k)) {
        while (i > j && i + j <= n && s[i - j] == s[i + j]) ++j;// 扩展回文串，找到以i为中心的最长回文串半径
        r[i] = j;// r[i]表示以i为中心的回文串半径
        for (k = 1; k < r[i] && r[i] - k != r[i - k]; ++k)// 利用已计算的信息优化后续计算
            r[i + k] = min(r[i - k], r[i] - k);
    }
    g[n + 1] = K = n + 2;
    for (int i = n; i; --i) {// 从右到左计算每个位置的失配函数值
        while (K <= n + 1 && s[K - 1] != s[i]) K = g[K];
        g[i] = --K;
    }
    K = n + 1;
    for (int i = 1; i < n + 1; ++i) {// 从左到右计算每个位置的前缀函数值
        while (K <= n + 1 && s[K - 1] != s[i]) K = g[K];
        f[i] = --K;
    }
    for (int i = 1; i < n + 1; ++i) {
        f[i] = n + 1 - f[i];// 转换为前缀长度
        if (f[i] < f[i - 1]) f[i] = f[i - 1], w[i] = w[i - 1];// 维护单调性并计算w数组
        else w[i] = i - f[i] + 1;// 记录最优位置
    }

    ans = 0;
    for (int i = 1; i < n + 1; ++i) {// 枚举所有可能的回文中心，寻找最优解
        K = 2 * r[i] - 1 + min(n - i - r[i] + 1, f[i - r[i]]) * 2;
        if (K > ans) ans = K, p = i;
    }

    K = min(n - p - r[p] + 1, f[p - r[p]]);
    if (K)
        printf("3\n%d %d\n%d %d\n%d %d", w[p - r[p]], K,// 第一个子串：位置和长度
            p + 1 - r[p], 2 * r[p] - 1,// 第二个子串：位置和长度
            n - K + 1, K);// 第三个子串：位置和长度
    else
        printf("1\n%d %d\n", p + 1 - r[p], 2 * r[p] - 1);// 只有一个回文子串
    return 0;
}