//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
n：元素个数，a[N]：存放 n 个数（按下标 1..n）。
m1、m2：两个 map，键是"质因子/底数"，值是对应次数。用于统计分解后的因子次数。
读入第 i 个数 x。若 x==1 跳过（1 没有贡献）
判立方数：cbrt(x) 是 x 的立方根（注意：cbrt 返回 double，隐式转成了 long long）。如果 z³ == x，说明 x 是某个数 z 的立方，于是该数的因子次数贡献 3，记入 m1，continue
判平方数：o = sqrt(x)，若 o² == x 说明 x 是完全平方数。

再判 o 是否本身是平方数（t² == o）：
若 o 也是平方数，则 x = t⁴，即四次方数，因子次数贡献 4，m1[t] += 4；
否则 x = o²，贡献 2，m1[o] += 2。
既非一次平方、也非绝对立方数的情况：

内层循环遍历所有 a[j]，用 __gcd(a[i], a[j]) 找 a[i] 与某个 a[j] 的一个非平凡公因子 t（t ≠ 1 且 t ≠ a[i]）。找到就 break。
若找到这样的 t，则 a[i] 可分解为两个因子：a[i] = t * (x / t)，把这两个因子分别统计进 m1（m1[t]++, m1[x/t]++）。
若找不到（t 一直是 1 或 a[i]），说明 a[i] 是"质数/无法拆出已知因子的残余"数，把它整个存进 m2（m2[a[i]]++）
m1 | views::values：C++20 的 range 语法，取 map 的所有值（即各因子出现次数）。
对 m1 中的每个次数 val：ans *= (val+1)。
对 m2 中的每个次数 val：ans *= (val+1)*(val+1)。
全程取模 mod。
数学含义：答案是各质因子可分配方案数的乘积。对于某个因子出现 val 次（val 为它在 m1 中的计数），能分成 (val+1) 种不同组合；对于 m2 里的"独立残余因子"，每个这类因子既可单独也可与其他组合，贡献 (val+1)²
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define int long long
using namespace std;

constexpr int N = 505, mod = 998244353;

int n, a[N];
map<int,int> m1, m2;
signed main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n) {
        int x = a[i];
        if (x == 1) continue;
        int z = cbrt(x);
        if (z*z*z == x) { m1[z] += 3; continue; }
        int o = sqrt(x);
        if (o*o == x) {
            int t = sqrt(o);
            if (t*t == o) m1[t] += 4; else m1[o] += 2;
        } else {
            int t = 0;
            rep(j,n) {
                t = __gcd(a[i], a[j]);
                if (t != 1 && t != a[i]) break;
            }
            if (t != 1 && t != a[i]) m1[x/t]++, m1[t]++; else m2[a[i]]++;
        }
    }
    int ans = 1;
    for (auto val: m1 | views::values) ans = ans*(val+1)%mod;
    for (auto val: m2 | views::values) ans = ans*(val+1)%mod*(val+1)%mod;
    cout << ans;
    return 0;
}