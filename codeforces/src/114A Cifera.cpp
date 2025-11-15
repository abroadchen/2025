//
// Created by Psy.C on 2025/11/15.
//
/*
*k: 底数，用于计算幂次
l: 目标值，要检查是否为k的某次幂
k2: 保存原始k值的副本
 *cnt为0，用于记录幂次
*当k小于l时循环执行：
将k乘以k2（即k的幂次递增）
计数器cnt加1
这个循环计算k^1, k^2, k^3, ...直到k^n >= l
 *
 *
 */
#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    ll k, l, k2; cin >> k >> l;
    int cnt(0); k2 = k;
    while (k < l) { k = k * k2; cnt++; }
    if (k == l) cout << "YES\n" << cnt;
    else cout << "NO";
    return 0;
}