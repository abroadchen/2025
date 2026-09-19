//
// Created by Psy.C on 2026/9/19.
//
/**
N = 5005：点数上限（约 5000）。
mod = 1e9+7：模数，用于组合数取模（质数）。
M = 1e7+5：字符总长度上限。
K = 5e6+2：每个 01 串指针缓冲的一半，用于位压缩存储。
ksm(x, q) 计算 x^q mod mod。
默认 q = mod-2，结合费马小定理（mod 是质数），x^(mod-2) 就是 x 的模逆元。
循环：每次
q
q 右移一位、
x
x 自乘平方；当前位是 1 就乘进 r（标准快速幂）
用链式前向星存边。
add(x,y)：在 x 的链表头插入一条指向 y 的边（头插法），nxt 指向原 head
fc[i] = i!，fi[i] = (i!)^{-1}。
先正着算阶乘；再算 fi[x] = (x!)^{-1}，然后倒着推出所有 fi[i-1] = fi[i] * i（因为
(
i
−
1
)
!
−
1
=
i
!
−
1
⋅
i
(i−1)!
−1
 =i!
−1
 ⋅i
组合数
(
n
m
)
(
m
n
​
 )，非法时返回 0
最大公约数，后面用于求多个周期的 gcd。

dfn/low：时间戳和回溯值；dt：时间计数。
st：栈；tp：栈顶；clt：强连通分量个数。
cl[x]：点 x 属于哪个分量。
cg[c]：分量 c 的"周期 gcd"（见下）。
ln[x]：点 x 的 01 串长度。
vs[x]：是否在栈中
初始化时间戳、入栈。
遍历邻接边，树边更新 low，回边（在栈中）也更新 low。
当 low[x]==dfn[x]，说明 x 是分量的根，弹栈到 x，组成一个 SCC。
额外：每个分量内累加 cg[clt] = gcd(所有该分量点的 ln 长度)，即"该分量内所有 01 串长度的最大公约数"

读入 n（点数）、n1、n2（两个计数参数，见计数部分）
g[1] 指向字符缓冲 bfc，f[1] 指向 bfc+K（把缓冲分成两半，一半存 g，一半存 f 数组的位串）。
init(N-5) 预处理好组合数
读入一个
n
×
n
n×n 的 01 邻接矩阵，ch[j]=='1' 表示 i→j 有边，建到邻接表里。
（所以 n 既是点数又是矩阵维度。
对每个点读入一个长度 ln[i] 的 01 串，存到 g[i]。
g[i+1] = g[i] + ln[i] + 1：把字符缓冲按顺序分给每个点的串（第 i+1 个串跟在第 i 个串后面）。
g[i][j] ^= 48：把 ASCII '0'/'1' 转成 0/1（'0'^48=0，'1'^48=1）。
mn[i] 累加 1 的个数 = 该点 01 串里 1 的个数（popcount
对整个图跑一遍 Tarjan，得到 SCC 划分
为每个 SCC（从 2 到 clt）分配一段位存储空间，长度约 cg[i-1]（上一个分量的周期长度）。
即：每个分量用一个长度 = 该分量所有串长度 gcd（=周期）的 01 数组 f[分量] 来表示该分量的"模式"
把每个点 i 的 01 串，按位置 mod 周期 归入其分量 cl[i] 的周期数组。
用 |=：只要该分量里任意一个点在这一位置（模周期）是 1，那这个位置就记为 1。
这一步的意义：同一强连通分量内的信息按周期合并（周期 = 分量内所有长度 gcd）
从最后一个分量向前合并（分量编号按 Tarjan 弹出顺序编号，1 是最后一个弹出的根分量）。
对相邻分量 i 和 i-1：取两个周期 gcd t，把分量 i 的位压到分量 i-1（同样按 mod t 或合并）。
同时统计 cnt[i] = 分量 i 中为 1 的位置数（该分量周期数组里 1 的个数）
统计根分量 1 中 1 的个数
每个点 i 的 mx[i] = cnt[其分量] × ln[i] / cg[其分量]。
意义：用分量合并后的"密度"（每周期里 1 的比例 cnt/cg）外推到该点整个长度 ln[i]，得到该点 01 串理论上"能凑出的最大 1 的个数"
对于每个点 i 作为"基准"：

先遍历其余所有点 j，依据 mn[j]（j 的实际 1 数）和 mx[i]（i 的理论最大 1 数）分类：
c1：满足 mn[j] > mx[i] 的点数——即 j 的实际 1 数必然超过 i 能凑出的最大值，这类点"稳压 i"。
c2：满足 mx[j] > mx[i] 或（相等且 j < i，用编号平局）的点数——这类点"在最大值意义上不小于 i"。
if (0 > n1-1-c1) continue;：剩下可选名额的合法性检查，快速跳过不可能的情形。
内层枚举 j（从 n2-c1-1 到 n2、c2、n1-c1-1 的上限），累加 C(c2,j) × C(c1, n2-j-1)：
从 c2 类里选 j 个、从 c1 类里选 n2-j-1 个的组合计数，模 mod 累加。
输出 res。
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 5e3+5, mod = 1e9+7, M = 1e7+5, K = 5e6+2;

inline int ksm(int x, int q=mod-2) {
    int r = 1;
    for (; q; q>>=1, x=1ll*x*x%mod)
        if (q&1) r=1ll*r*x%mod;
    return r;
}

struct node { int to, nxt; } e[N*N];
int tot, head[N];
inline void add(int x, int y) {
    e[++tot] = {.to = y, .nxt = head[x]}, head[x] = tot;
}

int fc[N], fi[N];
inline void init(int x) {
    fc[0] = fi[0] = 1;
    for (int i = 1; i <= x; ++i) fc[i] = 1ll*fc[i-1]*i%mod;
    fi[x] = ksm(fc[x]);
    for (int i = x; i; --i) fi[i-1] = 1ll*fi[i]*i%mod;
}

inline int C(int n, int m) {
    return n < m || n < 0 || m < 0 ? 0 : 1ll*fc[n]*fi[m]%mod*fi[n-m]%mod;
}
inline int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }

int dfn[N], low[N], dt, st[N], tp, clt, cl[N], cg[N], ln[N];
char vs[N];
inline void tarjan(int x) {
    dfn[x] = low[x] = ++dt, st[++tp] = x, vs[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt) {
        if (!dfn[e[i].to]) tarjan(e[i].to), low[x] = min(low[e[i].to], low[x]);
        else if (vs[e[i].to]) low[x] = min(low[x], dfn[e[i].to]);
    }
    if (low[x] == dfn[x]) {
        int y = ++clt;
        do {
            y = st[tp--], vs[y] = 0, cl[y] = clt, cg[clt] = gcd(cg[clt], ln[y]);
        } while (y^x);
    }
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, n1, n2, mn[N], cnt[N], mx[N], res(0);
char *g[N], bfc[M], *f[N], ch[N];
int main() {
    rd(n), rd(n1), rd(n2);
    g[1] = bfc, f[1] = bfc + K, init(N-5);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", ch + 1);
        for (int j = 1; j <= n; ++j)
            if (ch[j] == '1') add(i, j);
    }
    for (int i = 1; i <= n; ++i) {
        rd(ln[i]), scanf("%s", g[i]), g[i+1] = g[i] + ln[i] + 1;
        for (int j = 0; j < ln[i]; ++j)
            g[i][j] ^= 48, mn[i] += g[i][j];
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i);
    for (int i = 2; i <= clt; ++i) f[i] = f[i-1] + cg[i-1] + 3;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < ln[i]; ++j)
            f[cl[i]][j%cg[cl[i]]] |= g[i][j];
    for (int i = clt; i > 1; --i) {
        int t = gcd(cg[i], cg[i-1]);
        for (int j = 0; j < cg[i]; ++j)
            f[i-1][j%t] |= f[i][j], cnt[i] += f[i][j];
    }
    for (int i = 0; i < cg[1]; ++i) cnt[1] += f[1][i];
    for (int i = 1; i <= n; ++i) mx[i] = 1ll*cnt[cl[i]]*ln[i]/cg[cl[i]];
    for (int i = 1; i <= n; ++i) {
        int c1 = 0, c2 = 0;
        for (int j = 1; j <= n; ++j)
            if (i^j) {
                if (mn[j] > mx[i]) ++c1;
                else if (mx[j] > mx[i] || (mx[j] == mx[i] && j < i)) ++c2;
            }
        if (0 > n1-1-c1) continue;
        for (int j = n2-c1-1; j <= n2 && j <= c2 && j <= n1-c1-1; ++j)
            (res += 1ll*C(c2, j)*C(c1, n2-j-1)%mod) %= mod;
    }
    return printf("%d\n", res), 0;
}