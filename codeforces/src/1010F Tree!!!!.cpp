//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
998244353 = 119×2²³ + 1，原根为 3
fac/ifac/inv：阶乘、逆阶乘、逆元（用于组合数）。
lg[n]：存"≥ n 的最小的 2 的幂"，即 NTT 长度。
rev：NTT 的位反转数组
计算 C(x,y)，越界返回 0。
用预处理好的阶乘/逆阶乘快速算
把 n 扩到 ≥ 2×nn 的 2 的幂。
lg[1]=lg[0]=1；对每个 i，lg[i] = 大于等于 i 的最小 2 的幂（通过递推 lg[(i+1)>>1]<<1）
线性预处理 1..n 的逆元（利用 inv[i] = -(mod/i)*inv[mod%i] mod p）
预处理阶乘和逆阶乘
多项式相加：z 先拷贝较短者，若 x 更长则补齐长度，然后把 t = min(x,y) 长度的部分逐项相加取模
先保证长度扩到 2 的幂（用 lg[n]）。
⚠️ 注意：lg[n] 的定义是"≥n 的最小 2 的幂"，这里 if (n < lg[n]) 只有非 2 的幂才满足
位反转排序：标准 NTT 的蝶形前置步骤，把元素按二进制反转位置排列
外层循环枚举块大小 i（1,2,4,...）。
u = 第 i 级的旋转因子（本原根 3 的 (mod-1)/(2i) 次幂）。逆变换用其逆元（即 3^( (mod-1)/(2i)*(-1))，等价于原根的逆）。
注：(mod-1)/i>>1 即 (mod-1)/(2i)
标准Cooley–Tukey 蝶形运算：每个块 j 内做 i 次蝶形，v 为递推的旋转因子。完成正/逆 NTT 的变换主体
逆变换末尾要乘 1/n（n 的逆元）归一化

n：卷积结果的真正长度；len：> n 的最小 2 的幂（NTT 长度）
标准 NTT 卷积流程：正变换 → 逐点相乘 → 逆变换 → 截断到真正长度 n
这是 Berlekamp–Massey 相关的循环卷积 / 多项式取逆快速求递推第 k 项技巧。
当 k>0 时：把 g 的奇数位取负（t[i] = -t[i]），构造出"负号交替"的多项式，用于把多项式相乘变成"对幂次翻转"操作。f = f*t, g = g*t 是两者相乘
抽取偶次幂项：把 f 中下标从 k&1 开始、步长 2 的元素重新存到 f[0], f[1], ...（即压缩偶数/奇数位置）。同理压缩 g。然后 k >>= 1。
这是"折半取幂"的循环：因为 (P·Q) 半折叠 对应某种平方/乘方的操作，能把后缀的计算量降为 O(log k) 次循环，每次循环是一次 NTT 卷积
循环结束后（k 变 0），返回 f[0] * inv(g[0]) —— 即特征多项式求解线性递推序列第某项的模结果。
总结 BM：给定初始多项式 f、特征多项式 g，求递推序列某项 X（X 从 main 传入），用了"二进制拆分 + 偶次项抽取"技巧在 O(log k) 次卷积内完成。这是对 线性递推 序列第 X 项求法（Molien 级数/最短线性递推式）的实现

生成多项式 (1 - t)^x（即展开 (1-t)^x = Σ (-1)^i C(x,i) t^i）。
ret[i] = (-1)^i * C(x,i)。
这是一个"负二项展开"多项式，用于后续分数加法时对齐分母次数（类似写作 (1-z)^g 的系数）
frac 表示形如 f(t) / (1-t)^g 的有理函数。
f = 分子多项式系数。
g = 分母中 (1-t) 的幂次（即分式阶数）。
乘法 *：分子相乘（NTT 卷积）、分母次数相加。
加法 +：需分母同阶。若 g >= x.g，则把 x 的分子乘上 get(g-x.g) = (1-t)^(g-x.g) 对齐分母，再相加分子。反之对称处理。结果分母取较大次数。
为什么用这种表示？因为树上的组合计数（如邻接矩阵/连通导出子图计数）的生成函数常可写成 P(t)/(1-t)^d 形式，重轻链剖分后每个轻链贡献一个这样的分式，用这些运算合并

sz[u]：u 的子树节点数。
son[u]：u 的重儿子（子树最大的孩子），用于轻重链剖分。
递归后统计子树大小并选出重儿子
cdq(b) 处理一条重链上的节点序列 b（按深度降序，从链头到链尾）。
单元节点：返回两个副本，第一个代表"整段乘积"，第二个代表"整段及末尾"
sum = 整条链上所有 f[x].g 之和（作为分治"权重"）。
遍历寻找使左右两部分最大 g 和最小的分割点 mid（保持分治平衡，避免退化）。这是"按照幂次均衡切分"
递归切左半段、右半段。
合并结果：
第一分量（多项式） = fr*gl + fl（右半段多项式乘左半段"末尾累积"，再加重链头贡献）。
第二分量 = gl*gr（两半段的"末尾累积"相乘）。
这实际是在用分治线性扫过重链，把树上一条重链上各节点的 frac 依次乘/加合并，得到整条链对应的多项式产物

递归进入重儿子；tp=0 表示重儿子延续当前链（不是新的链头）
先赋 f[u] = 1/(1-t)^0 = 1（分子多项式 {1}，次数 0）。
遍历所有轻儿子 v，递归处理（tp=1，新链头），然后 f[u] = f[v]。
这一步是核心：u 的多项式直接"继承"其轻儿子的 frac。因为重链上的每个非链头节点的生成函数贡献会被其下端链合并，这里选择了代表轻分支的 frac
仅当 u 是链头（tp=1）时：
顺着重链 x=u, son[x], son[son[x]]... 收集整条链到 td，并且把链上每个节点的 f[x].g++（分母幂次 +1，累积到链长度）。
f[u] = cdq(td).first：对整条链做分治合并，取结果的多项式部分作为链头 u 的 f.u。
若 u 不是根（u≠1），f[u].f 还要加上 get(f[u].g)（即加上 (1-t)^g，调整符号，见分数分母对齐）。这是为了保证构造的多项式表示与全局要求一致。
本质：按轻重链剖分深度递归，每条重链用一个 cdq 分治合并，向上聚合出整棵树的 f[1]

读入节点数 n 和参数 X（要查询的序列项）。
init((n+1)<<1)：初始化阶乘/逆元/NTT 长度到约 2(n+1)
建树（n-1 条边，无向存储）
dfs(1,0)：算子树大小和重儿子。
dfs2(1,0,1)：从根开始轻重链剖分 DP，计算出整棵树对应的 f[1]（根节点的 frac）
最终用 BM(f[1].f, get(f[1].g), X)：
分子多项式 f[1].f
"特征多项式" get(f[1].g) = (1-t)^g
求线性递推序列的第 X 项。
输出该结果。

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define vl vector<ll>
#define vi vector<int>
using namespace std;

constexpr int N = 2e5+10, mod = 998244353;

namespace Ju {
    ll fac[N<<2], ifac[N<<2], inv[N<<2];
    int lg[N<<2], rev[N<<2];
    ll C(int x, int y) {
        if (x < 0 || y < 0 || x < y) return 0ll;
        return fac[x]*ifac[y]%mod*ifac[x-y]%mod;
    }
    ll ksm(ll x, ll y) {
        ll z = 1;
        while (y) {
            if (y&1) z=z*x%mod;
            x=x*x%mod;
            y>>=1;
        }
        return z;
    }
    void init(int nn) {
        int n = 1;
        while (n < nn<<1) n <<= 1;
        lg[1] = lg[0] = 1;
        for (int i = 2; i <= n; i++) lg[i] = lg[(i+1)>>1]<<1;
        inv[1] = 1;
        for (int i = 2; i <= n; i++) inv[i] = (mod-mod/i)*inv[mod%i]%mod;
        fac[0] = ifac[0] = 1;
        for (int i = 1; i <= n; i++) fac[i] = fac[i-1]*i%mod, ifac[i] = ifac[i-1]*inv[i]%mod;
    }
    vl operator+(const vl &x, const vl &y) {
        vl z(y);
        int t = x.size();
        if (x.size() > y.size()) {
            t = y.size(); z.resize(x.size());
            for (int i = y.size(); i < x.size(); i++) z[i] = x[i];
        }
        for (int i = 0; i < t; i++) z[i] = (z[i] + x[i]) % mod;
        return z;
    }
    void ntt(vl &x, int flg) {
        int n = x.size();
        if (n < lg[n]) x.resize(lg[n], 0), n = lg[n];
        for (int i = 1; i < n; i++) {
            rev[i] = rev[i>>1]>>1;
            if (i&1) rev[i] |= n>>1;
            if (i < rev[i]) swap(x[i], x[rev[i]]);
        }
        for (int i = 1; i < n; i <<= 1) {
            ll u = ksm(3, (mod-1)/i>>1);
            if (flg == -1) u = ksm(u, mod-2);
            for (int j = 0; j < n; j += i<<1) {
                ll v = 1;
                for (int k = 0; k < i; k++) {
                    ll y = x[j|k], z = x[j|i|k]*v%mod;
                    x[j|k] = y + z;
                    if (x[j|k] >= mod) x[j|k] -= mod;
                    x[j|i|k] = y - z;
                    if (x[j|i|k] < 0) x[j|i|k] += mod;
                    v = v*u%mod;
                }
            }
        }
        if (flg == -1) {
            ll t = ksm(n, mod-2);
            for (int i = 0; i < n; i++) x[i] = x[i]*t%mod;
        }
    }
    vl operator*(const vl &x, const vl &y) {
        static vl t1, t2; vl z; t1 = x, t2 = y;
        int n = x.size() + y.size() - 1, len = lg[n];
        t1.resize(len, 0), t2.resize(len, 0); z.resize(len);
        ntt(t1, 1); ntt(t2, 1);
        for (int i = 0; i < len; i++) z[i] = t1[i]*t2[i]%mod;
        ntt(z, -1); z.resize(n);
        return z;
    }
    ll BM(vl f, vl g, ll k) {
        static vl t;
        while (k) {
            t = g;
            for (int i = 1; i < g.size(); i += 2) t[i] = (mod-t[i])%mod;
            f = f*t; g = g*t;
            int i = k&1;
            for (; i < f.size(); i += 2) f[i>>1] = f[i];
            f.resize(i>>1);
            for (i = 0; i < g.size(); i += 2) g[i>>1] = g[i];
            g.resize(i>>1);
            k >>= 1;
        }
        if (f.empty()) return 0;
        return f[0]*ksm(g[0], mod-2)%mod;
    }
}
using namespace Ju;
vl get(int x) {
    vl ret; ret.resize(x+1);
    for (int i = 0; i <= x; i++) {
        ll t = C(x,i);
        ret[i] = (i&1) ? (mod-t)%mod : t;
    }
    return ret;
}

struct frac {
    vl f; int g;
    frac operator*(const frac &x) const { return {f*x.f, g+x.g}; }
    frac operator+(const frac &x) const {
        if (g >= x.g) return {f+x.f*get(g-x.g), g};
        return {x.f+f*get(x.g-g), x.g};
    }
} f[N];

int sz[N], son[N];
vector<int> g[N];
void dfs(int u, int fa) {
    sz[u] = 1; son[u] = 0;
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}


pair<frac, frac> cdq(vi b) {
    if (b.size() == 1) return {f[b[0]], f[b[0]]};
    int sum = 0;
    for (int x : b) sum += f[x].g;
    int mid = 0, mn = sum, sm = 0;
    for (int i = 0; i < b.size()-1; i++) {
        sm += f[b[i]].g;
        if (max(sum-sm, sm) < mn) {
            mn = max(sum-sm, sm);
            mid = i;
        }
    }
    auto [fl, gl] = cdq(vi(b.begin(), b.begin()+mid+1));
    auto [fr, gr] = cdq(vi(b.begin()+mid+1, b.end()));
    return {fr*gl+fl, gl*gr};
}

void dfs2(int u, int fa, bool tp) {
    if (son[u]) dfs2(son[u], u, 0);
    f[u] = {{1}, 0};
    for (int v : g[u]) {
        if (v == son[u] || v == fa) continue;
        dfs2(v, u, 1);
        f[u] = f[v];
    }
    if (tp) {
        vi td;
        for (int x = u; x; x = son[x]) {
            td.push_back(x);
            f[x].g++;
        }
        f[u] = cdq(td).first;
        if (u != 1) f[u].f = f[u].f + get(f[u].g);
    }
}

ll X;
int n;
int main() {
    fast;
    cin >> n >> X; init((n+1)<<1);
    int sum = 0;
    for (int i = 1, x, y; i < n; i++)
        cin >> x >> y, g[x].push_back(y), g[y].push_back(x);
    dfs(1, 0); dfs2(1, 0, 1);
    cout << BM(f[1].f, get(f[1].g), X) << '\n';
    return 0;
}