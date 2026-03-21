//
// Created by Psy.C on 2026/3/21.
//
/**
p: 模数（通常是素数）
k: 底数
t: 保存原始k值
cnt: 计算k的阶（order）
计算k在模p下的乘法阶：最小的正整数d使得 k^d ≡ 1 (mod p)
cnt 就是k的阶数
特殊情况：当 k=0 时，阶数为1（但这里k=0的情况需要特别处理）

找到最小的 cnt 使得 k^cnt ≡ 1 (mod p)
根据费马小定理，我们知道 k^(p-1) ≡ 1 (mod p)（当gcd(k,p)=1时）
所以 cnt 是 (p-1) 的因子

阶的计算：O(阶数) ≤ O(p)
快速幂：O(log p)
总体：O(p)（最坏情况）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int mod = 1e9+7;
ll ksm(ll x, ll y) {
    ll t;
    for (t=1; y; y>>=1, x=x*x%mod)
        if (y&1) t=t*x%mod;
    return t;
}

ll p, k, t, cnt=1;
int main() {
    fast;
    cin >> p >> k; t = k;
    if (k)
        while (k % p != 1)
            k = k*t%p, cnt++;
    if (t != 1)
        cout << ksm(p, (p-1)/cnt) << '\n';
    else
        cout << ksm(p, (p-1)/cnt)*p%mod << '\n';
    return 0;
}