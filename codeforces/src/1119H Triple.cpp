//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
mod = 998244353（常用质数），inv = (mod+1)/2 即 mod 下 2 的逆元（因为 (mod+1)/2×2 ≡ 1 mod mod）
外层 for(i) 是蝴蝶宽度（1,2,4…翻倍）。
内层做 ad(x,y) 与 ad(x, mod-y)（即 x-y 的模写法）。
末尾若 c≠1，整体乘上 c——用于逆变换（乘 1/2^k）
n：行数；kk：要查询的异或值范围（输出 [0, 2^kk)）；m=3（三元/三变量）；k=17（值域 2^17）。
d[3]：容斥里的系数/目标数组。
w[8]、z[8][N]、h[8][L]：8 个掩码下各自的计数数组
对 8 个掩码 i，w[i] = 按位配对后 ±d 之和——这是容斥/子集构造的权重
对每个掩码 t（8 个），每一行算"取掩码对应的列异或结果" z[t][i]，统计频次到 h[t]，再各做一次正向 FWT
在频域里，把 8 个掩码结果按权重 w[i]^c[i] 乘起来，构成拼接结果 g[p]
对 g 做逆 FWT 回到"时域"，输出前 2^kk 个值（即异或值为 0..2^kk-1 的计数）

j | i 就是在 j 的第 i 位上置 1，于是 j 与 j|i 恰好构成"该位为 0 / 为 1"的一对对称位置，
对应异或卷积变换矩阵 [[4]]。continue 意味着只处理每一对中的一半（j&i==0 那半），
另一半在 j|i 处同时更新，避免重复
掩码 t 的第 j 位为 1  t & (1<<j)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 0; i < (n); i++)
using namespace std;

constexpr int N = 1e5+5, mod = 998244353, inv = (mod+1)/2;
int ad(int a, int b) {//取模加法（省 %）
    a += b;
    if (a >= mod) a -= mod;
    return a;
}
void add(int &a, int b) {//原地版本
    a += b;
    if (a >= mod) a -= mod;
}
int ksm(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = 1ll*res*a%mod;
        a = 1ll*a*a%mod;
        b >>= 1;
    }
    return res;
}

void fwt(int *f, int v, int c) {
    for (int i = 1; i < v; i <<= 1) rep(j,v) {
        if (j&i) continue;
        int x = f[j], y = f[j|i];//j 与 j|i 是一对（相差一个位 i）
        //变换公式 [1,1] 变换公式 [1,-1]
        f[j] = ad(x,y), f[j|i] = ad(x, mod-y);
    }
    if (c != 1) rep(i,v) f[i] = 1ll*f[i]*c%mod;
}

int n, kk, m, k, d[3], w[1<<3], a[N][3], z[1<<3][N], h[1<<3][1<<17], c[N], g[1<<17];
void solve() {
    cin >> n >> kk; m = 3, k = 17;
    rep(i,m) cin >> d[i], d[i] %= mod;
    rep(i,1<<3) rep(j,m) {
        if (i&(1<<j)) add(w[i],mod-d[j]);
        else add(w[i],d[j]);
    }
    for (int i = 1; i <= n; i++) rep(j,m) cin >> a[i][j];
    rep(t,1<<3) {
        for (int i = 1; i <= n; i++) rep(j,m) if (t&(1<<j)) z[t][i] ^= a[i][j];
        for (int i = 1; i <= n; i++) h[t][z[t][i]]++;
        fwt(h[t],1<<17,1);
    }
    rep(p,1<<17) {
        rep(t,1<<3) c[t] = h[t][p];//取 8 个 FWT 结果在位置 p 的值
        fwt(c,1<<3, ksm(inv,m));//对 8 个再做一次小 FWT（逆）
        g[p] = 1;
        rep(i,1<<3) g[p] = 1ll*g[p]*ksm(w[i],c[i])%mod;
    }
    fwt(g,1<<17,ksm(inv,k));
    rep(i,1<<kk) cout << g[i] << ' ';
}

int main() {
    fast;
    solve();
    return 0;
}