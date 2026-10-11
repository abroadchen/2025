//
// Created by Psy.C on 2026/10/11.
//
/**
标准求欧拉函数 φ(n)：对 n 分解质因数，res = res * (1 - 1/p)。
先枚举到 sqrt(n) 找质因子，处理完所有该因子后把 n 里的它全部除尽；最后剩下的 n > 1 也是一个质因子，再处理一次。
返回 φ(n)，即小于等于 n 且与 n 互质的正整数个数。
这个函数会反复被用来生成 φ(m), φ(φ(m)), φ(φ(φ(m)))... 的降幂链（见主函数里的 while）
如果真实指数 b < φ(m)，结果保持为真实值（不会无谓加 mod）；
如果 b ≥ φ(m)，则得到 a^{... + φ(m)}，正好对应扩展欧拉定理的第二种情形。
关键点：res%mod+mod 这个操作让返回值始终带着"是否超过 mod"的信息（值域是 [mod, 2mod) 或 [0, mod)），从而在递归里能正确判断需要加 φ 的分支。

这是本题之所以成立的核心：普通的 %mod 会丢失指数是否足够大的信息，无法在递归降幂时判断该用哪条扩展欧拉分支。这个"加模"写法是幂塔题目的标准解法
从 m 出发，反复取欧拉函数，形成链：
m → φ(m) → φ(φ(m)) → ... → 1
mp[x] = phi(x) 把每一步的下一层模数记进 map（x 作为键，φ(x) 作为值）。
最终 x 变成 1，把 mp[1]=1 兜底。
这样在递归 dfs 里，遇到某个模数 p 时能直接 O(log M) 拿到下一层 φ(p)，无需重复计算欧拉函数。
这个欧拉降幂链长度是 O(log m) 的（欧拉函数下降很快，通常几十层就到 1），所以总复杂度约为 O(n·log m · log a)
读入 n 个底数 a[1..n]。
读入 q 个询问，每询问区间 [l, r]，输出该区间构成的幂塔模 m 的结果
x：当前处理到数组下标 x（从 l 到 r）。
p：当前模数（第一层是 m，之后每层换成对应 φ）。
终止条件：
x == r+1：已经超出区间右端，指数塔到底，返回 1（空指数塔值约定为 1）。
p == 1：模数为 1 时任何数 mod 1 都是 0，返回 1 作为占位（这里返回 1，是幂塔约定/避免 0 影响后续乘方）。
递归计算指数：
t = dfs(x+1, mp[p])：先递归算出指数部分（即 a_{x+1}^{...} 在模 φ(p) 下，用扩展欧拉对应模数的值）。
return ksm(a[x], t, p)：用 a[x] 的 t 次幂（扩展欧拉快速幂，模 p）作为当前层的值。
递归顺序：从 a[l] 开始，一直递归到最内层 a_r（此时 x == r+1 返回 1），再从内到外逐层做 ksm(a[x], 内层结果, 当前模数)，最终回到第一层 p=m


预处理 m 的欧拉降幂链存进 mp，供递归查表。
dfs(x, p) 递归：最内层指数塔底（x==r+1）返回 1；每层用 ksm(a[x], t, p) 计算该层幂，其中指数 t 来自更深一层的递归结果，且模数自动降到 φ(p)。
ksm 的 "超过 mod 就 +mod" 技巧，使结果正确匹配扩展欧拉定理是否需要加 φ(p) 的分支，从而保证在模数较大、指数较大时仍正确。
复杂度：约 O((n+q)·log m · log a)，能高效处理大量查询，这正是设 N=1e5、用预处理欧拉链+快速幂的原因
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define rep(i,j,k) for(int i=j; i<=k; ++i)
using namespace std;

constexpr int N = 1e5+5;

int phi(int n) {
    int t = sqrt(n), res = n;
    rep(i,2,t) if (n%i == 0) {
        res /= i; res *= i-1;
        while (n%i == 0) n /= i;
    }
    if (n > 1) res /= n, res *= n-1;
    return res;
}
int ksm(int a, int b, int mod) {
    int res = 1;
    while (b > 0) {
        if (b&1) {
            res = res*a;
            if (res >= mod) res=res%mod+mod;
        }
        a = a*a;
        if (a >= mod) a=a%mod+mod;
        b>>=1;
    }
    return res;
}

int r, a[N];
map<int,int> mp;
int dfs(int x, int p) {
    if (x == r+1 || p == 1) return 1;
    int t = dfs(x+1, mp[p]);
    return ksm(a[x], t, p);
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

signed main() {
    fast;
    int n = rd(), m = rd(), q, l;
    int x = m;
    while (x != 1) mp[x] = phi(x), x = mp[x];
    mp[x] = 1;
    rep(i,1,n) a[i] = rd();
    q = rd();
    while (q--) {
        l = rd(), r = rd();
        cout << dfs(l, m)%m << '\n';
    }
    return 0;
}