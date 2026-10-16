//
// Created by Psy.C on 2026/10/16.
//
/**
求圆内整点数：

点数 = Σ_{x} (2 * floor(sqrt(n - x²)) + 1)   , x = -√n .. √n
因为对每个整数 x，整数 y 满足 y² ≤ n - x²，即 |y| ≤ floor(sqrt(n-x²))，共 2t+1 个（含 y=0）。

直接枚举 x 从 1 到 √n 有 O(√n) 个（√n - 1e9 时仍太大），所以每步里对 t = floor(sqrt(n-x²)) 的整数点做等幂求和闭合公式，把 sum 的循环挪到 i 递增推进上
x 从 sqrt(n) 递减到 0（-x 当 x=-1 时停止）。
对每个 x，t = floor(sqrt(n - x²)) 是 y 的上界。
i 从 1 单调递增到 t，只进不退（因为 x 递减时 n-x² 递增，所以 t 非降）。内层循环累加 s2 = Σ i²、s4 = Σ i⁴、s6 = Σ i⁶（模 mod）。
这样对 tt 的上界增量部分做累加，总 O(√n) 次内层操作
对某个固定的 x，圆内第 x 列的整点数为 (2t+1)，且对 y 从 -t 到 t 求和时，需要用 x²、y² 的幂和 来计算某个平方和形式的目标值。

代码里的 add 是若干项的组合（系数是 x 的多项式，乘以幂和 s2/s4/s6 和 (2t+1)），本质是用等幂求和公式 (Σi²、Σi⁴、Σi⁶ 的闭合表达式) 一次性算出整列的某种 F(x) 加权和，从而用数学变换把 O(t) 的列内求和压缩成 O(1)。

各分段：

第一项 2*inv3*s6：含 Σi⁶ 的项。
第二项 ... *s4：含 Σi⁴ 的项（系数含 x²）。
第三项 ... *s2：含 Σi² 的项（系数含 x²、x⁴）。
第四项 ... * (2t+1)：常数项乘列长度 (2t+1)（含 mn、x² 的组合，系数含 inv2、inv6——即 1/2、1/6 的模逆）。
所有模运算用 %%mod 处理负数（+2*mod、+mod 防负）
当 x = 0 时只有一列，贡献 add。
其余 x 值，x 与 -x 两列对称，贡献 2*add。
这样 sum 就覆盖了全部 2*√n+1 列（x 从 -√n 到 √n）

内层的 s2/s4/s6 是分段累积的（随 t 变化只增量更新），但每一列 add 里对这些幂和可以展开成关于 t 的多项式，配合已知公式：

Σ_{i=1}^t i   = t(t+1)/2
Σ i² = t(t+1)(2t+1)/6
Σ i⁴ = t(t+1)(2t+1)(3t²+3t-1)/30
Σ i⁶ = t(t+1)(2t+1)(3t⁴+6t³-3t+1)/42
代码使用 inv2 (1/2)、inv3 (1/3)、inv6 (1/6) 以及上述幂和逐步累加出的 s2/s4/s6（内层循环只用递推累加，不涉及高次反除），把整列的加权和化为 O(1) 计算
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int mod = 1e9+7, inv3 = 333333336,inv6 = 166666668, inv2 = 5e8+4;
ll n, mn, ans;
int main() {
    fast;
    cin >> n; mn = n%mod;
    for (ll x=1ll*sqrt(n+0.1), i=1, s2=0, s4=0, s6=0; ~x; --x) {
        ll t = sqrt(n-x*x), x2 = x*x%mod;
        for (; i <= t; ++i) {
            ll pw2=i*i%mod, pw4=pw2*pw2%mod;
            s2 = (s2 + pw2)%mod;
            s4 = (s4 + pw4)%mod;
            s6 = (s6 + pw2*pw4)%mod;
        }
        ll add = ((ll)2*inv3*s6%mod
                    +(2*x2-2-mn+2*mod)%mod *s4%mod
                    +( (1+mn)*((mod-2)*x%mod*x%mod+1)%mod + 2*x2*x2%mod-2*x2+inv3+2*mod )%mod *s2%mod
                    +   (inv2*(1+mn)%mod*(mn+x2)%mod*(mn-x2+mod+1)%mod
                        -inv6*mn%mod*(mn+1)%mod*(2*mn+1)%mod
                        +inv6*(x2-1)%mod*x2%mod*(2*x2-1)%mod
                        +mod
                        )%mod*(2*t+1)%mod
                )%mod;
        ans += (!x) ? add : 2*add;
    }
    cout << ans%mod << '\n';
    return 0;
}