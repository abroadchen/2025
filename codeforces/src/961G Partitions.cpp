//
// Created by Psy.C on 2026/10/21.
//
/**
标准快速幂，计算 a^b mod mod。
可确证：ksm(a,b) 返回 a^b mod 1e9+7【快速幂标准实现】
fac[i] = i! mod mod，预处理到 N-1。
C(m,n) = C(m,n) 组合数，用费马小定理求逆元（mod 为质数）：fac[m] * inv(fac[n]) * inv(fac[m-n])。
可确证：init 预处理 1..N-1 的阶乘；C(m,n) 用阶乘和费马小定理逆元计算组合数【标准实现】
r = k^n：先算总的映射数 k^n（把 n 个元素任意映射到 k 个位置/集合——不要求满射）。
循环 i=1..k：按容斥/交错和减去"有至少 i 个集合为空"的映射数：
C(k,i) * (k-i)^n 是"选定 i 个特定集合为空、其余 k-i 个集合任意分配"的映射数。
(i&1 ? -1 : 1) 给符号：i 为奇数时减，偶数时加（容斥的交替符号）。
整体 r = k^n - C(k,1)(k-1)^n + C(k,2)(k-2)^n - ...，这正是经典容斥：n 个不同元素到 k 个非空集合的满射/划分计数中的求和核心。
最后 * inv(fac[k])：除以 k!。这一步把"有序分配到 k 个有标号集合（且非空）"的计数转成"k 个无标号非空集合的划分"——即 第二类斯特林数 S(n,k) 的公式。
可确证：get(n,k) 通过容斥 Σ (-1)^i C(k,i)(k-i)^n 后除以 k!，得到 第二类斯特林数 S(n,k) 的显式公式（n 个不同元素划分成 k 个非空无标号集合的方案数）。
也就是说：get(n,k) = S(n,k)（第二类斯特林数
读入 n, k 与 a[1..n]。
x = get(n,k) = S(n,k)（第二类斯特林数，n 个元素分 k 块）。
y = get(n-1,k) = S(n-1,k)（n-1 个元素分 k 块）。
对每个 i 累加：r += a[i] * (x + (n-1)*y) mod mod。
可确证：x = S(n,k)，y = S(n-1,k)，主循环对每个 a[i] 乘上公共系数 (x + (n-1)*y) 后求和
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for (i = 1; i <= n; i++)
using namespace std;

constexpr int N = 2e5+1, mod = 1e9+7;

ll ksm(ll a, ll b) {
    ll r = 1;
    for (; b; b>>=1, a=a*a%mod)
        if (b&1) r=r*a%mod;
    return r;
}

ll fac[N], i;
void init() {
    fac[0] = 1;
    rep(i,N-1) { fac[i] = fac[i-1]*i; fac[i] %= mod; }
}
ll C(ll m, ll n) { return fac[m]*ksm(fac[n],mod-2)%mod*ksm(fac[m-n],mod-2)%mod; }

ll get(ll n, ll k) {
    ll r = ksm(k, n);
    rep(i,k) r = (r+(i&1?-1:1)*C(k,i)*ksm(k-i,n)%mod+mod)%mod;
    return r*ksm(fac[k],mod-2)%mod;
}

ll n, k, a[N];
int main() {
    fast;
    init(); cin >> n >> k;
    rep(i,n) cin >> a[i];
    ll x = get(n, k), y = get(n-1, k), r = 0;
    rep(i,n) r=(r+a[i]*(x+(n-1)*y%mod)%mod)%mod;
    cout << r << '\n';
    return 0;
}