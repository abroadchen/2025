//
// Created by Psy.C on 2025/12/21.
//
/*
 *
*当a和b都不为0时循环：
如果a < b，交换a和b（确保a ≥ b）
计算div = a / b（整数除法）
更新a = a - div * b（相当于a %= b）
累加ans += div
 *
*与欧几里得算法相同：O(log(min(a,b)))
但常数因子较小，因为使用了除法优化
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

void f() {
    ll a, b, ans = 0; cin >> a >> b;
    while (a && b) {
        if (a < b) swap(a, b);
        const ll div = a / b;
        a -= div * b;
        ans += div;
    }
    cout << ans << '\n';
}

int main() {
    fast;
    ll t = 1; cin >> t;
    while (t--) { f(); }
    return 0;
}