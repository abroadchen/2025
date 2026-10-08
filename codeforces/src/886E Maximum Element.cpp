//
// Created by Psy.C on 2026/10/8.
//
/**
标准二进制快速幂，模 1e9+7，用于后面 f[n]^(mod-2) 求 n! 的逆元（费马小定理，mod 为质数）
f[i]：阶乘；inv[i]：(i!)^{-1}。利用 inv[i] = inv[i+1]*(i+1) 反向递推，O(n) 得到全部逆元
dp[i] 表示某种"以 i 为末尾的合法结构数"。
sum 是一个滑动前缀和：dp[i] = f[i-1] * (sum)，其中 sum = Σ dp[j]*inv[j]（j 在窗口 [i-k, i-1] 内）。窗口超过 k 就减掉最老的一项，使递推只依赖最近 k 项 —— 这正对应题意里"长度不超过 k 的段"的约束
f[n-1]*inv[i-1] =
(
n
−
1
)
!
/
(
i
−
1
)
!
(n−1)!/(i−1)!，即把已定结构外的部分做全排列，累加得到"坏情况总数" tot
合法数量 = 总排列数 n! 减去坏情况 tot
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+5, mod = 1e9+7;

ll ksm(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y&1) res=res*x%mod;
        x=x*x%mod;
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

ll inv[N], f[N], dp[N], sum, tot;
int main() {
    fast;
    int n = rd(), k = rd(); inv[0] = f[0] = 1;
    for (int i = 1; i <= n; ++i) f[i] = f[i-1]*i%mod;
    inv[n] = ksm(f[n], mod-2);
    for (int i = n-1; i; --i) inv[i] = inv[i+1]*(i+1)%mod;
    dp[0] = sum = 1;
    for (int i = 1; i <= n; ++i) {
        dp[i] = f[i-1]*sum%mod;
        sum = (sum+dp[i]*inv[i]%mod)%mod;
        if (i >= k) sum = (sum-dp[i-k]*inv[i-k]%mod+mod)%mod;
    }
    for (int i = 1; i <= n; ++i)
        tot = (tot+dp[i-1]*f[n-1]%mod*inv[i-1]%mod)%mod;
    cout << (f[n]-tot+mod)%mod << '\n';
    return 0;
}