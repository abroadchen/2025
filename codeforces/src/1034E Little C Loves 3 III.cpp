//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
P(x) = x 的二进制中 1 的个数（popcount）
这是XOR 卷积（Walsh-Hadamard 变换）‍的标准实现：

外层 i 是当前合并的块大小（1, 2, 4, ...）。
中层 j 遍历每个"对偶块"。
内层对块内每个位置做：x[后半] += x[前半] * t。
t = 1 时是正变换，t = -1 时是逆变换（因为 t 控制加减号）。这是"仨目标 WH 变换"。

输入的是两个长度相同的 01 串/四进制串 s、t，n 从输入的是「指数」变成实际长度 2^n
s[i] & 15 取 s[i] 的低 4 位（把字符当成数值，可能是 0-3 之类的四进制位）。
把它左移 P(i)<<1 位 = 左移 2*P(i) 位，即按"下标 i 的二进制中 1 的个数 × 2"来分桶存放。
于是 a、b 中每一位的取值被"压缩"到与 popcount 对应的不同位区间，从而把"关联 popcount 的卷积"变成普通 XOR 卷积
逆变换后，每个位置 c[i] 的结果按 popcount 分布在对应位段上，这里通过 >> (P(i)<<1) 把该位段移下来，再 & 3 取低两位输出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define ll long long
using namespace std;

constexpr int N = 1<<21;

int P(int x) { return __builtin_popcount(x); }

int n;
void fwt(ll *x, int t) {
    for (int i = 1; i < n; i<<=1)
        for (int j = 0; j < n; j += i<<1) rep(k,i)
            x[i+j+k] = x[i+j+k] + x[j+k]*t;
}

string s, t;
ll a[N], b[N], c[N];
int main() {
    fast;
    cin >> n; n = 1<<n; cin >> s >> t;
    rep(i,n) a[i] = (s[i]&15ll)<<(P(i)<<1), b[i] = (t[i]&15ll)<<(P(i)<<1);
    fwt(a,1), fwt(b,1);
    rep(i,n) c[i] = a[i]*b[i];//频域逐点相乘
    fwt(c,-1);
    rep(i,n) cout << ((c[i]>>(P(i)<<1))&3);
    return 0;
}