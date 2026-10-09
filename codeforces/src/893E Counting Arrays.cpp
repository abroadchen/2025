//
// Created by Psy.C on 2026/10/9.
//
/**
预计算阶乘 fac、逆元阶乘 inv，用 C(n,m) 算组合数（对大模数取模）
递推求每个数模
p
p 的逆元（inv[i] = (p - p/i) * inv[p%i] % p）。
再乘起来得到 inv[i] = (i!)^{-1}（阶乘的逆元），配合 fac 用组合数公式
核心数学：把
x
x 质因数分解成
x
=
∏
p
i
c
i
x=∏p
i
c
i
​

​
 ，问题等价于——要把
x
x 分解成
y
y 个两两互质的因子。由于各质因子独立，对每个质因子
p
i
c
i
p
i
c
i
​

​
 ，它只能整体分给
y
y 个因子中的某一个（否则两个因子会不互质），所以：

每个质因子的分配是独立的；
但还有"每个因子是否为 1"的处理导致出现
2
y
−
1
2
y−1
  的项
这个公式与"把 n 拆成 k 个因子乘积"或 "balls into boxes with stars-and-bars" 一致：
(
c
n
t
+
y
−
1
y
−
1
)
(
y−1
cnt+y−1
​
 ) 是隔板法（把
c
n
t
cnt 个同类质因子分配到
y
y 个组，可空组）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e6, mod = 1e9+7;

int ksm(int a, int x) {
    int s = 1;
    for (; x; x&1?s=1ll*s*a%mod:0,a=1ll*a*a%mod,x>>=1) {}
    return s;
}
int fac[N+5], inv[N+5];
int C(int n, int m) { return 1ll*fac[n]*inv[n-m]%mod*inv[m]%mod; }

int x, y, ans;
int main() {
    fast;
    int T; cin >> T; fac[0] = 1;
    for (int i = 1; i <= N; ++i) fac[i] = 1ll*fac[i-1]*i%mod;
    inv[1] = 1;
    for (int i = 2; i <= N; ++i) inv[i] = 1ll*(mod-mod/i)*inv[mod%i]%mod;//线性求逆元
    inv[0] = 1;
    for (int i = 1; i <= N; ++i) inv[i] = 1ll*inv[i-1]*inv[i]%mod;//逆元前缀积 → 阶乘逆元
    while (T--) {
        cin >> x >> y; ans = ksm(2, y-1);//初始 = 2^(y-1)
        int t = x;
        for (int i = 2; i*i <= t; ++i) {//对 x 分解质因数
            if (t%i == 0) {
                int cnt = 0;
                while (t%i == 0) { t /= i; cnt++; }//cnt = 质因子 i 的重数
                ans = 1ll*ans*C(cnt+y-1, y-1)%mod;//乘上盒分配方案
            }
        }
        if (t != 1) ans = 1ll*ans*y%mod;//剩余一个次数为1的大质因子 → 乘 y
        cout << ans << '\n';
    }
    return 0;
}