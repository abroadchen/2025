//
// Created by Psy.C on 2026/9/2.
//
/**
输入一个整数 m 和一个长度为 m 的字符串 t（下标从1开始）。
去掉相邻重复字符：把所有相邻且相同的连续字符压缩成一个。例如 "aabbbc" → "abc"。结果存到 s[1..n]。
N = 5003，M = 26（26个字母）
f[j]：当前已处理到 s 的某前缀时，长度为 j 的本质上不同子序列的数量。
dp[x][j]：以字母 x 结尾的长度为 j 的子序列数。
d[x][j]：dp[x] 的前缀和，d[x][j] = dp[x][1] + ... + dp[x][j]。
ds[j]：f 的前缀和，ds[j] = f[1] + ... + f[j]。
对字符串 s 的每个字符 x = s[i] - 'a'

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5003, mod = 1000000007, M = 26;

int m, n, sum, f[N], dp[M][N], ds[N], d[M][N];
char t[N], s[N];
int main() {
    fast;
    scanf("%d%s", &m, t + 1);
    for (int i = 1; i <= m; ++i)
        if (t[i] != t[i-1]) s[++n] = t[i];
    for (int i = 1; i <= n; ++i) {
        int x = s[i] - 'a';
        for (int j = 1; j <= m; ++j) {
            //保存旧 f[j] 先移除旧以x结尾的长度j子序列
            sum = f[j], f[j] = (f[j]-dp[x][j])%mod;
            //更新：新以x结尾的长度j子序列
            dp[x][j] = (ds[j-1]-d[x][j-1]+1)%mod;
            d[x][j] = (dp[x][j]+d[x][j-1])%mod;//更新前缀和
            f[j] = (f[j]+dp[x][j])%mod;//再加回来
            ds[j] = (ds[j-1]+f[j])%mod;//更新f前缀和
        }
    }
    cout << (f[m]+mod)%mod;
    return 0;
}