//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
值域：1..M-5，即 1..200。
-1 表示该位置可为任意取值（1..200）‍，需要枚举统计。
f[i][j][0/1]：前 i 个位置、第 i 位取 j，且第 i 位是当前所形成"递减/递增"块的某种归属状态的方案数
若第 1 位未知（-1），则 j 取 1..200 每个值都是 1 种方案（写进状态 0）。
若第 1 位已知，则只有该值 j = a[1] 的状态 0 为 1
pre[j][k] = Σ_{t≤j} f[i][t][k]，suf[j][k] = Σ_{t≥j} f[i][t][k]。这样 O(1) 取"所有 ≤j 或 ≥j 的状态和"，避免每步 O(M) 枚举。
对每个位置 i（i≥2）：

若第 i 位未知 a[i]==-1，对每个 j
若第 i 位确定 a[i]==k，则只更新 j = k 的行，逻辑同上但 j 固定为 a[i]。

三个来源（含义猜测，取决于具体题意，多是与相邻位大小关系约束）：

f[i-1][j][0]+f[i-1][j][1]：前一位也取 j（相等，两个状态都能接）。
suf[j+1][1]：前一位取值 > j 且处于状态 1 —— 位 i 取 j 比前一位小（下降），仅状态1可接。
pre[j-1][0]+pre[j-1][1]：前一位取值 < j（位 i 比前一位大，上升），状态 0/1 都可接。
每个位置结束后重建 pre / suf 供下一步使用
答案只累加状态 1 在所有取值 j 上的方案数并取模
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define per(i,n) for (int i=n; i>=1; i--)
#define int long long
using namespace std;

constexpr int N = 1e5+5, M = 205, mod = 998244353;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int n, a[N], f[N][M][2], pre[M][2], suf[M][2], ans;
signed main() {
    fast;
    n = rd();
    rep(i,n) a[i] = rd();
    if (a[1] == -1) rep(i,M-5) f[1][i][0] = 1; else f[1][a[1]][0] = 1;
    rep(j,M-5) {//前缀和：j' ≤ j 的 f[1][j'][0]
        pre[j][0] = (pre[j-1][0] + f[1][j][0]) % mod;
        pre[j][1] = (pre[j-1][1] + f[1][j][1]) % mod;
    }
    per(j,M-5) {//后缀和：j' ≥ j 的 f[1][j'][0]
        suf[j][0] = (suf[j+1][0] + f[1][j][0]) % mod;
        suf[j][1] = (suf[j+1][1] + f[1][j][1]) % mod;
    }
    for (int i = 2; i <= n; i++) {
        if (a[i] == -1) {
            rep(j,M-5) {
                f[i][j][1] = (f[i][j][1]+f[i-1][j][0]+f[i-1][j][1]) % mod;//与前一位同值 j：状态0/1都可传
                f[i][j][1] = (f[i][j][1]+suf[j+1][1]) % mod;//前一位取值 ≥ j+1 且处于状态1
                f[i][j][0] = (f[i][j][0]+pre[j-1][0]+pre[j-1][1]) % mod;//前一位取值 ≤ j-1（状态0或1）
            }
        } else {
            f[i][a[i]][1] = (f[i][a[i]][1]+f[i-1][a[i]][0]+f[i-1][a[i]][1]) % mod;
            f[i][a[i]][1] = (f[i][a[i]][1]+suf[a[i]+1][1]) % mod;
            f[i][a[i]][0] = (f[i][a[i]][0]+pre[a[i]-1][0]+pre[a[i]-1][1]) % mod;
        }
        rep(j,M-5) {//重建 pre / suf 供下一步使用。
            pre[j][0] = (pre[j-1][0] + f[i][j][0]) % mod;
            pre[j][1] = (pre[j-1][1] + f[i][j][1]) % mod;
        }
        per(j,M-5) {
            suf[j][0] = (suf[j+1][0] + f[i][j][0]) % mod;
            suf[j][1] = (suf[j+1][1] + f[i][j][1]) % mod;
        }
    }
    rep(i,M-5) ans = (ans + f[n][i][1]) % mod;
    write(ans);
    return 0;
}