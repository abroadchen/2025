//
// Created by Psy.C on 2026/9/26.
//
/**
一个匿名 struct 对象 read，重载了 operator int 和 operator ll。
当出现 int x = read; 时，自动把逗号表达式 scanf(...), x 的结果转成 int（读入一个整数）。
这样写可以像 cin 一样 int n = read;，但底层是 scanf（更快，且不用 &）
快速幂 x^k mod mod。
关键：if (k < 0) k += mod-1; —— 用费马小定理把负指数转成正指数：x^(mod-1) ≡ 1 (mod mod)，所以 x^(-1) ≡ x^(mod-2)。这里 k=-1 时变成 k = mod-2，用来求逆元（如 ifac[n] = fac[n]^(-1)）。
标准快速幂循环
a[]：原数组（消平方因子后）。
b[]：各组的数量（第 i 组有多少个相同的 square-free 值），bn 为组数。
fac[], ifac[]：阶乘与阶乘逆元。
f[], g[], h[]：DP 用的多项式系数数组
读入 n，mx = sqrt(inf) = sqrt(1e9) ≈ 31623。
对每个数 a[i]：
从大到小尝试 x（从 sqrt(1e9) 到 1），若 a[i] 能被 x*x 整除，就除掉（消去一个平方因子），然后 break。
这样得到的是无平方因子部分（square-free part）‍。
推导：两个数 p, q 的乘积为完全平方数 ⟺ 它们的 square-free 部分相等（因为平方因子不会再影响是否平方）。设 a = A·s1², b = B·s2²（A、B 无平方因子），则 a·b = A·B·(s1s2)²，是平方数 ⟺ A·B 是平方数 ⟺ A=B。★ 这就是消平方因子的原因。
关于为什么只除一次 x*x：因为每个平方数都可以写成若干质数平方之积，从大到小扫描配合 break，即使不能一次除尽，最终结果仍是无平方因子的（实际这类题通常保证或接受这样处理；严格来说可能需要完全除尽，这里算法成立的前提是每个数只含一个会被除到的 x² 或者后续结果仍正确——这里按常见题解约定处理，属于该题的特定实现）。
排序后相同 square-free 值会相邻。
遍历：若与上一个不同，开新组 b[++bn]=1；否则当前组计数 ++b[bn]。
得到各组大小 b[1..bn]（相同 square-free 值的个数）
计算 fac[i] = i!。
ifac[n] = (n!)⁻¹（用快速幂求逆）。
递推回退得到所有 ifac[i] = (i!)⁻¹（因为 ifac[i-1] = ifac[i] * i）

把各组"同色相邻对"的生函数做多项式卷积的部分。

对第 i 组（大小为 b[i]）：

构造该组的 g[]：
g[k] 表示把这一组的 b[i] 个相同元素，分成"k 个块（块内元素相邻）"的方案相关值（含 ifac 用于后续容斥）。
系数按 coe *= j(j-1) 递推，对应把 k 块还能再减少块数的（斯特林/选块）组合数。这里本质是计算：这一组内部"合并成 k 个连续块"的计数，乘以 ifac[k]
把之前的累积多项式 f 与当前组的 g 卷积，结果存 h。
f[j] 表示前 i-1 组总共合并成 j 个"坏块"的加权计数；乘上本组贡献 k 块 → 总计 j+k 块
lim += b[i] - 1：每新增一组，最大可能"坏块/相邻"数增加 b[i]-1（一组内最多 b[i]-1 个同色相邻对）。
f = h 更新累积多项式。
最终 f[j] 表示：把所有组拼在一起、总共留下 j 处"同色相邻（坏块）"时的（含 ifac 容斥权重）计数
f[j] *= fac[n-j]：把前面乘的 ifac 抵消掉，fac[n-j] 是对合并出的 j 个块（连同其余单元素）进行全排列的方案数——即"j 个同色相邻对固定时"的排列计数。
容斥：用 Σ (-1)^j · f[j]（j 为奇数取减、偶数取加）。这里是对"恰好 0 个同色相邻对"的排列数做容斥排除——标准容斥：ans = Σ_j (-1)^j · (至少有 j 处同色相邻的排列数)
修正负数取模后输出 ans，即满足"任意相邻两数乘积不是完全平方数"的排列数
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 5005, mod = 1e9+7, inf = 1e9;

struct {
    operator int() const {
        int x;
        return scanf("%d", &x), x;
    }
    operator ll() const {
        ll x;
        return scanf("%lld", &x), x;
    }
} read;

ll ksm(ll x, int k) {
    if (k < 0) k += mod-1;
    ll res = 1;
    while (k) {
        if (k&1) (res*=x) %= mod;
        (x*=x) %= mod;
        k >>= 1;
    }
    return res;
}

int a[N], b[N], bn;
ll fac[N], ifac[N], f[N], g[N], h[N];
int main() {
    int n = read, mx = int(sqrt(inf));
    for(int i = 1; i <= n; i++) {
        a[i] = read;
        for(int x = mx; x; x--)
            if(!(a[i] % (x * x))) {
                a[i] /= x * x;
                break;
            }
    }
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i ++)
        if(a[i] != a[i - 1])
            b[++ bn] = 1;
        else
            ++b[bn];
    fac[0] = 1;
    for(int i = 1; i <= n; i ++)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = ksm(fac[n], -1);
    for(int i = n; i; i --)
        ifac[i - 1] = ifac[i] * i % mod;

    int lim = 0;
    f[0] = 1;

    for(int i = 1; i <= bn; i ++) {
        ll coe = 1;
        for(int j = b[i]; j; j --) {
            g[b[i] - j] = coe * ifac[b[i] - j] % mod;
            (coe *= j * (j - 1)) %= mod;
        }
        for(int j = 0; j <= lim + b[i]; j++)
            h[j] = 0;
        for(int j = 0; j <= lim; j++)
            for(int k = 0; k < b[i]; k++)
                (h[j + k] += f[j] * g[k]) %= mod;
        lim += b[i] - 1;
        for(int j = 0; j <= lim; j++)
            f[j] = h[j];
    }

    for(int j = 0; j <= lim; j++)
        (f[j] *= fac[n - j]) %= mod;

    ll ans = 0;
    for(int j = 0; j <= lim; j++)
        ans += j & 1 ? - f[j] : f[j];
    ans %= mod;
    if(ans < 0) ans += mod;
    printf("%lld\n", ans);
    return 0;
}