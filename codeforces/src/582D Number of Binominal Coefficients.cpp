//
// Created by Psy.C on 2026/3/17.
//
/**
al：最小位数要求
len：字符串长度
a[N+5]：存储转换后的数字（大数处理）
x[N+5]：存储每一位的结果
m：转换后数组的长度
dp[2][N+5][2][2]：动态规划数组
s[N+5]：输入的字符串

读入n（可能是进制）、al（最小位数）和字符串s
计算字符串长度
如果最小位数要求超过数组容量，直接返回0
将字符串转换为数字数组并倒序存储（低位在前）
将十进制数转换为n进制数
通过模拟除法，每次计算a/n的商和余数
余数存储到x数组，商更新到a数组
逐步缩小a的长度直到为0

cur和pre用于滚动数组优化
初始化DP状态，dp[1][0][0][1] = 1
从高位向低位处理
使用异或交换技巧翻转cur和pre
计算转移过程中需要的各种组合数
c1 0到n-1所有数字的和
c2 0到x[i]所有数字的和
c3 1到n-1所有数字的和
c4 x[i]+1到n-1所有数字的和
c5 1到x[i]-1所有数字的和
c6 x[i]到n-1所有数字的和

第一维：处理到第几位
第二维：已经选择的位数
第三维：是否已经开始放置数字
第四维：是否小于上界

dp[cur][j][0][0] = f0c1 + f1c2 + f2c3 + f3c4
当前状态：未开始放置数字，未受上界限制
从前一状态转移：
f0*c1：从[未开始，未受限]转移，放置0到n-1的数
f1*c2：从[未开始，受限]转移，放置0到x[i]的数
f2*c3：从[已开始，未受限]转移，放置1到n-1的数
f3*c4：从[已开始，受限]转移，放置x[i]+1到n-1的数
dp[cur][j][0][1] = (x[i]+1)*f1 + (n-x[i]-1)*f3
当前状态：未开始放置数字，仍受限
x[i]+1个选择使状态继续受限（0到x[i]）
n-x[i]-1个选择使状态变为不受限（x[i]+1到n-1）
dp[cur][j+1][1][0] = f0c3 + f1c5 + f2c1 + f3c6
当前状态：已开始放置数字，未受上界限制
位数+1，因为现在开始放置数字了
f0*c3：从[未开始，未受限]，放置1到n-1
f1*c5：从[未开始，受限]，放置1到x[i]-1
f2*c1：从[已开始，未受限]，放置0到n-1
f3*c6：从[已开始，受限]，放置x[i]到n-1
dp[cur][j+1][1][1] = x[i]*f1 + (n-x[i])*f3
当前状态：已开始放置数字，仍受限
位数+1
x[i]*f1：从[未开始，受限]，放置1到x[i]
(n-x[i])*f3：从[已开始，受限]，放置x[i]到n-1


 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 4e3, mod = 1e9+7;

int n, al, len, a[N+5], x[N+5], m, dp[2][N+5][2][2];
char s[N+5];
int main() {
    scanf("%d%d%s", &n, &al, s+1); len = strlen(s+1);
    if (al > N) return puts("0")&0;
    for (int i = 1; i <= len; ++i) a[len-i+1] = s[i] - '0';
    while (len) {
        ll cur = 0;
        for (int i = len; i; --i) {
            cur = cur*10 + a[i];
            a[i] = cur/n;
            cur %= n;
        }
        x[++m] = cur;
        if (!a[len]) len--;
    }
    int cur = 1, pre = 0; dp[cur][0][0][1] = 1;
    for (int i = m; i; --i) {
        cur ^= pre ^= cur ^= pre;
        memset(dp[cur], 0, sizeof(dp[cur]));
        int c1 = 1ll*(n+1)*n/2%mod, c2 = 1ll*(x[i]+1)*x[i]/2%mod,
        c3 = 1ll*(n-1)*n/2%mod, c4 = 1ll*x[i]*(n*2-x[i]-1)/2%mod,
        c5 = 1ll*(x[i]-1)*x[i]/2%mod, c6 = 1ll*x[i]*(n*2-x[i]+1)/2%mod;
        for (int j = 0; j <= m-i+1; ++j) {
            int f0 = dp[pre][j][0][0], f1 = dp[pre][j][0][1],
            f2 = dp[pre][j][1][0], f3 = dp[pre][j][1][1];
            dp[cur][j][0][0] = (1ll*f0*c1 + 1ll*f1*c2 + 1ll*f2*c3 + 1ll*f3*c4) % mod;
            dp[cur][j][0][1] = (1ll*(x[i]+1)*f1 + 1ll*(n-x[i]-1)*f3) % mod;
            dp[cur][j+1][1][0] = (1ll*f0*c3 + 1ll*f1*c5 + 1ll*f2*c1 + 1ll*f3*c6) % mod;
            dp[cur][j+1][1][1] = (1ll*x[i]*f1 + 1ll*(n-x[i])*f3) % mod;
        }
    }
    int ans = 0;
    for (int i = al; i <= m; ++i) {
        ans = (ans + dp[cur][i][0][0]) % mod;
        ans = (ans + dp[cur][i][0][1]) % mod;
    }
    printf("%d\n", ans);
    return 0;
}