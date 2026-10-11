//
// Created by Psy.C on 2026/10/11.
//
/**
str：被插入的字符流。
len[u]：回文树节点 u 代表的回文串长度。
fa[u]：fail 指针 —— 指向该回文串的最长真回文后缀对应的节点
回文树插入字符 str[i] 时，需要找到"以 str[i] 结尾的最长回文后缀"。
从当前节点 u 沿 fa（fail）向上跳：每次检查 str[i] 能否在 u 代表回文串的左边再接一个与 str[i] 相同的字符构成新回文，即 str[i-len[u]-1] == str[i]。不满足就跳 fail。
返回能接上的那个节点

pos[i]：插入第 i 个字符后，指向"以 i 结尾的最长回文后缀"的节点（当前回文树的"当前节点"）。
ch[u][v]：转移边，v 是字符
找到能接上的节点 u 和字符编号 v
新回文 = 在 u 的回文串外再包一层 str[i]，所以长度 len[u]+2。
fa[tot] 用 get(fa[u], i) 找它的最长真回文后缀（标准回文树建 fail 的方法）
dt[u] = len[u] - len[fa[u]]：回文串与其 fail 回文后缀的长度差。
sl[u]："series link / 等差数列跳指针"（回文树优化技巧）。当当前节点与其 fail 的 dt 相等时，sl 继承 sl[fa]；否则 sl 就是 fa。这用于在 DP 时沿回文后缀按等差长度跳跃，把 O(回文后缀个数) 的枚举优化到 O(log n)。
sl 和 dt 是近年来回文树优化 DP 的核心（"Palindrome Series" 优化），用于在较短复杂度内枚举所有回文后缀

读入两个等长字符串 s、t（长度 n）。
交错拼接：str[2k-1] = s[k], str[2k] = t[k]，总长 2n。即第奇数位来自 s、偶数位来自 t。
初始化回文树：奇数根 1 长度 -1、偶数根 0 长度 0，fa[1]=0, fa[0]=1。
dp[i] 初始化为无穷大，dp[0]=0（空前缀覆盖 0 段
add(i)：把当前字符插入回文树。

特判：若 i 偶数 且 str[i-1]==str[i]（相邻两位相同），那么 s[k]=t[k] 这两个字符本身构成一个长度为 2 的回文，可以独立切成一段，dp[i]=dp[i-2]（直接接上一前缀），ts[i]=i-2 记录切分点。这里 ts 类似前一题的 fa，记录 DP 转移来源。

回文后缀枚举（用 sl/dt 优化）‍：

u = pos[i] 从当前最长回文后缀开始。
bt[u] = i - len[sl[u]] - dt[u]：计算"以某一回文后缀结尾的这一段的起始位置-1"。len[u] 是回文长度，i - len 就是该回文串起始位置，再取前一个位置即 i - len - 1……这里公式 i - len[sl] - dt 与等差跳跃相关，用来快速取得该等差回文系列里第一个段的起始。
bt 数组可理解为"每个回文后缀对应段的左端点（前一位）"。
当 fa[u] != sl[u] 时，用 bt[fa[u]] 来更新 bt[u]（把更优的起点传递上来，从而得到该等差数列上最优的段起点）。
转移：dp[i] = min(dp[i], dp[bt[u]]+1)，即"前 bt[u] 个字符的答案 + 当前用一段回文覆盖"。ts[i]=bt[u] 记录转移来源。
u = sl[u]：沿 series link 跳到下一个等差回文后缀，枚举所有（有代表性的）回文后缀。
简言之：这是回文串拆分 / 覆盖 DP，在枚举所有回文后缀时用 sl/dt 优化到接近 O(n log n)
若 dp[n] 仍为无穷大 → 无法覆盖，输出 -1。
否则输出 dp[n]（最小段数），并沿 ts 回溯输出每段的区间 ((ts>>1)+1, p>>1)（把交错后的下标还原回 s/t 的 1-based 位置）。
回溯时若 ts[p] < p-2 才输出（排除长度恰为 2 的特判段，那些已在 dp[i-2] 转移里隐式处理，不需要单独输出区间）
 */
#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=j; i<=k; ++i)
using namespace std;

constexpr int N = 1e6+5, inf = 1e9;

char str[N];
int len[N], fa[N];
int get(int u, int i) {
    while (str[i-len[u]-1] != str[i])
        u = fa[u];
    return u;
}
int pos[N], ch[N][26], tot(1), dt[N], sl[N];
void add(int i) {
    int u = get(pos[i-1], i), v = str[i]-'a';
    if (!ch[u][v]) {
        tot++; fa[tot] = ch[get(fa[u], i)][v];
        ch[u][v] = tot;
        len[tot] = len[u] + 2;
        dt[tot] = len[tot] - len[fa[tot]];
        if (dt[tot] == dt[fa[tot]]) sl[tot] = sl[fa[tot]];
        else sl[tot] = fa[tot];
    }
    pos[i] = ch[u][v];
}


template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

char s[N], t[N];
int n, cnt, dp[N], ts[N], bt[N];
int main() {
    scanf("%s%s", s+1, t+1); n = strlen(s+1);
    rep(i,1,n) str[++cnt] = s[i], str[++cnt] = t[i];
    n = cnt; fa[1] = 0, fa[0] = 1, len[1] = -1, pos[0] = 0;
    rep(i,0,n+1) dp[i] = inf; dp[0] = 0;
    rep(i,1,n) {
        add(i);
        int u = pos[i];
        if (!(i&1) && str[i-1] == str[i]) dp[i] = dp[i-2], ts[i] = i-2;
        while (u > 1) {
            bt[u] = i - len[sl[u]] - dt[u];
            if (fa[u] != sl[u]) {
                if (dp[bt[fa[u]]] < dp[bt[u]])
                    bt[u] = bt[fa[u]];
            }
            if (!(i&1) && dp[bt[u]]+1 < dp[i])
                dp[i] = dp[bt[u]]+1, ts[i] = bt[u];
            u = sl[u];
        }
    }
    if (dp[n] == inf) return puts("-1"), 0;
    write(dp[n]), putchar('\n');
    int p = n;
    while (p) {
        if (ts[p] < p-2)
            write((ts[p]>>1)+1), putchar(' '), write(p>>1), putchar('\n');
        p = ts[p];
    }
    return 0;
}