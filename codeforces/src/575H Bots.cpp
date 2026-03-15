//
// Created by Psy.C on 2026/3/15.
//
/**
fac[i]：存储i! % mod（i的阶乘模mod）
inv[i]：存储i!的模逆元，即(i!)^(-1) % mod
fac[0] = 1：0! = 1
inv[1] = 1：1的逆元是1
inv[0] = 1：(0!)^(-1) = 1
(i!)^(-1) = ((i-1)!)^(-1) * (i^(-1))

这个程序计算的是卡塔兰数（Catalan Number）的一个变种，公式为： C(2n+2, n+1) - 1
卡塔兰数通常表示为 C(2n,n)/(n+1)，这里使用了等价形式 C(2n+2, n+1)/(n+2) 的变形。
该程序高效地解决了大规模组合数计算问题，时间复杂度：
预处理：O(N)
单次查询：O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e6+2, mod = 1e9+7;

int fac[N], inv[N];
void init(int n=N) {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = 1ll*i*fac[i-1]%mod;
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] = mod - 1ll*(mod/i)*inv[mod%i]%mod;
    inv[0] = 1;
    for (int i = 1; i <= n; ++i)
        inv[i] = 1ll*inv[i-1]*inv[i]%mod;
}

int C(int n, int m) {
    return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}

int n;
int main() {
    fast; init();
    cin >> n;
    cout << (C(2*n+2, n+1) - 1 + mod) % mod << '\n';
    return 0;
}