//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
N=4：数组下标 1..3 放三个数，多留一位。
a[]：存三个数值。
m：后面会放最小值
读入三个数。
m = 三者最小值
循环从 i = m+2 开始向下扫描（m 是 min，m+2 是理论上能取到的最大 i，因为 i-2 <= a[1] 中 a[1] 恰好是最小值 m 时 i 最大为 m+2）。
if (i <= a[3] && i-1 <= a[2] && i-2 <= a[1])：检验三层阶梯约束。因为从大到小扫，第一个满足条件的 i 就是最大可行值。
满足后输出 i*3 - 3 并终止。
否则 i 继续减小；若扫完都找不到，循环自然结束，函数返回 0（此时不输出任何东西）
程序在 [3, m+2] 区间向下扫描满足三层阶梯递减约束 (i, i-1, i-2) 均≤对应 a 的最大 i，并输出三层的总数 3i-3
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 4;

int a[N], m;
int main() {
    fast;
    cin >> a[1] >> a[2] >> a[3]; m = min(min(a[1],a[2]),a[3]);
    for (int i = m+2; i >= 3; --i)
        if (i <= a[3] && i-1 <= a[2] && i-2 <= a[1]) {
            cout << i*3 - 3;
            return 0;
        }
    return 0;
}