//
// Created by Psy.C on 2026/9/29.
//
/**
inv2 = 5e8+4 是 2 在模 1e9+7 下的逆元（逆 FWT 要除以 2）。
MAXN 足够容纳 N = 2^(n+1)，n 最大到 20，即 N ≤ 2^21。
XOR（异或）FWT 蝴蝶变换，每层 mid 把区间分成两半做 (x+y, x-y)。正向变换用于把点乘关系转化为卷积关系
与正向对称，从大到小合并，多乘 inv2（逆变换要除长度，这里按 2 逐层除）。作用是把点乘还原回原域
读入 n 和一个 0/1 字符串 str（长度 2^n，对应某个集合的指示向量）。
N = 2^(n+1)，pw 存 2 的幂，pc[i] 存 i 的二进制中 1 的个数（popcount）
把字符串装入 f[0 .. 2^n-1]。
FWT → 平方 → 逆 FWT：这一条链路等价于求 f 与自身的 XOR 卷积 g = f ⊗ f，其中
g[k] = Σ_{i xor j = k} f[i]·f[j]。
即统计"两两异或得到某个值的对数"
对每个结果值 i，f[i] 是可造成该异或值的方案数，乘上 2^(n - popcount(i))（通常来自某种"自由位"计数，比如集合内部还可以任意组合的部分）。
累加后整体 ×3——这一步对应题目里某个"三倍"计数（常见于 CF 某道题中最终答案要乘 3，比如有三种轮换/某种结构）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int MAXN = (1<<21)+3, mod = 1e9+7, inv2 = 5e8+4;

int N;
inline void fwt(int f[]) {
    for (int mid = 1; mid < N; mid <<= 1)
        for (int i = 0; i < N; i += mid<<1)
            for (int j = 0; j <= mid-1; ++j) {
                int x = f[i+j], y = f[i+mid+j];
                f[i+j] = (x+y)%mod;
                f[i+mid+j] = (x+mod-y)%mod;
            }
}

inline void ifwt(int f[]) {
    for (int mid = N>>1; mid; mid >>= 1)
        for (int i = 0; i < N; i += mid<<1)
            for (int j = 0; j <= mid-1; ++j) {
                int x = f[i+j], y = f[i+mid+j];
                f[i+j] = 1ll*(x+y)*inv2%mod;
                f[i+mid+j] = 1ll*(x+mod-y)*inv2%mod;
            }
}

int n, pw[MAXN], pc[MAXN], f[MAXN];
char str[MAXN];
int main() {
    fast;
    cin >> n >> str; N = 1<<(n+1); pw[0] = 1;
    for (int i = 1; i <= MAXN-1; ++i)
        pw[i] = 2ll*pw[i-1]%mod, pc[i] = pc[i>>1] + (i&1);
    for (int i = 0; i <= (1<<n)-1; ++i) f[i] = str[i] - '0';
    fwt(f);
    for (int i = 0; i <= N-1; ++i) f[i] = 1ll*f[i]*f[i]%mod;
    ifwt(f);
    int ans = 0;
    for (int i = 0; i <= N-1; ++i)
        (ans += 1ll*f[i]*pw[n-pc[i]]%mod) %= mod;
    ans = 3ll*ans%mod;
    cout << ans << '\n';
    return 0;
}