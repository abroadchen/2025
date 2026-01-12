//
// Created by Psy.C on 2026/1/12.
//
/**
* 左边界 l（第一个大于等于a的m的倍数）
如果 a % m == 0：a 本身就是 m 的倍数，l = a
否则：l = a / m * m + m，即大于 a 的第一个 m 的倍数
a / m 是 a 除以 m 的整数部分
a / m * m 是小于等于 a 的最大 m 的倍数
a / m * m + m 是大于 a 的第一个 m 的倍数
右边界 r（最后一个小于等于b的m的倍数）
如果 b % m == 0：b 本身就是 m 的倍数，r = b
否则：r = b / m * m，即小于等于 b 的最大 m 的倍数
 *
*(r - l) / m + 1：计算 [l, r] 范围内 m 的倍数个数
这是等差数列项数公式：(末项 - 首项) / 公差 + 1
 *
* q = a / m  (整数除法)
=> q ≤ a/m < q + 1
=> q * m ≤ a < (q + 1) * m
=> a / m * m ≤ a < (a / m + 1) * m
所以 a / m * m ≤ a，即 a / m * m 不大于 a。

为什么是最大的 m 的倍数
设 k 是任意满足 k ≤ a 的 m 的倍数，即 k = p * m（其中 p 是正整数）：

p * m ≤ a
p ≤ a / m
由于 p 是整数，所以 p ≤ floor(a / m) = a / m（整数除法）
所以 k = p * m ≤ (a / m) * m
这说明 (a / m) * m 是所有不超过 a 的 m 的倍数中最大的。
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int gcd(const int a, const int b) { return b ? gcd(b, a % b) : a; }

int main() {
    fast;
    int x, y, a, b, l, r; cin >> x >> y >> a >> b;
    const int n = gcd(x, y), m = x * y / n;// 计算最大公约数 最小公倍数
    if (a % m == 0) l = a; else l = a / m * m + m;
    if (b % m == 0) r = b; else r = b / m * m;
    cout << (r - l) / m + 1 << '\n';
    return 0;
}