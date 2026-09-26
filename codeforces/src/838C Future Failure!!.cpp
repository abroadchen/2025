//
// Created by Psy.C on 2026/9/26.
//
/**
用 Barrett reduction 做快速取模（用乘法+位移代替除法），是竞赛里的取模加速技巧
线性求逆元 + 阶乘 fac、阶乘逆元 ifac，供组合数 C(n,k)=fac[n]*ifac[k]*ifac[n-k] 使用
这是 标准 FWT-OR（或卷积）变换，x=1 是正变换，x=mod-1（即 -1）是逆变换。
用于把"或卷积"变为点乘，从而加速计数
当 n 为偶数才进入。核心处理：
cnt = popcount(n)：n 二进制里 1 的个数。
len：不小于 n 的 2 的幂（因为 FWT 需要长度是 2 的幂）。
初始化数组：f[pc][i] = ifac[i]（每个位置按 popcount 分层），g[0][i]=1
用类似快速幂的二进制幂方式做"或卷积的 K 次方"。因为已经做过 FWT 正变换，卷积变成逐点相乘，所以内层是点乘累加（g[k][i]*f[j-k][i]
逆变换回原域后，取下标为 n 的值，乘 n!，从 res 中减掉
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ull unsigned long long
#define ll long long
using namespace std;
constexpr int N = 64, M = 1e6+10, O = 19, L = 3e5;
struct bm {
    ull d;
    __uint128_t m;
    void init(ll mod) { m = (((__uint128_t)1) << N)/(d=mod); }

    __attribute__((always_inline)) ull operator()(ull x) const {
        ull w = (m*x)>>N;
        w = x - w*d;
        return w >= d ? w - d : w;
    }
} MOD;
ll mod;
void fwtor(ll *f, ll x, int n) {
    int i, j, k, o;
    for (o = 2, k = 1; o <= n; o<<=1, k<<=1)
        for (i = 0; i < n; i += o)
            for (j = 0; j < k; ++j)
                f[i+j+k] = MOD(f[i+j+k]+f[i+j]*x);
}

ll inv[M], fac[M], ifac[M];
void init(int n) {
    int i;
    for (inv[0]=0, inv[1]=fac[0]=fac[1]=ifac[0]=ifac[1]=1, i = 2; i <= n; ++i)
        ifac[i] = ifac[i-1]*(inv[i]=mod-mod/i*inv[mod%i]%mod)%mod, fac[i] = fac[i-1]*i%mod;
}
ll ksm(ll b, ll e) {
    ll res = 1;
    while (e) {
        if (e&1) res=MOD(res*b);
        b=MOD(b*b);
        e>>=1;
    }
    return res;
}

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

ll f[O][L], g[O][L], res;
int i, j, k, len, e, cnt;
int main() {
    fast;
    int n = read(), K = read(); mod = read(); MOD.init(mod);
    res = ksm(K, n);
    if (!(n&1)) {
        cnt = __builtin_popcount(n);
        len = 1<<__lg(n);//2^floor(log2 n)
        if (len <= n) len <<= 1;//扩大到 ≥ n 的 2 的幂
        init(len);//预处理阶乘到 len
        for (i = 0; i < len; ++i)
            f[__builtin_popcount(i)][i] = ifac[i], g[0][i] = 1;
        for (i = 0; i <= cnt; ++i) fwtor(f[i], 1, len);//f 做 FWT-OR 正变换
        e = K;
        while (e) {
            if (e&1) {
                for (j = cnt; ~j; --j)
                    for (k = 0; k < j; ++k)
                        for (i = 0; i < len; ++i)
                            g[j][i] = MOD(g[j][i]+g[k][i]*f[j-k][i]);
            }
            for (j = cnt; ~j; --j)
                for (k = 0; k < j; ++k)
                    for (i = 0; i < len; ++i)
                        f[j][i] = MOD(f[j][i]+f[k][i]*f[j-k][i]);
            e>>=1;
        }
        fwtor(g[cnt], mod-1, len);//FWT-OR 逆变换
        (res += mod-g[cnt][n]*fac[n]%mod) %= mod;//res -= g[cnt][n]*n!
    }
    write(res);
    return 0;
}