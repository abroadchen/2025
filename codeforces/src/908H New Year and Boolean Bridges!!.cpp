//
// Created by Psy.C on 2026/10/11.
//
/**
快读 rd() 读 n。
并查集初始化 fa[i]=i, sz[i]=1。
A：表示 i、j 同色/等价，合并进并查集。
所以每个连通块 = 一组必须同色（等价）的元素
对每个代表元（根），若块大小 sz>1（即不是孤立单点），给它一个编号 id，tot 计数。
也就是把"大小 ≥ 2 的同色块"挑出来，压缩成 tot 个"待处理集合"。
注意：id 只对大小≥2的块赋值；单点块无 id
对每条 X（i,j 必须不同）：
若 u、v 在同一连通块（由 A 约束它们必须同色），却又有 X 要求不同 → 矛盾，输出 -1。
否则若两端所在的块都 ≥2，则在"块图"上连一条边，用 bitmask e[u] 记录 u 的邻居集合。
这里 e[] 是 tot 维的邻居位掩码
all = 2^tot。

对每个子集 i，取最低位 t（i&-i），对应节点 __builtin_ctz(t)。

递推式：

cnt[i] = cnt[i\t] + cnt[ i\t 去掉 (i & e[节点]) ]
这实际上是计数"子集 i 中有多少种方式选择独立集 / 向下闭包"之类——i & e[...] 把与该节点相邻的节点从剩余子集中剔除。

这很像 "staircase/poset 的闭包计数" 或 "独立集在偏序下的扩展数"。具体到本题，它统计的是从集合 i 出发、不断"加入新块及其必要依赖"的合法过程数
pw[i] 初始为 1，每次外层迭代乘上 cnt[i]。
每轮对每个子集 i：
用 (n - popcount(i)) 的奇偶性决定 +/−（容斥符号）。
累加 sum。
然后 pw[i] *= cnt[i]。
一旦某轮 sum != 0，输出 n-1+k 并结束。
这本质上是在做容斥求和：sum = Σ_i (-1)^(n-|i|) cnt[i]^k，随着 k 增加（相当于把子集幂级数自乘 k 次），逐步逼近期望的计数。当 sum 首次非零时，对应的 k 就是答案所需的最小步数/参数，输出 n-1+k。
cnt[i]^k（通过反复乘）等价于把子集结构"展开 k 层"，是典型的"集合幂级数取幂"来统计某种 k-步可达方案数的技巧。
 */
#include <bits/stdc++.h>
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define For(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 49, M = 1<<23, mod = 1e9+7;

inline int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
inline int ksm(int a, int b) {
    static int ans;
    for (ans=1; b; b>>=1, a=1ll*a*a%mod)
        if (b&1) ans=1ll*ans*a%mod;
    return ans;
}

int fa[N], sz[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
inline void uni(int u, int v) {
    u = find(u); v = find(v);
    if (u != v) fa[u] = v, sz[v] += sz[u];
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int id[N], tot, e[N], cnt[M], all, pw[M];
int main() {
    static char str[N][N];
    static int fu, fv, sum;
    int n = rd();
    rep(i,n) fa[i] = i, sz[i] = 1;
    rep(i,n) {
        scanf("%s", str[i]);
        rep(j,n) if (str[i][j] == 'A') uni(i, j);
    }
    For(i,1,n) if (fa[i] == i && sz[i] > 1) id[i] = tot++;
    rep(u,n) For(v,u+1,n) if (str[u][v] == 'X') {
        if ((fu=find(u)) == (fv=find(v))) { puts("-1"); return 0; }
        if (sz[fu] > 1 && sz[fv] > 1)
            e[id[fu]]|=1<<id[fv], e[id[fv]]|=1<<id[fu];
    }
    cnt[0] = 1, all = 1<<tot;
    For(i,1,all-1) {
        int t = i&-i;
        cnt[i] = add(cnt[t^i], cnt[t^i^(i&e[__builtin_ctz(t)])]);
    }
    rep(i,all) pw[i] = 1;
    for (int k = 0; ; ++k) {
        sum = 0;
        rep(i,all) {
            sum = add(sum, ((n-__builtin_popcount(i))&1)?mod-pw[i]:pw[i]);
            pw[i] = 1ll*pw[i]*cnt[i]%mod;
        }
        if (sum) { printf("%d\n", n-1+k); return 0; }
    }
    return 0;
}