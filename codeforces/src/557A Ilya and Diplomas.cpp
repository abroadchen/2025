//
// Created by Psy.C on 2026/3/11.
//
/**
n: 可分配的总资源数
a1, b1, c1: 三个变量的初始值（最小值）
a2, b2, c2: 三个变量的最大值
读入三个变量的范围：[a1,a2], [b1,b2], [c1,c2]
初始化三个变量为其最小值
从总资源中扣除已分配的基础值

第一阶段: 优先增加a变量到其最大值
如果剩余资源足够，将a提升到最大值a2
否则，将所有剩余资源分配给a
第二阶段: 优先增加b变量到其最大值
逻辑同第一阶段
第三阶段: 将所有剩余资源分配给c变量
输出最终的三元组

时间复杂度: O(1)，常数时间
空间复杂度: O(1)，常数空间
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a1, a2, b1, b2, c1, c2;
int main() {
    fast;
    cin >> n;
    cin >> a1 >> a2 >> b1 >> b2 >> c1 >> c2;
    int a = a1, b = b1, c = c1;
    n = n - a - b - c;
    if (n) {
        if (n >= a2 - a1) { n -= a2 - a1; a = a2; }
        else { a += n; n = 0; }
    }
    if (n) {
        if (n >= b2 - b1) { n -= b2 - b1; b = b2; }
        else { b += n; n = 0; }
    }
    if (n) c += n;
    cout << a << ' ' << b << ' ' << c << '\n';
    return 0;
}