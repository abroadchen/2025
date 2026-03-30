//
// Created by Psy.C on 2026/3/30.
//
/**
是否存在非负整数 x, y，使得 ax + by = c
枚举 x 的所有可能值（0 到 ⌊c/a⌋）
对于每个 x = i，检查 (c - a*i) 是否能被 b 整除
如果能整除，则 y = (c - a*i) / b，且 y ≥ 0

O(min(c/a, c/b)) = O(c/min(a,b))
最坏情况下需要 O(c) 时间

方程 ax + by = c 有整数解 ⟺ gcd(a,b) | c
但题目要求非负整数解，所以仍需枚举
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b, c;
int main() {
    fast;
    cin >> a >> b >> c;
    bool flag = false;
    for (int i = 0; i <= c/a; ++i)
        if ((c - i*a) % b == 0) {
            flag = true;
            break;
        }
    cout << (flag ? "Yes\n" : "No\n");
    return 0;
}