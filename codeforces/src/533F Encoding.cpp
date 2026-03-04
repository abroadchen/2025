//
// Created by Psy.C on 2026/3/4.
//
/**
N = 2e5+10: 数组最大容量
M = 30: 26个字母加上额外空间
base = 233: 字符串哈希的基数
n, m: 两个字符串的长度
bin[N]: base的幂次数组（用于哈希计算）
h1, h2: 当前哈希值和目标哈希值
nxt[N][M-3]: nxt[i][j]表示从位置i开始第一个字符'a'+j的位置
h[N][M-3]: 二维哈希数组
b[M]: 映射数组
ans: 匹配数量
s[N]: 存储匹配位置
c1[N], c2[N]: 两个输入字符串

读入n和m
初始化bin[0] = 1
读入两个字符串（从下标1开始）
计算base的幂次数组
计算字符串c2的哈希值h2
初始化边界条件：nxt[n+1][j] = n+1
从后往前遍历，预处理nxt数组
nxt[i][j]: 从位置i开始第一个字符'a'+j的位置
如果当前位置就是目标字符，记录当前位置；否则继承下一位置的结果
计算每个位置每种字符的滚动哈希值
(c1[i]=='a'+j-1): 如果c1[i]是第j个字符则为1，否则为0

遍历所有可能的起始位置（1到n-m+1）
重置h1和映射数组b
对于每种字符j，如果在当前窗口内存在：
计算对应的目标字符p
建立字符间的映射关系
更新当前哈希值h1
如果h1等于目标哈希值h2，记录匹配位置

时间复杂度约为O(n26)，空间复杂度为O(n26)。
 */
#include <bits/stdc++.h>
#define int long long
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

constexpr int N = 2e5+10, M = 30, base = 233;
int n, m, bin[N], h1, h2, nxt[N][M-3], h[N][M-3], b[M], ans, s[N];
char c1[N], c2[N];
signed main() {
    n = read(), m = read(); bin[0] = 1;
    scanf("%s", c1 + 1); scanf("%s", c2 + 1);
    rep(i,n) bin[i] = bin[i-1]*base;
    rep(i,m) h2 = h2*base + c2[i] - 'a' + 1;
    rep(i,26) nxt[n+1][i] = n + 1;
    for (int i = n; i; i--) rep(j,26)
        nxt[i][j] = c1[i] == j+'a'-1 ? i : nxt[i+1][j];
    rep(i,n) rep(j,26) h[i][j] = h[i-1][j]*base + (c1[i]=='a'+j-1);
    rep(i,n-m+1) {
        h1 = 0; memset(b, 0, sizeof b);
        rep(j,26) if (nxt[i][j] <= i+m-1) {
            int p = c2[nxt[i][j]-i+1] - 'a' + 1;
            if (!b[p] && !b[j]) b[p] = j, b[j] = p;
            h1 += b[j]*(h[i+m-1][j] - h[i-1][j]*bin[m]);
        }
        if (h1 == h2) s[++ans] = i;
    }
    printf("%lld\n", ans);
    rep(i,ans) printf("%d ", s[i]);
    return 0;
}