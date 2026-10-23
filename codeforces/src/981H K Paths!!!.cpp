//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
手写 inc/dec：带有符号处理的加减法取模（a>>31&mod 用于把负数修正成模内非负）。
mul：64 位乘积取模。
ksm：快速幂，默认指数 mod-2（即求逆元）
lim：NTT 长度（2 的幂）。
标准迭代式 NTT（蝴蝶变换），使用模 998244353 的 2^23 次原根 3。
单位根预处理在 w[] 中。
f=1 正变换（蝶运算相加），f=-1 逆变换（先 reverse 再蝶运算，最后乘以长度逆元 mod-mod/lim）。
init(n) 构造 rev 置换和单位根表
对节点 u 的每个子节点 v，把多项式 a 的一块写成 {1, sz[v]}（即 [1*x^0 + sz[v]*x^1]），对应"这个子树选 0 个或选 sz[v] 个"。
用分治 + NTT 把所有子树的这些一次多项式逐层相乘，得到关于"从各子树中总共选取点数"的生成函数放进 a[]。
本质：a[] 成为多项式 ∏ (1 + sz[v]·x)（大致），其 [i] 项表示"选 i 个"的某种计数，供后面 calc 使用
mul(x)：给多项式 a 乘以 (1 + x·t) 的形式——即 a[i] += x·a[i-1]（从高次往低次更新）。
div(x)：除以 (1 + x·t)——a[i] -= x·a[i-1]（从低次往高次更新，是乘法的逆操作）。
用来在 ODT/分治过程中临时乘入或移除某个子树因子，避免重复计算
计算 r = Σ_{i=0}^{min(m,k)} a[i] · C(k, i)，其中 C(k,i)=fac[k]·ifac[k-i]·ifac[i]（这里写成 fac[k]·ifac[k-i]，省略了 ifac[i]？——注意这里 a[i] 可能已含有一部分组合系数，需看 poly 定义；简言之是"信息学里的组合数卷积求和"）。
本质：把多项式 a 在 i≤k 范围内与组合数 C(k,i) 点乘求和
dfs 做树形 DP：

计算子树大小 sz[u]，去掉父边转成有根树（e[v].erase 删除父指向）。
子树间合并：f[u] = Σ f[子]，并且把"不同子树间两两贡献"累进 ans（f[u]*f[v]，这里 f[u] 只统计已遍历子树的累计）。
将子节点按子树大小升序排序。
solve(u) 用 NTT 求出所有子树的"选点多项式"乘积放入 a。
m = e[u].size()，先用 mul(n-sz[u]) 乘入"(当前节点 u 除子树外的剩余、或等价的根方向补充)因子"。
按子树大小分组（相同 sz 的分一组）：
对该组，先 div(t) 临时移除这个大小的因子（恢复成"不含本组"的多项式），
统计本组所有子节点 f 之和 s，
ans += s · calc()（用不含本组的多项式去算组合求和，再乘上本组的贡献 s），
mul(t) 加回该因子。
最后 div(n-sz[u]) 移除前面乘入的因子，f[u] += calc()（当前节点自身的组合贡献），并清空 a。
核心思路：利用"乘/除单个一次因子"的 O(降) 技巧，遍历每个子树大小组时能在线性增量代价下重算多项式，避免重复全卷积。这是该题时间优化的关键。
读入 n, k。m = max(n,k)，预处理阶乘 fac 和逆元阶乘 ifac。
if (k==1) 特判直接输出 n(n-1)/2（此时只有一条对角线的特殊情况）。
读入树的 n-1 条边（无向，双向加边）。
dfs(1) 后输出 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define vi vector<int>
using namespace std;

constexpr int N = 1e5+10, mod = 998244353, M = 524289;

int inc(int a, int b) { return a += b - mod, a + (a>>31&mod); }
int dec(int a, int b) { return a -= b, a + (a>>31&mod); }
int mul(int a, int b) { return 1ll*a*b%mod; }
int ksm(int a, int k=mod-2) {
    int r = 1;
    for (; k; k>>=1, a=mul(a,a))
        if (k&1) r=mul(a,r);
    return r;
}

int lim, w[M], rev[M];
void init(int n) {
    lim = n, w[lim>>1] = 1;
    int g = ksm(3, mod/lim);
    for (int i = 1; i < lim; ++i) rev[i] = (rev[i>>1]>>1)|(i&1?lim>>1:0);
    w[lim>>1] = 1;
    for (int i = (lim>>1)+1; i < lim; ++i) w[i] = mul(w[i-1], g);
    for (int i = (lim>>1)-1; i; --i) w[i] = w[i<<1];
}

void ntt(int *a, int f) {
    if (!~f) reverse(a+1, a+lim);
    for (int i = 0; i < lim; ++i)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int i = 1; i < lim; i <<= 1)
        for (int j = 0, l = i<<1; j < lim; j += l)
            for (int k = 0, x; k < i; ++k)
                x=mul(a[i+j+k],w[i+k]),a[i+j+k]=dec(a[j+k],x),a[j+k]=inc(a[j+k],x);
    if (!~f) for (int i = 0, x=mod-mod/lim; i < lim; ++i) a[i] = mul(a[i], x);
}

vi e[N];
int a[M], sz[N];
void solve(int u) {
    int n = e[u].size()<<2;
    for (int i = 0; i < n; i += 4) a[i]=1, a[i+1]=sz[e[u][i>>2]];
    for (int i = 4; i < n; i <<= 1) {
        init(i);
        for (int j = 0; j+i < n; j += i<<1) {
            int *p = a+j, *q = p+i;
            ntt(p, 1), ntt(q, 1);
            for (int k = 0; k < i; ++k) p[k] = mul(p[k], q[k]);
            ntt(p, -1), memset(q, 0, i<<2);
        }
    }
}

int m;
void mul(int x) { for (int i = m+1; i; --i) a[i] = inc(a[i], mul(x, a[i-1])); }
void div(int x) { for (int i = 1; i <= m+1; ++i) a[i] = dec(a[i], mul(x, a[i-1])); }

int k, fac[N], ifac[N];
int calc() {
    int n = min(m, k), r = 1;
    for (int i = 1; i <= n; ++i)
        r = inc(r, mul(mul(a[i],fac[k]), ifac[k-i]));
    return r;
}

int ans, f[N], n;
void dfs(int u) {
    sz[u] = 1;
    for (int v : e[u]) {
        e[v].erase(ranges::find(e[v], u));
        dfs(v); sz[u] += sz[v];
        ans = inc(ans, mul(f[u], f[v]));
        f[u] = inc(f[u], f[v]);
    }
    ranges::sort(e[u], [](int i, int j) {
        return sz[i] < sz[j];
    });
    solve(u), m = e[u].size(), mul(n-sz[u]);
    for (int l = 0, r, s, t; l < m; l = r) {
        div(t = sz[e[u][l]]), s = 0;
        for (r = l+1; r < m && sz[e[u][r]] == t; ++r) {}
        for (; l < r; ++l) s = inc(s, f[e[u][l]]);
        ans = inc(ans, mul(s, calc())), mul(t);
    }
    div(n-sz[u]), f[u] = inc(f[u],calc()), memset(a, 0, (m+1)<<2);
}


inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    fast;
    n = rd(), k = rd(), m = max(n, k), fac[0] = 1;
    if (k == 1) return cout << 1ll*n*(n-1)/2%mod, 0;
    for (int i = 1; i <= m; ++i) fac[i] = mul(fac[i-1], i);
    ifac[m] = ksm(fac[m]);
    for (int i = m; i; --i) ifac[i-1] = mul(ifac[i], i);
    for (int i = 1, u, v; i < n; ++i)
        u = rd(), v = rd(), e[u].push_back(v), e[v].push_back(u);
    dfs(1);
    cout << ans;
    return 0;
}