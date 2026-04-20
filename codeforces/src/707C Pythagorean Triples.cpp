//
// Created by Psy.C on 2026/4/19.
//
/**
n: 输入的数值
d: 2的幂次因子
如果n ≤ 2，无解，输出-1

提取n中所有因子2
d <<= 1: d *= 2
n >>= 1: n /= 2
循环结束后，n变为奇数部分

对于奇数n，(n, (n²-1)/2, (n²+1)/2) 是一个勾股数组
如果now = 1，说明n = √3，这不是整数解
a = d * now = d * (n²-1)/2
b = d * (now+1) = d * (n²+1)/2
这是考虑了2的幂次因子的完整解

这个问题寻找满足以下条件的勾股数组 (a, b, c)：
a² + b² = c²（勾股定理）
a² + b² + c² = n（额外约束）
从条件2可得：c² + c² = n，即 2c² = n，所以 c = √(n/2)
但实际上，代码的逻辑是基于：
对于奇数n，存在勾股数组 (n, (n²-1)/2, (n²+1)/2)
然后乘以2的幂次因子d来构造一般解
O(log n): 主要是提取因子2的循环
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ull unsigned long long
using namespace std;

ull n, d = 1;
int main() {
    fast;
    cin >> n;
    if (n <= 2) { cout << -1; return 0; }
    if (n%4 == 0) {
        cout << (ll)3*n/4 << ' ' << (ll)5*n/4 << '\n';
        return 0;
    }
    while (n%2 == 0) { d <<= 1; n >>= 1; }
    ull now = (n*n-1)/2;
    if (now == 1) { cout << -1 << '\n'; return 0; }
    cout << d*now << ' ' << d*(now+1) << '\n';
    return 0;
}