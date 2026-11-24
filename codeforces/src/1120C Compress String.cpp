//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
后缀自动机节点：ch[26] 转移边、fa 后缀链接、len 该状态代表的最长串长。
N<<1 是因为 SAM 节点数 ≤ 2×长度
新建节点 u，len 为末尾节点 lst 的 len+1。
沿后缀链接补转移，找不到 c 的地方都连向 u。
若有已有转移 q，分两种情况：len 恰好相等则直接建后缀链接；否则克隆节点 x，复制 q 的转移和后缀链接，并重定向相关转移，最后设置 u、q 的 fa。
末尾 lst 更新为 u。
作用：每加入一个字符，SAM 就能在线回答"某个子串是否已作为某个前缀的后缀出现过"

n 串长，a 单字符输入代价，b 复制一段的代价。
dp 初始化为无穷大，dp[0]=0（空串代价 0）。
SAM 初始只有根节点（tot=lst=1）
对每个 i，先把 s[i] 插入 SAM（这样 SAM 始终包含 s[1..i] 的所有子串信息）。
dp[i] 至少可用 dp[i-1]+a（把 s[i] 作为新字符单独输入）。
从 i+1 起，尝试在 SAM 中沿 s[i+1], s[i+2], ... 走转移：
若能走通（t[u].ch[c] 存在），说明 s[i+1..j] 这个子串在 s[1..i] 中已经出现过，于是可以用 dp[i]+b 一次"复制" j−i 个字符 → 更新 dp[j]。
一旦转移断裂（某字符不在 SAM 中）就 break，因为更长的子串也必断裂。
最后输出 dp[n]，即把整个串打完的最小代价
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 5050;

struct SAM { int ch[26], fa, len; } t[N<<1];

int tot, lst;
void insert(int c) {
    int u = ++tot; t[u].len = t[lst].len + 1;
    int p = lst;
    while (p && !t[p].ch[c]) { t[p].ch[c] = u; p = t[p].fa; }
    if (!p) t[u].fa = 1;
    else {
        int q = t[p].ch[c];
        if (t[q].len == t[p].len + 1) t[u].fa = q;
        else {
            int x = ++tot; t[x] = t[q]; t[x].len = t[p].len + 1;
            while (p && t[p].ch[c] == q) { t[p].ch[c] = x; p = t[p].fa; }
            t[u].fa = t[q].fa = x;
        }
    }
    lst = u;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, a, b, dp[N];
char s[N];
int main() {
    fast;
    n = rd(), a = rd(), b = rd(); memset(dp, 0x3f, sizeof dp);
    scanf("%s", s+1); tot = lst = 1; dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        insert(s[i]-'a');
        dp[i] = min(dp[i], dp[i-1]+a);//第 i 个字符单独输入，代价 a
        int u = 1;//从 SAM 根开始
        for (int j = i+1; j <= n; ++j) {
            int c = s[j]-'a';
            if (t[u].ch[c]) {//该字符可沿 SAM 转移 → 子串 s[i+1..j] 出现过
                dp[j] = min(dp[j], dp[i]+b);//从 i 复制到 j，代价 b
                u = t[u].ch[c];//继续沿转移走
            } else break;//发生断裂则停止
        }
    }
    cout << dp[n] << '\n';
    return 0;
}