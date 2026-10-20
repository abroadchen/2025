//
// Created by Psy.C on 2026/10/20.
//
/**
先按位逆序排列（r[i] 预存的位反转表）。
标准蝴蝶变换：op=1 正变换，op=-1 逆变换（用 G 的逆元做根，最后乘 n 的逆元）。
返回变换后的数组
假定 a、b 已被 pad 到相同长度并已 NTT 化，这里直接点乘再逆变换。
由 mul 内部调用，不单独对外
pad 到长度 1<<k（≥ n+m+1），做一次完整卷积，再 resize 回 n+m+1 项。
这是"返回完整多项式乘积"的对外主 API
先倒序 a，卷积，再截前 n 项又倒序回来。
这个模式在代数里对应 "模 x^n 下 A 与 B 的某种逆/截断卷积"，常用于 多项式除法/求逆中"低位保留" 或 串匹配（字符串卷积翻转）‍。
这里具体用于 get 中"截断的低位卷积"
指数生成函数 EGF 的乘法：普通多项式卷积得到的系数需要除掉阶乘才是 EGF 卷积系数。
逻辑：
先把 a 的系数乘 i!（转成"EGF 卷积可乘"的形式）。
构造 b[i] = n^i / i!（这是 e^{n x} 的系数）。
c = dmul(a, b)：做一次截断卷积，得到含"e^{nx}"的中间结果（低位保留版）。
把 c 和 a 都除以对应阶乘，再做一次普通卷积 mul(a, c) 得 res。
综合起来，get 实现的应是某种 (EGF 意义下) 多项式与 e^{n·x} 卷积，并只保留前 n+1 项 的操作——在生成函数组合推导中常用于处理"上升/下降"递推。
语义推断（待题面确证）：get = 把多项式 a 与 e^{n x} 做 EGF 卷积（即组合意义下的"陪集/指数卷积"），截断到度数 n。
分治构造。
基准：n=1 时返回多项式 x。
一般步：res = dfs(n/2)，再 res = get(res)。
若 n 为奇数，再乘上一次线性多项式 (n-1) + x。
这个递推形式非常符合 第一类 Stirling 数（无符号）上升幂 的分治求法：
第一类 Stirling 数的生成函数 x^(overline n) = ∏_{i=0}^{n-1} (x + i)。
分治：F(2m) 可由 F(m) 经"平移/逆 Wilson 卷积"得到（正是 get 做的事——把 ∏(x+i) 从 m 扩张到 2m 需要乘 e^{mx} 型卷积），奇数再加一项 (x + n-1)。
所以 dfs(n) 实际应返回多项式 x^(overline n) = ∏_{k=0}^{n-1}(x+k) 的系数。
语义推断（强相关，待题面确证）：dfs(n) 输出的是 ∏_{i=0}^{n-1}(x+i)（上升幂），即无符号第一类 Stirling 数多项式
标准组合数（预处理阶乘逆元后 O(1)）
读入 n, A, B，预处理阶乘与逆元。
三种边界：A 或 B 为 0，或 A+B-1 > n → 输出 0；n==1 → 输出 1。
主要计算：res = dfs(n-1)（上升幂多项式），取 res[A+B-2] 系数与 C(A+B-2, A-1) 相乘取模输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define vl vector<ll>
#define sz(x) ((int)(x).size())
using namespace std;

constexpr int N = 5e5+5, mod = 998244353, G = 3;

inline ll ksm(ll b, ll p) {
    ll res = 1;
    while (p) {
        if (p&1) res=res*b%mod;
        b=b*b%mod;
        p>>=1;
    }
    return res;
}

ll r[N];
inline vl ntt(vl a, int op) {
    int n = sz(a);
    for (int i = 0; i < n; ++i) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int k = 1; k < n; k <<= 1) {
        ll wn = ksm(op==1?G:ksm(G,mod-2), (mod-1)/(k<<1));
        for (int i = 0; i < n; i += k<<1) {
            ll w = 1;
            for (int j = 0; j < k; ++j, w=w*wn%mod) {
                ll x = a[i+j], y = w*a[i+j+k]%mod;
                a[i+j] =(x+y)%mod;
                a[i+j+k] = (x-y+mod)%mod;
            }
        }
    }
    if (op == -1) {
        ll inv = ksm(n, mod-2);
        for (int i = 0; i < n; ++i) a[i] = a[i]*inv%mod;
    }
    return a;
}

inline vl operator*(vl a, vl b) {
    a = ntt(a, 1); b = ntt(b, 1);
    int n = sz(a);
    for (int i = 0; i < n; ++i) a[i] = a[i]*b[i]%mod;
    a = ntt(a, -1);
    return a;
}
inline vl mul(vl a, vl b) {
    int n = sz(a) - 1, m = sz(b) - 1, k = 0;
    while (1<<k <= n+m+1) ++k;//求 >= 长度和的 2^k
    for (int i = 1; i < 1<<k; ++i) r[i] = (r[i>>1]>>1)|((i&1)<<(k-1));
    vl A(1<<k), B(1<<k);
    for (int i = 0; i <= n; ++i) A[i] = a[i];
    for (int i = 0; i <= m; ++i) B[i] = b[i];
    vl res = A*B; res.resize(n+m+1);//截取有效项
    return res;
}
inline vl dmul(vl a, vl b) {
    int n = sz(a); ranges::reverse(a);//反转 a
    a = mul(a, move(b)); a.resize(n); ranges::reverse(a);//反转回来
    return a;
}

ll fac[N], ifac[N];
inline vl get(vl a) {
    int n = sz(a) - 1;
    for (int i = 0; i <= n; ++i) a[i] = a[i]*fac[i]%mod;//a_i *= i!
    vl b(n+1);
    ll pw = 1;
    for (int i = 0; i <= n; ++i) {
        b[i] = pw*ifac[i]%mod;//b[i] = n^i / i!
        pw = pw*n%mod;
    }
    vl c = dmul(a, b);
    for (int i = 0; i <= n; ++i) {
        c[i] = c[i]*ifac[i]%mod;
        a[i] = a[i]*ifac[i]%mod;//a 还原为原系数
    }
    vl res = mul(a, c);
    return res;
}
vl dfs(int n) {
    if (n == 1) {
        vl res(2); res[1] = 1;//返回多项式 x
        return res;
    }
    int m = n/2;
    vl res = dfs(m); res = get(res);//对 dfs(m) 做 get 变换
    if (n&1) {
        vl a(2); a[0] = n-1; a[1] = 1;//多项式 (n-1) + x
        res = mul(res, a);
    }
    return res;
}

inline ll C(ll n, ll m) {
    if (n < m || n < 0 || m < 0) return 0;
    return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

ll n, A, B;
void solve() {
    cin >> n >> A >> B; fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = fac[i-1]*i%mod;
    ifac[n] = ksm(fac[n], mod-2);
    for (int i = n-1; ~i; --i) ifac[i] = ifac[i+1]*(i+1)%mod;
    if (!A || !B || A+B-1 > n) { cout << "0\n"; return; }
    if (n == 1) { cout << "1\n"; return; }
    vl res = dfs(n-1);
    cout << res[A+B-2]*C(A+B-2,A-1)%mod << '\n';
}

int main() {
    fast;
    int T = 1;
    while (T--) solve();
    return 0;
}