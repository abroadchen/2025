//
// Created by Psy.C on 2026/10/12.
//
/**
fac 从 1 开始，每轮 fac *= 2：经过 i 轮后 fac = 2^i。
循环到第 i 轮：若 2^i > m，则记录 k = i 并 break。
若中途 break（k≠0）‍：输出 m。
若 n 轮都跑完没 break（k==0）‍：此时 fac = 2^n，输出 m % (2^n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m;
int main() {
    fast;
    cin >> n >> m;
    int fac = 1, k = 0;
    for (int i = 1; i <= n; ++i) {
        fac *= 2;
        if (fac > m) { k = i; break; }
    }
    if (!k) cout << m%fac << '\n'; else cout << m << '\n';
    return 0;
}