//
// Created by Psy.C on 2026/10/4.
//
/**
把 vector<ll> 当作多项式的系数（A[i] 表示 x^i 的系数）。

A + B：多项式加法，对应位数系数相加（取模）。
A * B：多项式卷积（乘法）。结果长度为 n+m-1，C[i+j] += A[i]*B[j]。这是 O(n·m) 的朴素卷积。
A % B：多项式长除法取余（模一个首一多项式 B，B 最高次数为 m-1）。
若 A 次数低于 B，直接返回 A。
否则用 inv = B[m-1] 的逆元（B 最高次系数），从高次往低次做带形除法，把 A 降到次数 < m-1。
这段就是"多项式对 g 取模"，即在一个商环 F_p[x]/(g(x)) 中运算。


构建多项式 g：g[M]=1，然后对每个 c，把 x^{M-c} 的系数减 1。这给出 g(x) = x^M - Σ x^{M-c_i}，是一个首一的次数为 M 的多项式，作为"模"（特征多项式）。
这看起来像线性递推/特征多项式：比如斐波那契递推 F_n = F_{n-1}+F_{n-2} 对应的特征多项式 x^2 - x - 1。这里 b 个 c 就是递推的"回退步长"，f 个 p 是初始项的贡献位置
第一部分：ksm({0,1}, p[i], g) 算的是 x^{p[i]} mod g。多项式 {0,1} 就是 x（第 0 位系数 0、第 1 位系数 1）。累加 f 个得到 x = Σ_{i=1}^{f} x^{p_i} mod g。

第二部分：x = ksm(x, n, g) —— 在商环里求 (Σ x^{p_i})^n mod g。

第三部分：巧妙的移位。x.resize(x.size()+M-1) 扩容，然后把整个系数右移 M-1 位（x[i] = x[i-M+1]），低 M-1 位补 0。这等价于乘以 x^{M-1}。

最后：(x%g)[M-1] 再对 g 取余，取出结果中 x^{M-1} 的系数，模 mod 输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 15, M = 255, mod = 1e9+7;

ll ksm(ll a, ll b) {
    ll c = 1;
    while (b) {
        if (b&1) c=c*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return c;
}

vector<ll> operator+(vector<ll> A, vector<ll> B) {
    int m = B.size(); A.resize(max((int)A.size(), m));
    for (int i = 0; i < m; ++i) A[i] = (A[i]+B[i])%mod;
    return A;
}
vector<ll> operator*(vector<ll> A, vector<ll> B) {
    int n = A.size(), m = B.size();
    vector<ll> C(n+m-1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            C[i+j] = (C[i+j]+A[i]*B[j]%mod)%mod;
    return C;
}
vector<ll> operator%(vector<ll> A, vector<ll> B) {
    int n = A.size(), m = B.size();
    if (n < m) return A;
    ll inv = ksm(B[m-1], mod-2);
    for (int i = n-1; i >= m-1; --i)
        for (int j = 0; j < m; ++j)
            A[i-m+1+j] = (A[i-m+1+j]-A[i]*inv%mod*B[j]%mod+mod)%mod;
    A.resize(m-1);
    return A;
}

//多项式版的快速幂
vector<ll> ksm(vector<ll> A, ll b, vector<ll> P) {
    vector<ll> C = {1};
    while (b) {
        if (b&1) C=C*A%P;
        A=A*A%P;
        b>>=1;
    }
    return C;
}

template <typename T>
T rd() {
    T f = 0, ch = 0; T x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int f, b, p[N];
ll n;
int main() {
    fast;
    f = rd<int>(), b = rd<int>(), n = rd<ll>();
    for (int i = 1; i <= f; ++i) p[i] = rd<int>();
    vector<ll> g(M+1); g[M] = 1;
    for (int i = 1; i <= b; ++i) {
        int c = rd<int>();
        g[M-c] = (g[M-c] - 1 + mod)%mod;
    }
    vector<ll> x;
    for (int i = 1; i <= f; ++i) x = x + ksm({0,1}, p[i], g);
    x = ksm(x, n, g);
    x.resize(x.size()+M-1);
    for (int i = (int)x.size()-1; i >= M-1; --i) x[i] = x[i-M+1];
    for (int i = 0; i < M-1; ++i) x[i] = 0;
    cout << (x%g)[M-1] << '\n';
    return 0;
}