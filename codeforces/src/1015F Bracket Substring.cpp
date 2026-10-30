//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
s：模式串（从 s[1] 起有效）。
nxt：KMP 的失配数组。
f[k][0/1]：自动机转移表——当前已匹配模式串前缀长度 k，再读入字符 '('（0）或 ')'（1）后，匹配长度跳到多少
① 构造 nxt（失配数组）
标准 KMP 失配指针构造：nxt[i] = 前缀“s[1..i-1]”的最长真前后缀匹配长度。

我的口算核对一下：j 初始 0，i=1，因 j=0 跳过内层 while，执行 nxt[2]=1，i 变 2… 这是教科书式写法。

② 构建转移表 f（关键）
理解：当前已匹配了模式串前 i 个字符，尝试读入新字符 c。

理想情况：s[i+1]==c，则新长度为 i+1（设 p=i+1 作为初始猜测）。
若 s[i+1]!=c，就不断用 KMP 失配 nxt[p] 回退，直到找到某个位置 p 满足 s[p]==c，此时新匹配长度 = p。
若回退到 0 仍不匹配，p=0 表示匹配长度归 0。
这样 f[i][0] 就是“读到 ( 后的新匹配长度”，f[i][1] 同理为 )。
f[len][0]=f[len][1]=len：已经完整匹配了模式串（长度 len），状态锁死在 len（表示已含模式串，之后不再变——用于最终统计“正好含模式串”的方案数）
状态定义 dp[i][j][k]：

i：已经填充的括号个数（位置 0..n）。
j：当前未匹配的 ( 数，即当前括号深度。
k：当前在模式串 s 的 KMP 自动机匹配长度（0..len）。
初始化 dp[0][0][0]=1。

转移，对每个状态尝试放 ( 或 )
放 (：深度 j→j+1，自动机 k→f[k][0]。
放 )：深度 j→j-1（仅当 j>0，保证括号合法闭合），自动机 k→f[k][1]。
所有取模 %mod。

答案：dp[n][0][len]

n = 2*n_orig（原始 n 翻倍为总括号对数×2，即总字符数）。
j=0：最终深度归零 → 合法完整括号序列。
k=len：且 KMP 匹配长度恰好 = len，即包含了模式串 s。
所以这个 dp 统计的是「长度为 2n、合法、且包含模式串 s 作为子串」的括号序列数，答案输出 dp[n][0][len]
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=0; i<n; ++i)
#define ll long long
using namespace std;

constexpr int N = 210, mod = 1e9+7;

char s[N];
int nxt[N], f[N][2];
void kmp() {
    int len = strlen(s+1);
    int i = 1, j = 0; nxt[1] = 0;
    while (i <= len) {
        while (j && s[i] != s[j]) j = nxt[j];
        nxt[++i] = ++j;
    }
    rep(i,len) {
        int p = i+1, q = i+1;
        while (p && s[p] != '(') p = nxt[p];
        f[i][0] = p;
        while (q && s[q] != ')') q = nxt[q];
        f[i][1] = q;
    }
    f[len][0] = f[len][1] = len;
}

int n, i, j, k;
ll dp[N][N][N];
int main() {
    fast;
    scanf("%d%s",&n, s+1); kmp(); n <<= 1; dp[0][0][0] = 1;
    int len = strlen(s+1);
    rep(i,n) rep(j,n+1) rep(k,len+1) {
        if (j+1 <= n) dp[i+1][j+1][f[k][0]] = (dp[i+1][j+1][f[k][0]]+dp[i][j][k])%mod;
        if (j) dp[i+1][j-1][f[k][1]] = (dp[i+1][j-1][f[k][1]]+dp[i][j][k])%mod;
    }
    cout << dp[n][0][len] << '\n';
    return 0;
}