//
// Created by Psy.C on 2026/10/14.
//
/**
mod = 998244353：NTT 常用质数（NTT-friendly，原根为 3）。
N = (1<<20)+1：最大多项式数组长度（约 1e6）。
inf = 1e5：暴力乘法的阈值（两多项式度数乘积 ≤ 1e5 时直接用三重循环，否则用 NTT）。
E = mod-1：费马小定理指数，用于降幂（指数 m 对 mod-1 取模）
ksm 标准二进制快速幂。
INV = 3^(mod-2)：原根 3 的逆元，供逆变换用
pw[i]、ipw[i]：NTT 各级单位根与逆单位根。
fac/inv：阶乘与阶乘逆元，预处理到 2n（用于之后的多项式点值/系数转换和组合数）。
n<<1 预计算到 2n，说明程序可能用到长度为 2n 的组合
一个小 helper，把 t 规范化到 [0, mod)
标准 Cooley-Tukey 迭代 NTT。
正变换 iv=false 用 pw[e]（正单位根），逆变换 iv=true 用 ipw[e]（逆单位根），逆变换最后乘 len 的逆元。
rev 数组存位逆序，由调用方预计算
封装了多项式乘法：小度数据跑平方级暴力，大度数走 NTT，自适应.
input/out/init/resize：输入、输出、初始化、截断长度的辅助函数
这一步是经典的 多项式幂级数复合 / "矩阵指数"（matrix exponential 或 e.g. 幂级数在 x 平移下的作用）‍ 套路：

先把 p 乘 fac[i] 做"点乘"预处理；
利用 1/i! 的卷积反向实现差分/级数求其多项式在某点的平移（即计算 p(x+1) 或复合 (i+1) 的幂）；
乘 (i+1)^{-m} 并对奇数项取负 → 相当于对第 i 项施加 (-1)^i (i+1)^{-m} 的逐点乘法（对角矩阵作用）；
再做一次反向卷积还原系数，并除以 i!。
这其实是 "多项式在变换下的复合"（polynomial composition / 类似 Stirling 变换或 e^(x) 卷积）‍，常见于 多项式幂、斯特林数、及"给多项式每个系数乘 (-1)^i (i+1)^c"型的组合问题

输入一个 n 次多项式 p，以及幂次 m，输出变换后多项式
g_i = (1/i!) · (-1)^i · (系数经 (i+1)^{-m} 缩放)
——本质是多项式在"某个平移/指数核"下的复合（幂级数指数变换）‍，用两次 NTT 卷积优化到 O(n log n)。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; --i)
#define ll long long
using namespace std;

constexpr int N = (1<<20)+1, mod = 998244353, M = 2e5+1, inf = 1e5, E = mod-1;

inline ll ksm(ll base, int e) {
    ll res = 1;
    while (e) {
        (e&1) && ((res=res*base%mod));
        base=base*base%mod;
        e>>=1;
    }
    return res;
}
int INV = ksm(3, mod-2);
int pw[22], ipw[22], fac[M], inv[M], n;
inline void calc() {
    rep(i,1,21) {
        pw[i] = ksm(3, (mod-1)>>i);
        ipw[i] = ksm(INV, (mod-1)>>i);
    }
    fac[0] = inv[0] = 1;
    int t(n<<1);
    rep(i,1,t) fac[i] = fac[i-1]*1ll*i%mod;
    inv[t] = ksm(fac[t], mod-2);
    per(i,t,2) inv[i-1] = inv[i]*1ll*i%mod;
}

inline void add(int &t) {
    t < 0 && (t += mod);
    t >= mod && (t -= mod);
}

int rev[N];
inline void ntt(int *p, int len, bool iv) {
    rep(i,0,len-1) if (i < rev[i]) swap(p[i], p[rev[i]]);
    static ll g[N]; g[0] = 1;
    for (int i = 1, e = 1; i < len; i <<= 1, ++e) {
        ll o = iv ? ipw[e] : pw[e];//正/逆变换的旋转因子
        rep(j,1,i-1) g[j] = g[j-1]*1ll*o%mod;//该层旋转因子
        for (int j = 0; j < len; j += i<<1) rep(k,0,i-1) {
            int x = p[j+k], y = g[k]*p[i+j+k]%mod;
            p[j+k] = (x+y)%mod;
            p[i+j+k] = (x-y+mod)%mod;//蝴蝶操作
        }
    }
    if (iv) {//逆变换末尾除以 len
        ll il = ksm(len, mod-2);
        rep(i,0,len-1) p[i] = il*p[i]%mod;
    }
}

struct poly {
    int len=0, num[N]{};
    void resize(const int a) {
        for (; len > a; --len) num[len] = 0;
        len = a;
        if (len < 0) len = 0;
    }
    poly operator*(const poly a) const {
        poly x, y = *this;
        if (a.len*1ll*len <= inf) {
            x.len = a.len + len;
            rep(i,0,len) rep(j,0,a.len) {
                int &w(x.num[i+j]);
                w += a.num[j]*1ll*num[i]%mod;
                w >= mod && (w -= mod);
            }
            return x;
        }
        x = a;
        int e = max((int)ceil(log2(((len+a.len+1)<<1)+1)), 1), l = 1<<e;
        rep(i,0,l-1) rev[i] = (rev[i>>1]>>1)|((i&1)<<(e-1));
        ntt(x.num, l, 0); ntt(y.num, l, 0);
        rep(i,0,l-1) x.num[i] = 1ll*x.num[i]*y.num[i]%mod;
        ntt(x.num, l, 1); x.resize(len+a.len);
        return x;
    }
} p;

ll m;
int main() {
    fast;
    cin >> n >> m; calc(); m >= E && (m%=E); p.len = n;
    rep(i,0,n) cin >> p.num[i], p.num[i] = p.num[i]*1ll*fac[i]%mod;
    poly x; x.len = n;
    rep(i,0,n) x.num[i] = inv[i]; reverse(p.num, p.num+n+1);
    p = p*x; p.resize(n); reverse(p.num, p.num+n+1);
    rep(i,0,n) {
        p.num[i] = p.num[i]*ksm(ksm(i+1,mod-2),m)%mod;
        (i&1) && ((p.num[i] = mod - p.num[i]));
    }
    reverse(p.num, p.num+n+1);
    p = p*x; p.resize(n); reverse(p.num, p.num+n+1);
    rep(i,0,n) cout << ((i&1)?mod-p.num[i]*1ll*inv[i]%mod:p.num[i]*1ll*inv[i]%mod)%mod << ' ';
    return 0;
}