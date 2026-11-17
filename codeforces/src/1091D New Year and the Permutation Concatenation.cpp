//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
a^(-1) = a^(mod-2)。
用预计算阶乘与逆元 O(1) 求组合数 C(a,b) = a!/(b!(a-b)!) mod p。
边界：a<b 返回 0，b=0 或 a=b 返回 1
fac[i]：i! mod p。
逆元用递推式 inv[i] = inv[i+1]*(i+1) mod p 一次性算好，比逐个快速幂快（费马小定理只在 inv[N-1] 用一次）。
该式由 1/i! = 1/(i+1)! × (i+1) 恒等推导。
读入 n。
初始 ans = n!。
对 i 从 2 到 n-1 累加 (i! - 1) * C(n,i) * (n-i)!。
输出 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 1e6+5, mod = 998244353;

int ksm(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

int fac[N], inv[N];
int C(int a, int b) {
    if (a < b) return 0;
    if (b == 0 || a == b) return 1;
    return fac[a]*inv[b]%mod*inv[a-b]%mod;
}

void init() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i-1]*i%mod;
    inv[N-1] = ksm(fac[N-1], mod-2);
    for (int i = N-2; i >= 0; i--) inv[i] = inv[i+1]*(i+1)%mod;
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n;
signed main() {
    fast; init();
    read(n);
    int ans = fac[n];
    for (int i = 2; i < n; i++)
        ans = (ans + ((fac[i]-1)*C(n,i)%mod*fac[n-i])%mod)%mod;
    cout << ans << '\n';
    return 0;
}