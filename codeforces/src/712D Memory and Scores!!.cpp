//
// Created by Psy.C on 2026/4/20.
//
/**
计算阶乘数组
使用费马小定理计算逆元：a^(-1) ≡ a^(p-2) (mod p)
从后往前计算阶乘逆元
计算组合数的前缀和

遍历容斥原理中的每一层（0到t）
i代表排除的约束条件数量
x = (2*k+1)*(t-i)：偏移量，表示排除了(t-i)个约束条件后的修正值
(2*k+1)：可能是每个约束条件的影响范围
(t-i)：还有多少个约束条件需要考虑
l = max(lim-x, 0)：有效范围的左边界
r = 2*k*t-x：有效范围的右边界
这定义了我们需要计算的区间[l, r]

1. C(t, i)
从t个约束条件中选择i个的组合数
表示我们考虑同时违反i个约束条件的方案数
2. (i&1?-1:1)
容斥原理的正负号：(-1)^i
当i为奇数时为-1，i为偶数时为1
这是容斥原理的核心：加偶数项，减奇数项
3. ((sum[r]-(l?sum[l-1]:0)+mod)%mod)
计算区间[l, r]内满足条件的方案数
sum[r]：前r项的前缀和
l?sum[l-1]:0：前l-1项的前缀和（如果l>0）
sum[r] - sum[l-1]：区间[l, r]的和
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 8e5+7, mod = 1e9+7, M = 410000;

int ksm(int x, int k) {
    int res = 1;
    while (k) {
        if (k&1) res = 1ll*res*x % mod;
        x = 1ll*x*x % mod;
        k >>= 1;
    }
    return res;
}
int fac[N], inv[N];
int C(int n, int m) {
    if (n < m) return 0;
    return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int sum[N];
int main() {
    fast;
    int a = rd(), b = rd(), k = rd(), t = rd()<<1;
    int lim = k*t - a + b + 1; fac[0] = 1;
    for (int i = 1; i <= M; ++i) fac[i] = 1ll*fac[i-1]*i%mod;
    inv[M] = ksm(fac[M], mod-2);
    for (int i = M-1; ~i; --i) inv[i] = 1ll*inv[i+1]*(i+1)%mod;
    sum[0] = 1;
    for (int i = 1; i <= 2*k*t; ++i) sum[i] = (sum[i-1]+C(t+i-1,t-1))%mod;
    int ans = 0;
    for (int i = 0; i <= t; ++i) {
        int x = (2*k+1)*(t-i), l = max(lim-x, 0), r = 2*k*t-x;
        if (l > r || r < 0) continue;
        if (l > r) swap(l, r);
        ans = (ans + 1ll*C(t, i)*(i&1?-1:1)*((sum[r]-(l?sum[l-1]:0)+mod)%mod)%mod+mod)%mod;
    }
    cout << ans;
    return 0;
}