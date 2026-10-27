//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
c[i][j] 是组合数 C(i,j)，用杨辉三角递推预计算，取模 998244353。
这些组合数用于后面"从可用位置里选取 a[i]−1 个成员"的方案数
f[0]=1：空前缀方案数为 1。
对每个端点 i，枚举"从哪个位置 j 开始的一组/段"（j < i），条件是：位置 j 是某个锚点（a[j]>0）且它要求的成员数 a[j]-1 不超过它右侧到 i 之间可用位置数 i-j-1。
若成立，那么这段 [j..i] 可以作为一个合法段：方案数 =（前 j-1 部分的方案 s[j-1]）×（从 i−j−1 个可选位置里选 a[j]−1 个的选法 c[i-j-1][a[j]-1]）。
累加到 f[i]。
s[i] = s[i-1] + f[i]：s[i] 是 f[0..i] 的前缀和，用作下一层的 s[j-1]。
DP 含义：f[i] = 恰好以 i 作为某段的右端点/结尾时，前缀 [1..i] 的划分方案数；s[i] 是所有以 ≤i 结尾的累计方案数
s[n] 是所有可能划分方案总数，减去 1（去掉 f[0] 那一个空方案）即最终答案
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e3+5, mod = 998244353;

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int n, a[N];
ll f[N], s[N], c[N][N];
int main() {
    read(n);
    rep(i,n) read(a[i]);
    f[0] = s[0] = 1; c[0][0] = 1;
    rep(i,n) {
        c[i][0] = 1;
        rep(j,i) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
    }
    rep(i,n) {
        rep(j,i-1) if (a[j] > 0 && a[j]-1 <= i-j-1) f[i] = (f[i]+s[j-1]*c[i-j-1][a[j]-1]%mod) % mod;
        s[i] = (s[i-1] + f[i]) % mod;
    }
    write((s[n]-1+mod) % mod), putchar('\n');
    return 0;
}