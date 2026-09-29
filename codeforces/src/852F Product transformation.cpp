//
// Created by Psy.C on 2026/9/29.
//
/**
fac[i] = i! % mod，预处理到约 1e9 规模（N=1e6+1e2）。
inv[] 用线性递推求逆元：inv[i] = inv[mod%i]*(mod-mod/i)%mod（需 mod 为素数）。
第二遍循环把 inv[i] 变成阶乘逆元（inv[i] = inv[i]*inv[i-1]，即 1/i!）。
于是 C(n,m) = n!/m!/(n-m)! 组合数可直接 O(1) 求
带模数参数 p 的快速幂（因为这里要对 q 取模，而不是固定 mod）。指数也可能是很大的数（ans[i]）
从 mod=1 开始，逐个增加，直到满足 a^mod ≡ 1 (mod q)。
也就是说，mod 被设成 a 在模 q 意义下的阶（order）‍——满足 a^k≡1 (mod q) 的最小正 k。
这保证了指数可以在这个模下"折叠"：因为对任意指数 e，a^e ≡ a^(e % mod)（mod q），且用费马/欧拉思想可把大指数取模到 mod 内来算组合数。
注意：该模数需要是素数才能用上面的线性逆元；题目保证/该区域内成立（假定如此
c[i] 是 C(m, i-1) 的前缀和：c[i] = Σ_{j=1..i} C(m, j-1) = Σ_{t=0..i-1} C(m,t)
从后往前填 ans[]。
当 n-i+1 <= m+1（即未超出前缀和范围）时，ans[i] = c[n-i+1]；
否则沿用后面一个（相当于前缀和"截断/钳制"在末尾值）。
效果：ans[i] 在开头是变化的前缀和，超过范围后保持不变（类似取前缀和的最大范围
依次输出 a^ans[i] mod q（指数为前缀和/固定值），中间空格分隔
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+1e2;

int mod;
ll fac[N], inv[N];
void init() {
    fac[0] = 1;
    for (int i = 1; i <= N; ++i) fac[i] = fac[i-1]*i%mod;
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= N; ++i) inv[i] = inv[mod%i]*(mod-mod/i)%mod;
    for (int i = 2; i <= N; ++i) inv[i] = inv[i]*inv[i-1]%mod;
}

ll C(int n, int m) {
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}

ll ksm(ll a, ll b, ll p) {
    ll c = 1;
    while (b) {
        if (b&1) c=c*a%p;
        a=a*a%p;
        b>>=1;
    }
    return c;
}

int n, m, a, q;
ll c[N], ans[N];
int main() {
    fast;
    cin>>n>>m>>a>>q; mod = 1;
    while (ksm(a, mod, q) != 1) mod++; init();
    for (int i = 1; i <= m+1; ++i) {
        c[i] = C(m, i-1);
        c[i] = (c[i] + c[i-1]) % mod;
    }
    for (int i = n; i; --i) {
        if (n-i+1 <= m+1) ans[i] = c[n-i+1];
        else ans[i] = ans[i+1];
    }
    for (int i = 1; i < n; ++i)
        cout << ksm(a, ans[i], q) << ' ';
    cout << ksm(a, ans[n], q) << '\n';
    return 0;
}