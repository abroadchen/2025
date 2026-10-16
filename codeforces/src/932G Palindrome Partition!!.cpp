//
// Created by Psy.C on 2026/10/16.
//
/**
输入串 t[1..n]，把后半部分 t[(n>>1)+1 .. n] 反转。
然后按奇偶交错的顺序构造新串 s：
奇数下标 i：取交错后的左边部分；
偶数下标 i：取反转后右边对应元素。
tot：节点总数。
lst：上一步插入后的"最后节点"。
nxt[i]：节点 i 的 fail / suffix link（最长真回文后缀）。
len[i]：节点 i 代表的回文串长度。
ch[i][c]：转移边。
sl[i]：series link（等差链跳转）‍，用于 O(log) 内处理"回文后缀按长度等差分组"
标准两个根：长度 0 的偶根、长度 -1 的奇根
标准 PAM 插入新回文节点 + 计算 series link（等差回文后缀压缩，是 O(1) 均摊 DP 的关键）
标准 PAM 插入：从 lst 沿 fail 找到最长可扩展回文，必要时新建节点
f[i]：把 s[1..i] 划分成回文串的方案数 / 状态值。
沿 p = lst, lst = sl[lst], ... 的等差链遍历所有"有区别"的回文后缀。
g[p] 是这个等差串集合的某种前缀和，由 f[pos - len[...]] 累加而来。
只有当 pos 是偶数时才累加到 f[pos]（对应 !(pos&1)），因为这题只统计偶数长度段的贡献
逐字符插入进 PAM，每步更新 DP，最终输出 f[n]

PAM 插入：总 O(n)。
series link DP：每个位置均摊 O(log n)，总 O(n log n)。
空间 O(n)

build 只在"插入字符 s[pos] 时，发现最长回文后缀无法继承、必须新建一个回文节点"时被调用。它做四件事：① 建新节点并定长度；② 找新节点的 fail（suffix link）；③ 计算 series link sl
① 新建节点、确定长度
调用 build 时传入的 p 是"当前最长可扩展回文"（在 ins 中由 lst 沿 fail 找到的那个节点，它的 ch[p][c] 原本为 0）。

新回文串 = c + (p 代表的回文) + c，所以长度 = len[p] + 2。ch[p][c] 记下新节点编号 tot。

这里 len[0]=0（偶根，代表空串）、len[1]=-1（奇根，代表"长度 -1"的虚拟串）。因为当 p 是奇根时，len[1]+2 = 1，正好得到一个长度为 1 的单字符回文。
② 找新节点的 fail（nxt）

新回文串是 c P c（P 是 p 的回文串）。它的最长真回文后缀怎么找？

关键性质：c P c 的真回文后缀必然是 c Q c 的形式，其中 Q 是 P 的最长回文后缀（即 P 的 fail），并且这个后缀还要满足 c Q c 本身是回文、且它的最后一个字符能接上 s[pos]。

特殊情况：p == 1（奇根）
如果 p 是奇根（len=-1），那新回文是单字符 c，长度为 1。单字符回文没有非空的真回文后缀，所以 nxt = 0（指向偶根/长度 0 的空串）
一般情况：沿 fail 找
从原来 p 的 fail nxt[p] 开始，不断沿 fail 跳。
对每个候选回文 P'（长度 len[p]），检查它能否被字符 c 左右包裹成回文：条件即 s[pos-1-len[p]] == s[pos]（当前字符左侧第 len[p]+1 个字符等于当前字符 c）。
找到第一个满足条件的 p 后，ch[p][c] 就是 c P' c 那个回文节点，即新节点的 fail。
这是 PAM 在建节点时的标准 fail 求解：新回文的 fail = 由 P 的最长合法回文后缀再左右各包一个 c 得到的回文
③ 计算 series link sl
series link 的作用：把"所有回文后缀"按长度构成等差的方式压缩成链。sl[v] 定义为"从 v 出发，长度小于等于 len[v]/2 的长度最长的、且与 v 属于同一个等差链的回文后缀的 fail"。

判断依据是长度差是否构成等差：

len[tot] - len[nxt[tot]]：当前回文与其最长回文后缀的长度差 d₁。
len[nxt[tot]] - len[nxt[nxt[tot]]]：fail 与其 fail 的长度差 d₂。
若 d₁ != d₂（或没有 fail），说明当前节点开启一条新的等差链，sl[tot] = nxt[tot]。
若 d₁ == d₂，说明它和 fail 属于同一条等差链，直接继承 sl[tot] = sl[nxt[tot]]。
这样，从 lst 出发沿 sl 跳，每次能跳过一整条"长度等差递减"的回文后缀组，使 DP 从每步 O(回文后缀数) 降到 O(log n)
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 1e6, mod = 1e9+7;
inline int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }

char s[N+10];
int f[N+1];
namespace pam {
    const int T = N+2;
    int tot, lst, nxt[T], len[T], ch[T][26], sl[T], g[T];
    void init() { s[0] = '#'; tot = 1, lst = 0, nxt[0] = nxt[1] = 1, len[0] = 0, len[1] = -1; }
    void build(int pos, int p, int c) {
        ch[p][c] = ++tot; len[tot] = len[p] + 2;//新回文 = c + 原回文 + c
        if (p == 1) nxt[tot] = 0;
        else {
            for (p = nxt[p]; s[pos-1-len[p]] != s[pos]; p = nxt[p]) {}
            nxt[tot] = ch[p][c];//找 fail
        }
        if (nxt[tot] == 0 || len[tot] - len[nxt[tot]] != len[nxt[tot]] - len[nxt[nxt[tot]]])
            sl[tot] = nxt[tot];
        else sl[tot] = sl[nxt[tot]];
    }
    void ins(int pos) {
        int p = lst, c = s[pos] - 'a';
        for (; s[pos-1-len[p]] != s[pos]; p = nxt[p]) {}
        if (!ch[p][c]) build(pos, p, c);
        lst = ch[p][c];
    }
    void get(int pos) {
        for (int p = lst; p; p = sl[p]) {
            g[p] = f[pos-len[sl[p]]-(len[p]-len[nxt[p]])];
            if (sl[p]^nxt[p]) g[p] = add(g[p], g[nxt[p]]);
            if (!(pos&1)) f[pos] = add(f[pos], g[p]);
        }
    }
}
using namespace pam;

char t[N+10];
int main() {
    scanf("%s", t+1); int n = strlen(t+1);
    reverse(t+(n>>1)+1, t+n+1);
    for (int i = 1; i <= n; ++i) {
        if (i&1) s[i] = t[(i+1)>>1];
        else s[i] = t[(n>>1)+(i>>1)];
    }
    init(); f[0] = 1;
    for (int i = 1; i <= n; ++i) { ins(i); get(i); }
    printf("%d\n", f[n]);
    return 0;
}