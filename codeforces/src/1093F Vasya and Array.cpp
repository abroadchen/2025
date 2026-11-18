//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
l[i][j]：第 i 位之前（含）连续多少个位置值为 j（即到 i 为止、值为 j 的连续后缀长度）。
s[i]：长度为 i 的合法前缀总数。
f[i][j]：第 i 位为 j 的最后一位、合法前缀方案数
若第 i 位能填 j（固定为 j 或自由 -1），则连续 j 的后缀长度 = 上一处的 +1；否则为 0（初始 0）。
这用于后面判断：若当前以 j 结尾，已连续 len 个 j，则需剔除非法方案
该位置要么值固定、要么自由。若当前位置不能填 j，跳过
忽略约束时，第 i 位填 j 的方案 = 前 i-1 位任意合法方案数。但这样会把连续 len 个 j 的非法情况也计入，须剔除
当以 i 结尾连续 j 达到 len 时，本次接 j 会导致 i-len+1..i 全部是 j —— 非法。

需要从 s[i-1] 里减去"会导致这种非法连续"的方案数：

具体地，减去 s[i-len]：即前 i-len 位是安全的、但 i-len+1..i 这段补 len 个 j 会造成非法。但这里面多扣了那些 i-len 位本身以 j 结尾（即 i-len 位值为 j）的情况——因为那种情况下前面更早处已经因为 l[i-len][j] 处理过，不能重复算非法，所以要加回 f[i-len][j]。
即：f[i][j] = s[i-1] - s[i-len] + f[i-len][j]（经典"容斥式"递推，用来拆掉恰好以第 i-len+1 位起、连续 len 个 j 的非法串，同时保留第 i-len 位本身为 j 的合法延续）
s[i] 累加所有以第 i 位结尾、末位为任意 j 的方案数
输出长度为 n 的合法方案总数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
#define ll long long
using namespace std;

constexpr int N = 1e5+10, M = 110, mod = 998244353;

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int n, k, len;
ll a[N], l[N][M], s[N], f[N][M];
int main() {
    fast;
    read(n); read(k); read(len);
    rep(i,n) read(a[i]);
    rep(i,n) rep(j,k) if (a[i] == j || a[i] == -1) l[i][j] = l[i-1][j] + 1;
    s[0] = 1;//空前缀只有 1 种（起算点）
    rep(i,n) rep(j,k) {
        if (a[i] != j && a[i] != -1) continue;
        f[i][j] = s[i-1];
        if (l[i][j] >= len) f[i][j] = ((f[i][j]-s[i-len]+mod)%mod+f[i-len][j])%mod;
        s[i] = (s[i] + f[i][j])%mod;
    }
    cout << s[n];
    return 0;
}