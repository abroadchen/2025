//
// Created by Psy.C on 2026/3/23.
//
/**
h[N][M]：用于存储字符串哈希值的二维数组
P = 113：哈希的基数
mod = 1e9+7：模数
M = 13：倍增层数（因为2^13 > 5000）

判断从位置x开始长度为len的子串是否小于从位置y开始长度为len的子串
如果x<1，返回true（边界情况）
使用倍增思想逐步比较，如果哈希值相同则跳过，否则比较首字符

预计算哈希基数的幂次
将字符串前面加空格，使索引从1开始
初始化单字符哈希值
构建倍增哈希数组，h[i][j]表示从位置i开始长度为2^j的子串的哈希值

dp[i][j]：在前i个字符中，最后一个分割段长度不超过j的方案数
如果起始字符是'0'，跳过（不允许前导零）
使用ok函数比较相邻两段的大小关系
根据比较结果选择不同的转移方程
如果当前段小于前一段：dp[i][j] += dp[i-j][j]
如果当前段大于等于前一段：dp[i][j] += dp[i-j][j-1]

时间复杂度：
预处理哈希：O(n log n)
DP计算：O(n³)
总体：O(n³)
空间复杂度：
O(n²)，主要用于存储DP数组和哈希数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 5005, M = 13, mod = 1e9+7, P = 113;

int h[N][M];
bool ok(int x, int y, int len) {
    if (x < 1) return 1;
    for (int j = 12; j >= 0; --j) {
        if (1<<j > len) continue;
        if (h[x][j] == h[y][j])
            len -= 1<<j, x += 1<<j, y += 1<<j;
    }
    return len && h[x][0] < h[y][0];
}

int p[M], n, dp[N][N];
string s;
signed main() {
    fast;
    p[0] = P;
    for (int i = 1; i < M; ++i) p[i] = p[i-1]*p[i-1]%mod;
    cin >> n >> s; s = " " + s;
    for (int i = 1; i <= n; ++i) h[i][0] = s[i];
    for (int j = 1; j < M; ++j)
        for (int i = 1; i+(1<<j)-1 <= n; ++i)
            h[i][j] = (h[i][j-1]*p[j-1]%mod + h[i+(1<<(j-1))][j-1])%mod;
    for (int i = 1; i <= n; ++i) dp[i][i] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            if (s[i-j+1] == '0') continue;
            if (ok(i-2*j+1, i-j+1, j))
                dp[i][j] = (dp[i][j] + dp[i-j][j])%mod;
            else dp[i][j] = (dp[i][j] + dp[i-j][j-1])%mod;
        }
        for (int j = 1; j <= n; ++j)
            dp[i][j] = (dp[i][j] + dp[i][j-1])%mod;
    }
    cout << dp[n][n];
    return 0;
}