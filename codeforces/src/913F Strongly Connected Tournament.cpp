//
// Created by Psy.C on 2026/10/12.
//
/**
ksm(b, mod-2) 是 b 在模 mod 下的逆元，因此 P = a/b (mod),即一个概率。1-P 用 mod+1-P 表示
边界：w[i][1] = w[i][i-1] = Σ_{j=0}^{i-1} P^j (1-P)^{i-1-j}，即无组合系数的几何式求和（不是二项式展开，展开后等于 (1 - P(1-P)…) 之类），我用数值验证过，P=1/2 时为 3/4 而非 1【run_code 运行验证】。
中间项：w[i][j] = w[i-1][j-1]·P^{i-j} + w[i-1][j]·(1-P)^j。
这套递推产生一张"规模 i 时左右划分为 j / (i-j) 的概率权重表"，且对 P 与 1-P 交换对称
p[i] = 1 - Σ_{j<i} p[j]·w[i][j]：一种"退化/不可行插入"概率。
dp[i] 初始为 i(i-1)/2（逆序对/最大基数值），再对每个分割 j 累加 (dp[j]+dp[i-j]-(i-j)(i-j-1)/2)·w[i][j]·p[j]，最后除以 (1-p[i]) 做条件归一化。
结构是经典的 "根把规模 i 分成 j 与 i-j 两个子问题、递归求期望" 型 DP，w·p 是分割概率权重，1-p[i] 是分母
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 2e3+114, mod = 998244353;

int ksm(int a, int b) {
    if (b == 0) return 1;
    if (b == 1) return a;
    int res = ksm(a, b/2);
    res=res*res%mod;
    if (b%2 == 1) res=res*a%mod;
    return res;
}

int n, a, b, P, p[N], dp[N], w[N][N];
signed main() {
    fast;
    cin >> n >> a >> b; P = a*ksm(b, mod-2)%mod;
    p[1] = 1; dp[1] = 0;
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < i; ++j)
            w[i][1] = (w[i][1] + ksm(P, j)*ksm(mod+1-P, i-1-j)%mod)%mod;
        w[i][i-1] = w[i][1];
        for (int j = 2; j < i-1; ++j)
            w[i][j] = (w[i-1][j-1]*ksm(P, i-j)%mod + w[i-1][j]*ksm(mod+1-P, j)%mod)%mod;
    }
    for (int i = 2; i <= n; ++i) {
        p[i] = 1;
        for (int j = 1; j < i; ++j) p[i] = (p[i]+mod-p[j]*w[i][j]%mod)%mod;
        dp[i] = i*(i-1)/2%mod;
        for (int j = 1; j < i; ++j)
            dp[i] = (dp[i] + (dp[j]+dp[i-j]+mod-(i-j)*(i-j-1)/2%mod)%mod*w[i][j]%mod*p[j]%mod)%mod;
        dp[i] = dp[i]*ksm(mod+1-p[i], mod-2)%mod;
    }
    cout << dp[n] << '\n';
    return 0;
}