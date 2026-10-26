//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
先把 a、b 各自取模，然后相乘再取模。
作用是统一地做"两个数的模乘法"，避免中间结果溢出（虽然 long long 范围内直接乘一般不会溢出，但统一封装更规范）
标准二进制快速幂算法，计算 base^t mod mod：

res = 1 表示累积结果，mul = base 表示当前位权值。
循环：只要 t 非零：
若 t 当前最低位为 1（t & 1）：把 mul 乘进 res。
mul *= mul：位权平方（base^1 → base^2 → base^4 → …）。
t >>= 1：去除最低位。
复杂度 O(log t)，因为 k 可能很大（如 k ≤ 1e18），直接循环不行，必须快速幂

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int mod = 1e9+7;

inline ll mul(ll a, ll b) {
    a %= mod; b %= mod;
    return a*b%mod;
}
inline ll ksm(ll base, ll t) {
    base %= mod;
    ll res = 1, mul = base;
    while (t) {
        if (t&1) { res*=mul; res%=mod; }
        mul*=mul; mul%=mod;
        t>>=1;
    }
    return res;
}

ll n, k;
int main() {
    fast;
    cin >> n >> k;
    if (!n) { cout << 0 << '\n'; return 0; }
    cout << ((mul(n,ksm(2,k+1))-ksm(2,k)+1)%mod+mod)%mod << '\n';
    return 0;
}