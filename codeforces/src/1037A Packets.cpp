//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
i = ⌊log2(x)⌋ + 1
ans 从 1 开始，每一轮迭代都翻倍（ans *= 2），即 ans = 1, 2, 4, 8, 16, ...。
循环变量 i 对应 ans 的"幂次"：初始 ans=1=2^0，第一次翻倍后 ans=2=2^1，第 i 次循环时 ans = 2^(i-1)（见下方推导）。
判断条件 ans <= x && x < ans*2 的含义是：x 落在区间 [ans, 2*ans) 内，即 ans ≤ x < 2·ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll x; cin >> x;
    ll ans = 1;
    for (ll i = 1; i <= x; i++) {
        if (ans <= x && x < ans*2) {
            cout << i << '\n';
            break;
        }
        ans *= 2;
    }
    return 0;
}