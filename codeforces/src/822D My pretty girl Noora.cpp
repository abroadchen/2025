//
// Created by Psy.C on 2026/9/23.
//
/**
对每个质数 i，把其倍数 k = i*j 记录：v[k] = i（k 的最小质因子），pre[k] = j（互补因子）。
质数 i 自己的 pre[i] = i*(i-1)/2（组合数 C(i,2)，模 mod）
对每个合数 i，沿其质因子分解链（通过 v[j] 和 pre[j]）累加 pri[i]。
分解链原理：i 可写成一个质因子 p 与另一因子 q 的乘积（v[i]=p, pre[i]=q），再对 q 继续分解……直到 q 为质数。每一步累加 pre[p]*pre[q]（即质数 p 的 pre 值 × 当前互补因子的 pre 值）。
最终 pri[i] 是基于质因数分解的某种「价值」累积和最
对 [l, r] 内每个 i，累加 pri[i] 乘上权重 t 的幂（从 t^0 到 t^(r-l)），全程取模
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 5e6+5, mod = 1e9+7;

ll v[N], pri[N], pre[N];
void init() {
    memset(v, 0, sizeof(v));
    memset(pri, 0, sizeof(pri));
    ll i, j, k;
    for (i = 2; i < N-4; ++i) {
        if (!v[i]) {
            for (j = 2; i*j < N-4; ++j) {
                k = i*j;
                if (!v[k]) { v[k] = i; pre[k] = j; }
            }
            pre[i] = i*(i-1)/2;
            pre[i] = pre[i]%mod;
        }
    }
    for (i = 2; i < N-4; ++i) {
        j = i;
        if (v[i]) {
            while (v[j]) {//沿分解链
                pri[i] += pre[v[j]]*pre[j];
                pri[i] = pri[i]%mod;
                j = pre[j];//跳到互补因子
            }
        }
        pri[i] += pre[j];//加上最后的质数项
        pri[i] = pri[i]%mod;
    }
}

ll l, r, t;
ll solve() {
    ll i, m = 1, ans = 0;
    for (i = l; i <= r; ++i) {
        ans += pri[i]*m;
        ans = ans%mod;
        m = (m*t)%mod;
    }
    return ans;
}

int main() {
    fast;
    init(); cin >> t >> l >> r;
    cout << solve() << '\n';
    return 0;
}