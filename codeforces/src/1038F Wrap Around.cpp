//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
读入长度 n 和模式串 s（下标从 1 开始）。
m 是模式串长度。
ch[i-1][s[i]-'0'] = i：给每个字符建立前缀节点的转移边。这里 ch 就是 AC 自动机的转移表（trie + 跳转）‍，ch[p][c] 表示状态 p 遇到字符 c 后转移到哪个节点。
初始：ch[i-1][s[i]-'0'] = i 构造了沿模式串的主链跳转
这是标准 AC 自动机的构建：
若节点 i 有子节点 ch[i][j]，则其 fail 指向 fail[i] 对应字符 j 的转移；
若不存在该子节点，就把 ch[i][j] 直接指向 ch[fail[i]][j]（补全转移，形成确定性自动机）。
完成后，ch[p][c] 表示从状态 p 读入字符 c 后到达的新状态（含 fail 跳转）
先假设所有 2^n 个 01 串都合法，ans = 1<<n
外层循环 i 遍历起始状态 0..m-1（枚举"匹配起点"）。
对每个起点 i 计数，然后从 ans 中减去——这是一种容斥/去重：防止同一个非法串被多个起点重复计数。
f[j][k][l]：长度为 j、当前 AC 状态为 k 和 l 的 01 串数量。
两个状态 k, l 的意义：这里实际上维护了**"两条平行自动机路径"——通常这种写法用来表达"串的某个后缀能匹配模式串的哪个前缀**（k）以及某个特定对齐限制（l）"。
每读入一个新字符 c（0 或 1），两个状态分别转移到 a=ch[k][c], b=ch[l][c]。
关键跳过条件：若 a == m || b == m，说明某个状态已经完整匹配到了模式串末尾（长为 m 的后缀等于 s），即出现了需要的非法形态，于是这个串不参与合法计数，continue 跳过
对所有终点状态的 f[n][i][j] 从 ans 中减去，即排除掉会匹配上模式串的串。
*/
#include <bits/stdc++.h>
#define rep(i,j,k) for (int i=j; i<=k; ++i)
#define ll long long
using namespace std;

constexpr int N = 44;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, ch[N][2], fail[N];
char s[N];
ll ans, f[N][N][N];
int main() {
    n = rd(); scanf("%s", s+1); m = strlen(s+1);
    rep(i,1,m) ch[i-1][s[i]-'0'] = i;
    rep(i,1,m) rep(j,0,1) {
        if (ch[i][j]) fail[ch[i][j]] = ch[fail[i]][j];
        else ch[i][j] = ch[fail[i]][j];
    }
    ans = 1ll<<n;
    rep(i,0,m-1) {
        memset(f,0,sizeof(f)); f[0][0][i] = 1;
        rep(j,0,n-1) rep(k,0,m-1) rep(l,0,m-1) rep(c,0,1) {
            int a = ch[k][c], b = ch[l][c];
            if (a == m || b == m) continue;
            f[j+1][a][b] += f[j][k][l];
        }
        rep(j,0,m-1) ans -= f[n][i][j];
    }
    printf("%lld\n", ans);
    return 0;
}