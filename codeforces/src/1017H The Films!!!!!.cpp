//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
N：数组/查询规模上限；
M：阶乘数组上限；
mod = 998244353：模数（素数）;
B = 80：出现次数分治阈值（heavy vs light 分界）
含义：a = (a+b) % mod。利用 a+b < 2*mod 的性质（因为两数都
<
m
o
d
<mod），若超界则一次减法完成取模，比 % 快
返回 a+b 的取模结果（不改 a），配合 add 使用
乘法取模，用 ll 防溢出
原地累乘：a = a*b % mod
递归快速幂，a^b mod mod。b=0 返回 1，否则二分平方，奇数位再乘一个 a。
模逆元，费马小定理：x^(mod-2)（因为 mod 是素数）

node：一个查询 {l, r, id}，id 是查询编号；
d[N]：存每个查询的 (l, r, k) 原始信息（在 main 中 d[i]={l,r,k}）;
p[N]：按 k（出现次数）分组存放查询，p[k] 是出现次数为 k 的查询集合；
ek[M]：某种「前缀/区间」阶乘组合结果数组（块1用）;
el[M]：另一套组合结果（块1用）；
ct[N]：ct[x] = 值 x 在数组 a[] 里的总出现次数；
out[N]：每个查询的答案，初始化为 1，最后累乘输出。
处理所有「出现次数恰好为 k」的查询（存在 p[k] 里的）
K = k!（k 的阶乘）
ren(i) 即 for i in 1..n。
ek[i] = (k+i)!：因为 K 从 k! 开始，每次乘 (i+k)，得到 (k+i)!。
所以 ek[i] = (i+k)!
这是从后往前填 el：
el[n] = 1；
每次 S *= nw，然后 nw++，再 el[n-i] = S。
展开看：设当前 nw 的值在迭代中依次为
k
⋅
m
+
1
,

k
⋅
m
+
2
,
…
k⋅m+1, k⋅m+2,…
el[n] = 1
el[n-1] = (k·m + 1)
el[n-2] = (k·m+1)(k·m+2)
…
`el[n-i] = \prod_{j=0}^{i-1}(k·m+1+j)$
即 el[i] = (k·m + (n-i+1))!! 类连乘积——具体是「从 (k·m+1) 起的 n 项连乘」的后缀，倒序存储
rem(i) 即 for i in 1..m（遍历所有值）。
对每个出现次数非 0 的值，w *= ek[ct[i]] = (ct[i]+k)!。
即 w = ∏ (ct[i]+k)!（对所有非空值）
对区间长度 len = r-l+1 的查询：
答案累乘 w * el[len]。
Mul(out[id], mul(w, el[r-l+1])) 即 out[id] *= w * el[r-l+1]。
小结：solve(k) 汇总了「出现次数为 k 的那类查询」里，所有 heavy 值（出现
≥
≥ 次数相关的）的贡献因子
t[N]：树状数组（差分查询用）；
nw[N]：节点的「当前值」（与出现次数相关的递归量）；
pre[N]：pre[i] = 位置 i 的值的上一次出现位置（在 main 中填）；
fr[x]：值 x 的第一次出现位置；
nxt[i]：位置 i 的值的下一次出现位置
树状数组单点加（实际上是差分数组上做区间加的前端）。
树状数组前缀和查询。
这是「扫描线」的核心：对位置 x，若有 0 < nw[x] <= x，则在区间 [pre[nw[x]]+1, nw[x]] 上做差分加减（用 ad 做区间加）。
l = pre[nw[x]] + 1：以 nw[x] 为「锚点值」时其上一次出现在 pre[nw[x]]，区间从该位置后一位开始到 nw[x]
状态转移函数：
若 w < -1：返回 w+1（表示某种「负数深度」递增）；
若 w == -1：返回 fr[col]（值 col 第一次出现位置）；
否则：返回 nxt[w]（位置 w 处值的下一次出现位置）。
这是对 nw 数组的「递推更新」用的转移。
fac[i] = i!（阶乘前缀）；
iv[i] = i^{-1}（每个数的逆元）；
Iv[i] = (i!)^{-1}（阶乘的逆元，倒推）。
读入 n（数组长）、m（值的种类数）、q（查询数）；
读入数组 a[1..n]，同时统计每个值的出现次数 ct[]
读入每个查询 (l, r, k)，存到 d[i]；
p[k]：按出现次数 k 分组该查询 → 供 solve 用；
out[i]=1：答案初始化为 1；
qs[r]：按右端点 r 分组，供扫描线用（结构体里 {l, k, id}
ps[x]：值 x 最近一次出现位置；
pre[i] = ps[a[i]]：位置 i 的值的上一次（前一个）出现位置（若没有则为 0）；
更新 ps；
nw[i] = i：初始化 nw 为位置本身
重置 ps 为 n+1（表示「之后不存在」）。
从后往前：
nxt[i] = ps[a[i]]：位置 i 的值的下一次出现位置（n+1 表示之后无）;
更新 ps；
fr[a[i]] = i：值 a[i] 的第一次（最前）出现位置（由于从后往前扫，最后覆盖的是最前面的位置）。
至此：

pre[i]：位置 i 的该值前一个出现位；
nxt[i]：位置 i 的该值后一个出现位；
fr[col]：值 col 第一次出现位
遍历每个值 x：
若 ct[x] >= B（heavy 值）：
先建 pr 前缀和：pr[i] = 前 i 个位置中值 x 出现的次数；
对每个查询 i，cnt = pr[r]-pr[l-1] 为区间 [l,r] 中值 x 的出现次数；
Mul(out[i], Iv[k + ct[x] - cnt])
即乘以 (k + ct[x] - cnt)!^{-1}。
否则（light 值）tot++：统计 light 值的个数。
这里 heavy 值对答案的贡献是「逆阶乘项」
对所有出现次数 w，若有查询（p[w] 非空）则调用 solve(w)，把该出现次数类别的查询贡献乘到 out
对每个位置 i 初始化 nw[i]：

若 pre[i]==0（位置 i 是其值第一次出现）：
若该值只出现一次 ct[a[i]]==1：nw[i]=i；
否则 nw[i] = -ct[a[i]] + 1（负值，表示「从该处开始往后的链深度」，随后会用 get 的 w+1 分支累加）；
否则（有前一次出现），用 get(a[i], nw[pre[i]]) 从前一次出现的状态转移过来。
这建立起 nw 的初始「链」，用来做后续的扫描线
外层循环 c 从 0 到 B-1（即
B
=
80
B=80 次迭代）；
每轮：
清空树状数组；
遍历每个位置 x：
若该位置值是 light（ct[a[x]] < B）：调用 Solve(pre[x],-1) 和 Solve(x,1)——在相应区间做差分加减（Solve 中根据 nw 的锚点做区间贡献）；
对以 x 为右端点的查询 y：Ct = query(l)（前缀和得到区间计数），然后 Mul(out[id], (k+c)!^{-1})^{Ct}，即 ksm(Iv[k+c], Ct)。
最后把所有 nw[i] 用 get 前进一步（递推更新状态）。
这轮扫描线针对 light 值统计「出现次数为 c 的」贡献
对真正出现次数 c（1..B-1）做更精确的扫描线：
清空树状数组；
rem(i) if (ct[i]==c)：对出现次数恰为 c 的值，在 [1, fr[i]] 区间加（ad(1,1), ad(fr[i],-1)），Cnt++ 计数；
ren(x) 遍历位置：
若位置 x 的值出现次数为 c，则在 [pre[x]+1, x] 区间偏移（ad(pre[x]+1,-1), ad(x,1)）；
若前一个位置的值的出现次数为 c，则在 [x, nxt[x-1]] 区间处理（ad(x,1), ad(nxt[x-1],-1)）；
对右端点为 x 的查询：Ct = query(l) 得到计数，tot -= Ct（消耗计数），Mul(out[id], (k+c)!^{-1})^{Ct}。
这个循环是在减法意义上进一步修正 tot 计数，并累乘对应逆阶乘贡献
逐行输出每个查询的答案 out[i]。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define per(i,j,k) for (int i=j; i>=k; i--)
#define ren(i) rep(i,1,n)
#define rem(i) rep(i,1,m)
#define ll long long
using namespace std;

constexpr int N = 1e5+5, M = 2e5+5, mod = 998244353, B = 80;

inline void add(int &a, int b) { (a+=b) >= mod && (a -= mod); }
inline int Add(int a, int b) { return add(a, b), a; }
inline int mul(int a, int b) { return 1ll*a*b%mod; }
inline void Mul(int &a, int b) { a = mul(a, b); }
inline int ksm(int a, ll b) {
    if (!b) return 1;
    int c = ksm(a, b>>1ll); Mul(c,c);
    if (b&1) Mul(c, a);
    return c;
}
inline int INV(int x) { return ksm(x, mod-2); }

struct node { int l, r, id; } d[N];
vector<node> p[N];
int ek[M], el[M], n, m, ct[N], out[N];
inline void solve(int k) {
    int K = 1;
    rep(i,1,k) Mul(K, i);
    ek[0] = K;
    ren(i) Mul(K, i+k), ek[i] = K;
    int nw = Add(mul(k,m), 1), S = 1;
    el[n] = S;
    ren(i) Mul(S, nw), add(nw, 1), el[n-i] = S;
    int w = 1;
    rem(i) if (ct[i]) Mul(w, ek[ct[i]]);
    for (auto [l, r, id] : p[k]) Mul(out[id], mul(w, el[r-l+1]));
}

int t[N], nw[N], pre[N], fr[N], nxt[N];
inline void ad(int x, int k) { while (x <= n) t[x] += k, x += x&-x; }
inline int query(int x) {
    int ans = 0;
    while (x) ans += t[x], x -= x&-x;
    return ans;
}
inline void Solve(int x, int k) {
    if (!x) return;
    if (nw[x] <= 0) return;
    if (nw[x] > x) return;
    int l = pre[nw[x]] + 1, r = nw[x];
    ad(l, k), ad(r+1, -k);
}
inline int get(int col, int w) {
    if (w < -1) return w + 1;
    if (w == -1) return fr[col];
    return nxt[w];
}

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


int fac[M], Iv[M], iv[M], q, a[N], ps[N], pr[N], tot;
vector<node> qs[N];
int main() {
    fast;
    fac[0] = 1;
    rep(i,1,M-5) iv[i] = INV(i), fac[i] = mul(fac[i-1], i);
    Iv[M-5] = INV(fac[M-5]);
    per(i,M-6,0) Iv[i] = mul(Iv[i+1], i+1);
     n = rd(), m = rd(), q = rd();
    ren(i) a[i] = rd(), ct[a[i]]++;
    rep(i,1,q) {
        int l = rd(), r = rd(), k = rd();
        d[i] = {l, r, k};
        p[k].push_back({l, r, i});
        out[i] = 1; qs[r].push_back({l, k, i});
    }
    ren(i) pre[i] = ps[a[i]], ps[a[i]] = i, nw[i] = i;
    rem(i) ps[i] = n+1;
    per(i,n,1) nxt[i] = ps[a[i]], ps[a[i]] = i, fr[a[i]] = i;
    rem(x) {
        if (ct[x] >= B) {
            ren(i) pr[i] = pr[i-1] + (a[i] == x);
            rep(i,1,q) {
                int l = d[i].l, r = d[i].r, k = d[i].id;
                Mul(out[i], Iv[k+ct[x]-(pr[r]-pr[l-1])]);
            }
        } else tot++;
    }
    rep(w,0,N-5) if (!p[w].empty()) solve(w);
    ren(i) {
        int x = pre[i];
        if (!x) {
            if (ct[a[i]] == 1) nw[i] = i;
            else nw[i] = -ct[a[i]] + 1;
        } else nw[i] = get(a[i], nw[x]);
    }
    rep(c,0,B-1) {
        ren(i) t[i] = 0;
        ren(x) {
            if (ct[a[x]] < B) Solve(pre[x], -1), Solve(x, 1);
            for (auto y : qs[x]) {
                int l = y.l, k = y.r, id = y.id, Ct = query(l);
                Mul(out[id], ksm(Iv[k+c], Ct));
            }
        }
        ren(i) nw[i] = get(a[i], nw[i]);
    }
    rep(c,1,B-1) {
        ren(i) t[i] = 0;
        int Cnt = 0;
        rem(i) if (ct[i] == c) ad(1, 1), ad(fr[i], -1), Cnt++;
        ren(x) {
            if (ct[a[x]] == c) ad(pre[x]+1, -1), ad(x, 1);
            if (x > 1 && ct[a[x-1]] == c) ad(x, 1), ad(nxt[x-1], -1);
            for (auto y : qs[x]) {
                int l = y.l, k = y.r, id = y.id, Ct = query(l);
                tot -= Ct;
                Mul(out[id], ksm(Iv[k+c], Ct));
            }
        }
    }
    rep(i,1,q) write(out[i]), putchar('\n');
    return 0;
}