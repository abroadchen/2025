//
// Created by Psy.C on 2026/9/1.
//
/**
输入整数 k ，返回 true 表示 k 是质数， false 表示不是质数。
只需要检查 2 ~ √k 范围的因数即可。如果 k 有一个大于 √k 的因数，那必然也有一个小于等于 √k 的因数。
2 遍历到 √k ，如果 k 能被 i 整除 → k 不是质数，立即返回 false 。

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

bool isok(int k) {
    int len = sqrt(k);
    for (int i = 2; i <= len; ++i)
        if (k%i == 0) return false;
    return true;
}

int main() {
    fast;
    int n; cin >> n;
    for (int m = 1; m <= 1000; ++m) {
        int k = n*m + 1;
        if (!isok(k)) { cout << m << '\n'; return 0; }
    }
    return 0;
}