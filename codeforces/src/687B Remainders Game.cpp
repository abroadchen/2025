//
// Created by Psy.C on 2026/4/15.
//
/**
初始化：t=1，作为累积LCM的变量
循环计算：
每次计算当前LCM与下一个数的最小公倍数
关键优化：每次计算后对k取模，防止数值溢出
使用质因数分解来计算LCM
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ull unsigned long long
using namespace std;
constexpr int N = 1e6+5;
int n;

ull gcd(ull a, ull b) {
    return b == 0 ? a : gcd(b, a % b);
}
ull lcm(ull a, ull b) {
    return a*b/gcd(a, b);
}

ull k, a[N];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    ull t = 1;
    for (int i = 0; i < n; ++i) {
        t = lcm(t, a[i]); t %= k;
    }
    if (t % k == 0) cout << "Yes\n"; else cout << "No\n";
    return 0;
}