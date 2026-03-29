//
// Created by Psy.C on 2026/3/29.
//
/**
一旦某一位变成1，就永远是1（不可逆）
这意味着：

a 包含了第一个数组中所有数字的二进制位的"并集"
b 包含了第二个数组中所有数字的二进制位的"并集"

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a, b;
int main() {
    fast;
    cin >> n >> a;
    for (int i = 1, x; i < n; ++i) {
        cin >> x; a |= x;
    }
    cin >> b;
    for (int i = 1, x; i < n; ++i) {
        cin >> x; b |= x;
    }
    cout << a + b;
    return 0;
}