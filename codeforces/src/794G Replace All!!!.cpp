//
// Created by Psy.C on 2026/9/16.
//
/**
mu[tp]：莫比乌斯函数 μ，存在 mod 意义下（-1 表示成 mod-1）。
vis/p/tp：线性筛质数辅助
mu[1]=1。
质数 μ = -1（mod 下 mod-1）。
欧拉筛：若 i%p[j]==0，则 t 含 p[j] 的平方 → μ=0；否则 μ[t] = -μ[i]（即 mod - mu[i]）
mo(x)：等价于 x %= mod（因为 x<2*mod 时只减一次）。
ksm：快速幂算 a^b % mod（用于阶乘逆元、2 的幂）
标准预处理阶乘 fac 和逆元 ifac，C(n,m) 组合数，非法情况返回 0
用于计算"在若干 ? 位置填 A/B 使得某种差值为 d 的方案数"
sieve(N-1) 预计算 μ 到 N-1。
阶乘、阶乘逆元（费马小定理 + 递推）。
pw[i] = 2^i mod 的预处理
读入 s、t、n。a、b 是两串长度。
cnts[?]：统计 s 中非 ? 字符里是/不是 A 的个数。s[i]=='A' 为真→1（索引 1 表示"A"的个数），否则 0（索引 0 表示"非 A 即 B"的个数）。
同理 cntt 统计 t
当长度相等，先做逐位匹配检查：
若某位 s、t 都不是 ? 且不相等 → 该位永远无法匹配，flg=0。
若某位两边都是 ? → cnt++（记这种双通配位置个数）。
若 flg（无必然冲突）：
ans 初始值是"完全相等匹配"的方案数：(pw[n+1]-2)^2 * pw[cnt]。
pw[n+1]-2 = 2^(n+1)-2，这通常是"长度为 1..n 的某种串的匹配数"（比如两串完全一致的对数），平方表示两串都要；pw[cnt] 是 cnt 个双通配位的自由填法（每个 2 种）
tot：差值为 0 的总填法数，减去刚才已经算进 ans 的"完全相等"部分（flg 时减 pw[cnt]），避免重复计数
对每个 p，累加 mu[p] * 2^(t/p) 到 sum[t]。
sum[t] = Σ_{p|t} μ(p) * 2^(t/p)，即经典反演和（把"长度为 n 周期 t"的匹配数整理）
最后对每个长度 i 累加：(n/i)^2 * sum[i] * tot 是"该长度下非完全相等的匹配数"。
这一整块是 a==b 时，统计"两个等长串所有前缀/长度 ≤n 的匹配方案"的莫比乌斯反演求和
枚举差值 i（两串"匹配起点/对齐偏移"）。
d = i + a - b：另一个导出差（来自两串长度差）。
calc(...) 算出对应差 i 的填法数 tot；为 0 跳过。
i*d <= 0 跳过（要求 i、d 同号才有效）。
x = |i|/gcd, y=|d|/gcd：约分。
up = min(n/x, n/y)：能对齐的最大长度。
ans += tot * (2^(up+1)-2)：累加该差值下所有长度的匹配方案。
这段处理不同偏移/不等声明时，基于 i、d 的 gcd 约分来枚举有效对齐长度 n 的贡献

a：s 中可填"某一类"的候选位置数（＝总长 - 已确定的某值数量，即 a-cnts[0] 是"可自由填 A/B 的位置"）。
b：t 中对应候选位置数。
cnta/cntb：另一类已确定计数。
d：两种字符差值的需求。
该公式用组合数计算"在 a 个空位中选若干个，使整体两种字符的计数差为 d"的填法数——是典型的"排球组合 + 通配符计数"的组合恒等变形


 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 4e6+10, mod = 1e9+7;

int mu[N], vis[N], p[N], tp;
void sieve(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) p[++tp] = i, mu[i] = mod-1;
        for (int j = 1, t; j <= tp && p[j]*i <= n; ++j) {
            t = i*p[j];
            vis[t] = 1;
            if (i%p[j] == 0) { mu[t] = 0; break; }
            mu[t] = mod - mu[i];
        }
    }
}
inline void mo(int& x) { x >= mod ? x -= mod : x; }
inline int ksm(int a, int b) {
    int ret = 1;
    while (b) {
        if (b&1) ret = 1ll*ret*a%mod;
        a = 1ll*a*a%mod;
        b >>= 1;
    }
    return ret;
}

int fac[N], ifac[N];
inline int C(int n, int m) {
    if (n < m || m < 0) return 0;
    return 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}
inline int calc(int a, int b, int cnta, int cntb, int d) {
    if (a < 0 || b < 0) return 0;
    return C(a+b-cnta-cntb, a+d-cntb);
}

int pw[N], cnts[2], cntt[2], sum[N];
char s[N], t[N];
int main() {
    pw[0] = fac[0] = ifac[0] = 1; sieve(N-1);
    for (int i = 1; i < N; ++i) fac[i] = 1ll*fac[i-1]*i%mod;
    ifac[N-1] = ksm(fac[N-1], mod-2);
    for (int i = N-2; i; --i) ifac[i] = 1ll*ifac[i+1]*(i+1)%mod;
    for (int i = 1; i < N; ++i) pw[i] = 2ll*pw[i-1]%mod;
    int a, b, n, ans = 0;
    scanf("%s%s%d", s+1, t+1, &n); a = strlen(s+1), b = strlen(t+1);
    for (int i = 1; i <= a; ++i)
        if (s[i] != '?') ++cnts[s[i]=='A'];
    for (int i = 1; i <= b; ++i)
        if (t[i] != '?') ++cntt[t[i]=='A'];
    if (a == b) {
        int flg = 1, cnt = 0;
        for (int i = 1; i <= a && flg; ++i) {
            if (s[i] != '?' && t[i] != '?' && s[i] != t[i]) flg = 0;
            else if (s[i] == '?' && t[i] == '?') ++cnt;
        }
        if (flg) ans = 1ll*(pw[n+1]-2)*(pw[n+1]-2)%mod*pw[cnt]%mod;
        int tot = (calc(a-cnts[0], b-cntt[0], cnts[1], cntt[1], 0)+mod-
            (flg?pw[cnt]:0))%mod;
        for (int p = 1; p <= n; ++p)
            for (int t = p; t <= n; t += p)
                mo(sum[t] += 1ll*mu[p]*pw[t/p]%mod);
        for (int i = 1; i <= n; ++i)
            mo(ans += 1ll*(n/i)*(n/i)%mod*sum[i]%mod*tot%mod);
    }
    for (int i = -a; i <= b; ++i) {
        if (!i) continue;
        int tot = calc(a-cnts[0], b-cntt[0], cnts[1], cntt[1], i), d = i+a-b;
        if (!tot) continue;
        if (1ll*i*d <= 0) continue;
        int x = abs(i), y = abs(d), p = __gcd(x, y); x = x/p; y = y/p;
        int up = min(n/x, n/y);
        mo(ans += 1ll*tot*(pw[up+1]-2)%mod);
    }
    printf("%d\n", ans);
    return 0;
}