//
// Created by Psy.C on 2026/10/5.
//
/**
b1[10] / b2[10]：分别记录第一组、第二组各 digit（0–9）是否出现过（出现计数）
b、c 用作“是否已取到该组最小 digit”的标记（初值 1）
k1、k2 存两组的各自最小 digit
对每个数不断取 a%10 记录后 a/=10，即逐位拆分，把每一位计入对应 b1/b2
从 0 到 9 扫描，第一个同时出现（b1[i]&&b2[i]）的 digit 就是最小公共 digit，直接输出并结束 （因为从 0 开始，找到的必是最小的）
同样从 0 扫描，用标记 b/c 只取每组第一次遇到的（即最小的）digit，存入 k1、k2
最后把两数中较小者放前面输出，形成最小的两位数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b1[10], b2[10], b(1), c(1), k1, k2;
int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a;
        while (a > 0) { b1[a%10]++; a /= 10; }
    }
    for (int i = 1; i <= m; ++i) {
        cin >> a;
        while (a > 0) { b2[a%10]++; a /= 10; }
    }
    for (int i = 0; i < 10; ++i)
        if (b1[i] && b2[i]) { cout << i; return 0; }
    for (int i = 0; i < 10; ++i) {
        if (b1[i] && b) k1 = i, b = 0;
        if (b2[i] && c) k2 = i, c = 0;
    }
    if (k1 > k2) cout << k2 << k1; else cout << k1 << k2;
    return 0;
}