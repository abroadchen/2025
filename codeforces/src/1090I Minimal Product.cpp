//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
chk_mn(a,b) / chk_mx(a,b)：原地求 min/max
N 数组上限 1e7。
mod = 2^32，用于模运算。
inf ≈ LLONG_MAX - 1，作为"无穷大"哨兵
带符号的 32 位模加法（处理负数换正）
a[i] 最终数组（ll）。
b[i] 原始 ui（unsigned int，即 32 位无符号）伪随机数
读 n、区间 [l,r]、参数 x,y,z、b[0],b[1]
生成递推伪随机序列 b[3..n]。由于 b 是 ui（32 位），%mod(2^32) 实际会被无符号截断自然完成，无需显式取模；但这里显式写了 %mod 也无妨
把每个 b[i] 映射到区间 [l, r]：取余长度 + l，得到数组 a[i]
维护前缀最小值 mn。
遍历到 i 时，若已有比 a[i] 更小的 mn，则候选乘积 mn*a[i] 尝试更新 ans。
只要 a[i] 前面存在更小的值，"更小 × 更大一点"就能得到更小的积（正数相乘越小、负数×正数也更小）
维护后缀最大值 mn（从后往前扫，记录到当前为止的最大值）。
若当前 a[i] 比 max 小，候选 mn*a[i]（max × 当前小值）尝试更新 ans。
这专门覆盖 "一个很大的正数 × 后面一个较小的(可为负)数"，因为反向扫描能捕捉到"大正在前、小负在后"这种正向扫描捕捉不到的配对。
两种扫描合起来，保证"任意 i<j 的最小乘积"都能被某一方向枚举到（正乘/负乘都被覆盖）
若 ans 没被更新过（仍是 inf），说明找不到任何 i<j 的配对，即 n < 2，输出 IMPOSSIBLE。
否则输出最小乘积

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define chk_mn(a,b) (a=(a<b?a:b))
#define chk_mx(a,b) (a=(a>b?a:b))
#define ll long long
#define ui unsigned int
using namespace std;

constexpr int N = 1e7+10;
constexpr ll mod = 1ll<<32, inf = 9223372036854775806;

ll add(ll x, ll y) {
    if (x + y < 0) return x + y + mod;
    return x + y >= mod ? x + y - mod : x + y;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n;
ll l, r, x, y, z, a[N];
ui b[N];
void solve() {
    n = rd(), l = rd(), r = rd(), x = rd(), y = rd(), z = rd();
    b[1] = rd(), b[2] = rd();
    for (int i = 3; i <= n; i++) b[i] = (b[i-2]*x%mod+b[i-1]*y%mod+z)%mod;
    for (int i = 1; i <= n; i++) a[i] = b[i]%(r-l+1) + l;
    ll mn = inf, ans = inf;
    for (int i = 1; i <= n; i++) {
        if (mn < a[i]) chk_mn(ans, mn*a[i]);
        chk_mn(mn, a[i]);
    }
    mn = -inf;
    for (int i = n; i >= 1; i--) {
        if (a[i] < mn) chk_mn(ans, mn*a[i]);
        chk_mx(mn, a[i]);
    }
    if (ans == inf) cout << "IMPOSSIBLE\n";
    else cout << ans << '\n';
}

int main() {
    fast;
    for (int T = rd(); T; T--, solve()) {}
    return 0;
}