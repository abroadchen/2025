//
// Created by Psy.C on 2026/2/10.
//
/**
求满足以下条件的非负整数解的个数：
x₁ + x₂ + ... + xₙ = m
0 ≤ xᵢ ≤ f[i] (对所有i)

无限制方案数：C(n+m-1, n-1)
违反特定限制的方案数：通过变量替换计算
最终答案：∑(容斥符号) × Lucas(剩余和, n-1)

时间复杂度：O(2^n × n × log(mod))
空间复杂度：O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define mod 1000000007
using namespace std;

ll ksm(ll a, ll x) {//时间复杂度：O(log x)
    ll res = 1; a %= mod;
    while (x) {
        if (x&1ll) res = res * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return res;
}

ll C(const ll a, ll b) {
    ll res = 1, fm = 1, fz = 1;
    if (a - b < b) b = a - b;//C(a,b) = C(a,a-b)
    for (int i = 1; i <= b; ++i) {
        fm = fm * i % mod;//分母
        fz = fz * (a - i + 1) % mod;//分子
    }
    res = fz * ksm(fm, mod - 2) % mod;//分母的模逆元
    return res;
}

ll Lucas(const ll a, const ll b) {//适用于a,b很大的情况
    if (b == 0) return 1;
    return Lucas(a/mod, b/mod) * C(a%mod, b%mod) % mod;
}

int n;
ll m, f[22], ans;
void out() {
    for (int i = 0; i < 1<<n; ++i) {//枚举所有可能的子集
        ll sgn = 1, sum = m;//总和上限
        for (int j = 0; j < n; ++j)
            //第j位是否在子集i中
            if (1<<j&i) sum -= f[j] + 1, sgn *= -1;//选择第j个限制，减去(f[j]+1) 容斥符号交替变化
        if (sum < 0) continue;
        ans = (ans + sgn * Lucas(n + sum - 1, n - 1)) % mod;
    }
}

int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> f[i]; out();
    cout << (ans%mod + mod) % mod << '\n';
    return 0;
}