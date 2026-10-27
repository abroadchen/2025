//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
带符号的模加：处理 x+y 可能落在 [-mod, 2*mod)，只做一次加减修正
快速幂。add(x,0) 用前面的 add 把负数 x 归一化（因为后面会有 ksm(-1, i+1) 这种负底数）。
y 作为指数直接按二进制幂乘
组合数 C(x,y)，预先算好阶乘和逆元
a = C(n,i) * (-1)^(i+1)：这就是容斥的 ± 组合系数（i 从 1 开始）。
指数 (n*(n-i)+i) % (mod-1)：用费马小定理降幂。因为 mod 是质数 998244353，3^(mod-1) ≡ 1，所以指数只需对 mod-1 取模。
x = 3^(n(n-i)+i)：某种以 3 为底的方案计数（可能是某种自由染色计数，含 3 种颜色）。
累加后 ans = 2*ans
t = -3^i（对 mod 取负）。
x = (t+1)^n - t^n：差的形式，类似"至少选一个"。
同样用容斥系数 a 累加。
res = 3*res（3 因子）
最终答案是两个容斥和相加
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 1e6+5, mod = 998244353;

void add(int &x, int y) {
    x += y;
    if (x < 0) x += mod;
    if (x >= mod) x -= mod;
}
int ksm(int x, int y) {
    add(x, 0);
    int z = 1;
    for (; y; y>>=1) {
        if (y&1) z=1ll*z*x%mod;
        x=1ll*x*x%mod;
    }
    return z;
}

int fac[N], inv[N];
int C(int x, int y) { return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod; }

int n, ans, res;
int main() {
    fast;
    cin >> n; fac[0] = 1, inv[0] = 1;
    rep(i,n) {
        fac[i] = 1ll*fac[i-1]*i%mod;
        inv[i] = ksm(fac[i], mod-2);
    }
    rep(i,n) {
        int a = 1ll*C(n,i)*ksm(-1,i+1)%mod,
        x = ksm(3,(1ll*n*(n-i)+i)%(mod-1));
        add(ans,1ll*a*x%mod);
    }
    ans = 2*ans%mod;
    for (int i = 0; i < n; i++) {
        int t = mod - ksm(3,i), x = (ksm(t+1,n)+mod-ksm(t,n))%mod,
        a = 1ll*C(n,i)*ksm(-1,i+1)%mod;
        add(res, 1ll*a*x%mod);
    }
    res = 3ll*res%mod;
    cout << (ans+res)%mod << '\n';
    return 0;
}