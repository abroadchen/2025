//
// Created by Psy.C on 2026/10/14.
//
/**
ksm(a, b)：快速幂，计算 a^b mod p。
默认参数 b = p-2：利用费马小定理，当 p 为质数时 a^(p-1) ≡ 1 (mod p)，所以 a^(p-2) 就是 a 的乘法逆元。即默认调用 ksm(a) 求得 a⁻¹ mod p。
标准二进制快速幂实现
读入四个数：a, b, p, x。

外层循环 r = 0 .. p-2（遍历所有 r，注意是 < p-1，即 p 的循环群阶 p-1）
ksm(a, r) 求 a^r mod p；
再对它取逆元 ksm(...) 得到 (a^r)⁻¹ mod p；
乘上 b 再取模，即 f = b / a^r (mod p)（在模 p 下的乘法逆元除法）
计算 k ≡ r - f (mod p)，取模到 [0, p-1)
构造一个同余条件的基准值 now（这通常来自原问题里"x 对某数取模等于某值"的线性同余解）
若 now > x，说明该 r 分支下最小可行值已超出上限，跳过。
否则累加：满足条件的值形如 now + t·(p·(p-1))（t≥0），在不超过 x 的范围内共有 (x-now)/(p*(p-1)) + 1 个。
最后 cout << ans; 输出解的总数

复杂度	O(p · log p)，主要受 p 规模限制
退化解	需要前提 p 为质数（保证逆元存在）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

namespace Ju {
#define int long long
    int p;
    int ksm(int a, int b=p-2) {
        int res = 1;
        for (; b; b>>=1, a=a*a%p)
            if (b&1) res=res*a%p;
        return res;
    }
    int a, b, x, ans;
    void solve() {
        cin >> a >> b >> p >> x;
        for (int r = 0, f, k, now; r < p-1; ++r) {
            f = b*ksm(ksm(a, r))%p;
            k = (r - f + p)%p;
            if ((now = k*(p-1)+r) > x) continue;
            ans += (x - now)/(p*(p-1)) + 1;
        }
        cout << ans;
    }
#undef int
}

signed main() {
    fast;
    Ju::solve();
    return 0;
}