//
// Created by Psy.C on 2025/12/22.
//
/*
*n：总的元素个数
k：不同的数字种类数（使用1到k这k个不同的数字）
 *每种数字至少要出现3次才能满足某种约束条件
 *输出前k-1个数字，分别是2, 3, 4, ..., k（跳过了数字1）
 *输出数字1
 *2, 3, 4, ..., k, 1（这是一个1到k的排列）
 *
*初始化：i=1（要输出的数字），j=k（当前位置，从第k+1个位置开始）
循环条件：j < n（还没输出完n个数字）
更新：每次j自增1
 *输出当前数字i
 *i自增1，准备输出下一个数字
 *如果i超过了k，则重置i为1，形成循环：1, 2, 3, ..., k, 1, 2, 3, ...
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    if (n / k < 3) { cout << "-1\n"; return 0; }
    for (int i = 1; i < k; ++i) cout << i + 1 << ' ';
    cout << "1 ";
    for (int i = 1, j = k; j < n; ++j) {
        cout << i << ' ';
        ++i;
        if (i > k) i = 1;
    }
    cout << '\n';
    return 0;
}