//
// Created by Psy.C on 2026/10/13.
//
/**
欧拉线性筛（每个合数只被其最小质因子筛一次）。同时求出莫比乌斯函数：

μ(1)=1；
质数 p → μ(p)=-1；
当 i*pri[j] 中 i%pri[j]!=0（不含平方因子）时 μ 取反；
否则说明出现了平方因子，break 退出（其 μ 保持默认 0
预处理 p[i]=i^n mod mod，即每个 i 的 n 次幂 — 这对应后面狄利克雷式累加的基础值
这是一个倍数枚举（调和级数复杂度 O(k log k)）‍的累加：对每个 i，向所有倍数 j 累加 μ[i]·(p[j/i] - p[j/i-1])。

这里的 p[j/i] - p[j/i-1] 捕捉的是某函数在相邻下标上的差分，配合 μ[i] 做前缀和相关求和，正是莫比乌斯反演/狄利克雷卷积中常见的技巧——用 μ 作子集反演，把"互质/最大公约数"型计数化简。(x%mod+mod)%mod 用于保证取模非负
对 i 从 1 到 k：先把 d[i] 累进前缀 num，再把 num 与 i 做按位异或后累加进 ans，最后输出 ans（全程 mod 1e9+7）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 2e6+6, M = 1e6+6, mod = 1e9+7;

int mu[N], pri[M], cnt;
bitset<N> v;
inline void sieve(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!v[i]) pri[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= n&&1ll*i*pri[j] <= n; ++j) {
            v[i*pri[j]] = 1;
            if (i%pri[j]) mu[i*pri[j]] = -mu[i];
            else break;
        }
    }
}

inline int ksm(int x, int y) {
    int res = 1, p = x;
    while (y) {
        if (y&1) res=1ll*res*p%mod;
        p=1ll*p*p%mod;
        y>>=1;
    }
    return res;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int p[N], d[N], ans, num;
int main() {
    fast;
    int n = rd(), k = rd(); sieve(k);
    rep(i,1,k) p[i] = ksm(i, n);
    rep(i,1,k) for (int j = i; j <= k; j += i)
        d[j] = (d[j]+1ll*mu[i]*(p[j/i]-p[j/i-1])%mod+mod)%mod;
    rep(i,1,k) num = (num+d[i])%mod, ans = (ans+(num^i))%mod;
    cout << ans << '\n';
    return 0;
}