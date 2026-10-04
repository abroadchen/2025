//
// Created by Psy.C on 2026/10/4.
//
/**
把字符串逆序存入 a[i]（a[0] = 最低位，a[n-1] = 最高位）。
各数字和 m。若 m % 15 != 0 则直接 NO（因为 16 进制数 ≡ 各位和 mod 15）。
m /= 15 作为 DFS 的初始"可进位次数"
dfs(d, c)：处理第 d 位，还剩余 c 次"进位"机会。
每位的操作是：从低位借 16 进到高位 1（a[d] -= 16; ++a[d+1]），这会让低位数字小于 0（变"负数"，即借位后的表示）。
分支：要么第 d 位不进位（直接到 d+1），要么进位（消耗一次 c）。
DFS 到最高位 n-1 时，要求最高位 a[n-1] 是合法数字 [0,15]，然后进入子集 DP 验证
sum[i]：集合 i 中所有数字（除了最高位，因为最高位单独作为 sum[0] 基准）的和。
DP 状态 i 是已经用了哪些低位数字（bitmask，范围 0..lim-1，有 n-1 个低位数字）。
转移：如果当前已选集合的数字和 sum[i] 落在 [0,15]，说明它能构成目标数的一位（合法 16 进制位），就尝试把这个"和"放到某个还没用的位 j：dp[i|(1<<j)] = min(..., dp[i] + (sum[i] << (j<<2)))。
sum[i] << (j<<2)：把和值放到第 j 个 16 进制位（左移 4*j 位），拼成最终的 16 进制数值。
最终 ans = min(dp[lim-1])：所有低位都用上、且每位的和在 [0,15]，得到一个可行构造，取数值最小者
从最高位到最低位逐位输出 ans 的 16 进制表示
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;

template<typename T>
bool chkmin(T& a, const T& b) {
    if (a > b) return a = b, 1;
    return 0;
}
constexpr int N = 1<<13;//2^13 = 8192，子集DP表大小
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

int n, a[14], lim;
ll dp[N], sum[N], ans = inf;
void dfs(int d, int c) {
    if (d == n-1) {
        if (a[n-1] < 0 || a[n-1] > 15) return;
        memset(dp, 0x3f, sizeof(dp));
        sum[0] = a[n-1]; dp[0] = 0;
        for (int i = 1; i < lim; ++i)
            sum[i] = sum[i&(i-1)] + a[__builtin_ctz(i)];//子集中的数字和
        for (int i = 0; i < lim; ++i)
            if (sum[i] >= 0 && sum[i] < 16) {
                for (int j = 0; j < n-1; ++j)
                    if (!(i>>j&1))
                        chkmin(dp[i|(1<<j)], dp[i]+(sum[i]<<(j<<2)));
            }
        chkmin(ans, dp[lim-1]);
        return;
    }
    if (c < n-1-d) dfs(d+1, c);
    if (c > 0) {
        a[d] -= 16; ++a[d+1]; dfs(d+1, c-1);
        a[d] += 16; --a[d+1];
    }
}

int num(char c) { return isdigit(c) ? c-'0' : c-'a'+10; }
char chr(int c) { return c < 10 ? c+'0' : c-10+'a'; }

char s[15];
int m;
int main() {
    scanf("%s", s);
    n = strlen(s); lim = 1<<(n-1);
    for (int i = 0; i < n; ++i)
        m += a[i] = num(s[n-1-i]);
    if (m%15) { puts("NO"); return 0; }
    dfs(0, m/=15);
    if (ans == inf) puts("NO");
    else {
        for (int i = n-1; ~i; --i)
            putchar(chr(ans>>(i<<2)&15));//每4位取一个16进制字符
    }
    return 0;
}