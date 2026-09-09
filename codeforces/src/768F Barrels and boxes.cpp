//
// Created by Psy.C on 2026/9/7.
//
/**
fac[i]：i!（i 的阶乘）对 mod 取模。
ifac[i]：i! 的模逆元，用于快速计算组合数
第一行特判：当 n == m == -1 时返回 1（边界情况处理，见后面用到的"空段"情形）。
返回式：fac[n] * ifac[m] * ifac[n-m] % mod，即用阶乘与逆元算组合数。
若 n<0、m<0 或 n<m，直接返回 0（非法组合数）。这里的 ifac[-1] 之类越界调用因 w-1ll*(i-j)*h-1 可能为负，通过前置判断避免数组越界
f：食物/一种物品的数量（本例取"猫/fox"数）。
w：另一种物品的数量（"狼/wolf"数）。
h：每两只狼之间至少间隔的狼数（步长限制，h≥0）。
n = f+w：总物品数。
P：满足"狼之间至少隔 h 只狼"的排列数（分子）。
Q：所有合法总排列数（分母）

预处理阶乘表：fac[i] = fac[i-1] * i % mod
利用费马小定理求 fac[N-5] 的模逆元（因为 mod 是质数，a^(mod-2) 是 a 的逆元）
递推求所有逆元阶乘：ifac[i-1] = ifac[i] * i % mod（因为 1/(i-1)! = i/(i)!）

外层 i：枚举总共参与的"段/分隔单位"数量（i 大致代表把狗群切分的总段数相关量）。x 根据 i 奇偶取 1 或 2——这是为了处理"狗段的两端是否为开/关"的计数细节（若两侧都是猫围住，则权重不同）。
内层 j 从 i>>1 到 (i+1)>>1：这个区间很小（多数只有 1-2 个值），枚举 j 的对称取值。
组合数含义：

C(f-1, j-1)：把 f 只猫（额外的间隔填充）分配给 j 个"空隙"。参考实现中，这是"把 f-1 个可插入的位置中选 j-1 个"。
q 部分 C(w-1, i-j-1)：把 w 只狼在 i-j 个"段"里分配（每个段至少 1 只，故 w-1 选 i-j-1）——对应任意摆放（不限制狼之间的最小距离）。
p 部分 C(w-1ll*(i-j)*h-1, i-j-1)：把 w 只狼分配到 i-j 个段里，且每两个段之间额外多塞 h 只（即每只"狗之间的空隙"至少要 h 只狼），所以相当于 w 减去 (i-j)*h 后再做隔板分配。这就是"强制任意两只（段里）狼之间至少隔 h"的计数。
这个 p/q 结构正是条件概率分子/分母：

Q（分母）= 把所有 f+w 个排成一排时，各种切分下合法总排列数。
P（分子）= 满足"每两只狼之间距离 ≥ h"约束的排列数
最后输出 P / Q 对模数的结果，即利用 Q 的模逆元做"比例/条件概率"的模意义除法，得到满足约束的排列数占总排列数的比例
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5, mod = 1e9+7;

ll fac[N], ifac[N];
ll C(ll n, ll m) {
    if (n == m && n == -1) return 1;
    return n < 0 || m < 0 || n < m ? 0 : fac[n]*ifac[m]%mod*ifac[n-m]%mod;
}

ll pw(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b&1) (res*=a)%=mod;
        (a*=a)%=mod;
        b >>= 1;
    }
    return res;
}

int f, w, h, n;
ll P, Q;
int main() {
    fast;
    cin >> f >> w >> h;
    n = f+w; fac[0] = 1;
    for (int i = 1; i <= N-5; ++i) fac[i] = fac[i-1]*i%mod;
    ifac[N-5] = pw(fac[N-5], mod-2);
    for (int i = N-5; i; --i) ifac[i-1] = ifac[i]*i%mod;
    for (int i = 1; i <= n; ++i) {
        int x = (i&1) ? 1 : 2;
        for (int j = i>>1; j <= (i+1)>>1; ++j) {
            ll q = C(f-1, j-1)*C(w-1, i-j-1)%mod*x%mod,
            p = C(f-1, j-1)*C(w-1ll*(i-j)*h-1, i-j-1)%mod*x%mod;
            (Q+=q)%=mod, (P+=p)%=mod;
        }
    }
    cout << P*pw(Q, mod-2)%mod;
    return 0;
}