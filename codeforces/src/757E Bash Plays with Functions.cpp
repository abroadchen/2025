//
// Created by Psy.C on 2026/9/3.
//
/**
p[]：存储筛出来的质数表，cp 是质数个数。
mp[x]：记录 x 的最小质因子。
内层循环用 p[j] 去筛 i*p[j]，一旦 p[j] 达到 i 的最小质因子就 break，保证每个合数只被其最小质因子筛一次，做到线性复杂度。
mp 的作用：后面要用它来快速做质因数分解（不断除以最小质因子即可）
快速实现 (x) % mod，因为这里加一次不会溢出，直接判断是否 ≥ mod 再减一下即可，比 % 快

对一个质因子指数
c
c 需要乘
f
[
m
]
[
c
]
f[m][c]。这个二维数组在组合数学里通常是 ‍“把
c
c 个不可区分的质因子放到
m
m 个不同‘槽’（位置）里，允许空槽”的方案数 =
C
(
c
+
m
−
1
,
  
m
−
1
)
C(c+m−1,m−1)（隔板法）‍。代码用二维 DP 递推这张表（f[0][j]=2、f[i][0]=1 是边界，pf[j] 是第 j 列的前缀和做累加优化）。也就是说这题的答案实质是：对每个质因子指数
c
c，求某种“分配到
m
m 个位置”的组合数，再累乘

用 mp[n] 反复分解 n 的质因子：

取出 n 当前的最小质因子 pr = mp[n]；
内层循环把 n 里所有的 pr 都除掉，并计数 c（即 pr 的指数）；
外层循环结束时，把这项组合数 f[m][c] 乘进 ans（1ll* 防止溢出），并把 c 归零；
直到 n == 1，所有质因子分解完毕。
也就是说，对 n 的每一种质因子
p
c
p
c
 ，把
f
[
m
]
[
c
]
f[m][c] 累乘进答案。


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+7, M = 21, mod = 1e9+7;

int mp[N], p[N], cp;
inline void sieve() {
    for (int i = 2; i < N; ++i) {
        !mp[i] && (p[++cp] = mp[i] = i);
        for (int j = 1; i*p[j] < N; ++j) {
            mp[i*p[j]] = p[j];
            if (mp[i] == p[j]) break;
        }
    }
}

inline int add(const int& x) {
    return x >= mod ? x - mod : x;
}

int pf[M], f[N][M];
inline void prework() {
    sieve(), pf[0] = 1;
    for (int i = 1; i < N; ++i) f[i][0] = 1;
    for (int i = 1; i < M; ++i)
        f[0][i] = 2, pf[i] = pf[i-1] + 2;
    for (int i = 1; i < N; ++i)
        for (int j = 1; j < M; ++j)
            f[i][j] = pf[j], pf[j] = add(pf[j-1] + f[i][j]);
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int m, n, ans;
inline void solve() {
    rd(m), rd(n), ans = 1;
    for (int c = 0, pr; n != 1; ans = 1ll*ans*f[m][c]%mod, c = 0)
        for (pr = mp[n]; n % pr == 0; n /= pr)
            ++c;
    cout << ans << '\n';
}

int T;
int main() {
    fast;
    for (prework(), rd(T); T; --T) solve();
    return 0;
}