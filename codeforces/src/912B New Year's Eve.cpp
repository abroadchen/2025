//
// Created by Psy.C on 2026/10/12.
//
/**
k=1 时只能用 n 本身，所以答案就是 n
当 n >> b 非零时自增 b。
效果：b 是使 n >> b 第一次变为 0 的移位次数，即 n 的二进制有效位数（floor(log2(n)) + 1）
(1ll<<b)-1：把 1 左移 b 位得 1000...0，减 1 得 111...1（b 个 1）。这是不小于 n 的最小的"全 1 二进制"数（大于等于 n 的 Mersenne 型数，实际上因为 b 是 n 的位数，它一定 ≥ n）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, k;
int main() {
    fast;
    cin >> n >> k;
    if (k == 1) { cout << n << '\n'; return 0; }
    int b = 0;
    for (; n>>b; ++b) {}
    cout << (1ll<<b)-1 << '\n';
    return 0;
}