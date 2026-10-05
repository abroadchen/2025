//
// Created by Psy.C on 2026/10/5.
//
/**
模数取 998244353（NTT 友好质数）
inv[i]、Aa/Ab、Cb/Cc 用于预计算下面会反复用到的量
线性递推求 1..c 的模逆元
Aa[i] = a·(a-1)…(a-i+1) = P(a,i)，即 a 的下降阶乘（排列数)
Ab[i] = P(b,i)，同理 b 的下降阶乘
Cb[i] = P(b,i)/i! = C(b,i)，即 b 中选 i 个的组合数（用逆元消去 i!）
Cc[i] = C(c,i)，c 中选 i 个的组合数
读入 a、b、c 后通过三次交换保证 a ≤ b ≤ c
三组累加各为 Σ P(小,i)·C(大,i)，然后各自 +1，最后三者相乘作为答案。
数学含义（基于结构的读解）‍：Σ P(u,i)·C(v,i) 表示“从 v 个元素里选出 i 个、并与 u 个元素做 i 个位置一一对应（排列）”的配对方案数。这里三组求和分别统计 u、v 之间不完全匹配（对集）‍的数目，+1 表示“空匹配（一个都不配）”，最后三者相乘。这种形态通常对应于某个三集合两两配对方案数的组合计数目标。
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 5007, mod = 998244353;

ll inv[N], c, x, a, b;
ll Aa[N], Ab[N], Cb[N], Cc[N];
void init() {
    inv[1] = 1;
    for (int i = 2; i <= c; ++i)
        inv[i] = (mod-mod/i)*inv[mod%i]%mod;
    x = 1;
    for (ll i = 1; i <= a; ++i) {
        x *= a - i + 1; x %= mod;
        Aa[i] = x;
    }
    x = 1;
    for (ll i = 1; i <= b; ++i) {
        x *= b - i + 1; x %= mod;
        Ab[i] = x;
    }
    x = 1;
    for (ll i = 1; i <= b; ++i) {
        x *= b - i + 1; x %= mod;
        x *= inv[i]; x %= mod;
        Cb[i] = x;
    }
    x = 1;
    for (ll i = 1; i <= c; ++i) {
        x *= c - i + 1; x %= mod;
        x *= inv[i]; x %= mod;
        Cc[i] = x;
    }
}
template <typename T>
T read() {
    T f = 0, ch = 0; T x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

ll ab, ac, bc, ans;
int main() {
    a = read<ll>(), b = read<ll>(), c = read<ll>();
    if (b < a) swap(a, b);
    if (c < a) swap(a, c);
    if (c < b) swap(b, c);
    init();
    for (ll i = 1; i <= a; ++i) ab = (ab+(Aa[i]*Cb[i])%mod)%mod;
    for (ll i = 1; i <= a; ++i) ac = (ac+(Aa[i]*Cc[i])%mod)%mod;
    for (ll i = 1; i <= b; ++i) bc = (bc+(Ab[i]*Cc[i])%mod)%mod;
    ab++, ac++, bc++; ab %= mod, ac %= mod, bc %= mod;
    ans = ((ab*ac)%mod*bc)%mod;
    printf("%lld", ans);
    return 0;
}