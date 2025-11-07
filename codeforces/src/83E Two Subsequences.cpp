//
// Created by Psy.C on 2025/11/7.
//
/*
*定义函数w，计算两个n位二进制数x和y的最大重叠长度：
从n到1枚举重叠位数i
(1<<i) - 1 创建i位全1的掩码
x & ((1<<i) - 1) 获取x的后i位
y >> (n - i) 获取y的前i位
如果相等，说明可以重叠n-i位，返回n-i
如果都没有重叠，返回n（完全不重叠）
 *
 *n（字符串数量）和m（字符串长度）
 *a存储二进制字符串的整数表示
 *跳过非'0'和'1'的字符，找到第一个有效字符
*a[i]存储二进制数的十进制表示
每读一位就乘以2加上当前位的值
 *如果只有一个字符串，直接输出其长度并结束
 *
 *dp[i][j]表示以i位二进制数j结尾的最小额外代价
*t是第i-1个字符串和第i个字符串的重叠长度
sum累计总长度（初始为第一个字符串长度）
*枚举所有可能的后缀长度j
a[i] >> (m-j) 获取第i个字符串的前j位
dp[j][a[i] >> (m-j)] 是以前j位结尾的最小代价
m - j - t 是新增的字符数
找到最小值minn
 *
*枚举所有可能的后缀长度j
a[i-1] & ((1<<j) - 1) 获取第i-1个字符串的后j位
更新以这j位结尾的最小代价
 *
*枚举所有可能的结尾状态
sum是基础长度，dp[i][j]是额外代价
找到最小的总长度
 *
 */
#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 2e5, inf = 1e9;

int w(int n, int x, int y) {
    for (int i = n; i >= 1; --i) {
        if ((x & ((1<<i) - 1)) == (y >> (n - i)))
            return n - i;
    }
    return n;
}

int main() {
    int n, m; scanf("%d",&n);
    static int a[N];
    for (int i = 0; i < n; ++i) {
        char c;
        while (c = getchar(), c != '0' && c != '1');
        m = a[i] = 0;
        while (c == '0' || c == '1') {
            m++;
            a[i] = a[i] * 2 + (c == '1');
            c = getchar();
        }
    }
    if (n == 1) { printf("%d\n", m); return 0; }
    static int dp[21][1048576];
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < 1<<i; ++j) dp[i][j] = m;
    }
    int sum(m);
    for (int i = 1; i < n; ++i) {
        int t = w(m, a[i - 1], a[i]); sum += t;
        int minn = inf;
        for (int j = 0; j <= m; ++j) {
            minn = min(minn, dp[j][a[i] >> (m-j)] + m - j - t);
        }
        for (int j = 0; j <= m; ++j) {
            int x = a[i - 1] & ((1<<j) - 1);
            dp[j][x] = min(dp[j][x], minn);
        }
    }
    int ans(inf);
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < 1<<i; ++j)
            ans = min(ans, sum + dp[i][j]);
    }
    printf("%d\n", ans);
    return 0;
}