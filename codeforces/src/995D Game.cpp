//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
n、r：n 决定数组长度，r 是更新次数。
w = 1<<n → 数组长度是 2^n（即 2 的 n 次方）。
读入 w 个元素，同时累加到 ans（总和）。
输出初始均值 ans / w（约 8 位小数）
读入下标 j 和新的值 x。
更新总和：
ans -= a[j]：把旧值从总和中减去；
a[j] = x：写入新值；
ans += a[j]（即 x）：把新值加回总和。
输出新的均值 ans / w。
这就是 O(1) 的单点更新 + 快速求均值：只调整总和增量，不必重扫整个数组
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e6+10;

int n, r, w, j;
double a[N], ans, x;
int main() {
    fast;
    cin >> n >> r; w = 1<<n;
    for (int i = 0; i < w; i++) cin >> a[i], ans += a[i];
    printf("%.8lf\n", ans/w);
    for (int i = 1; i <= r; i++) {
        cin >> j >> x;
        ans -= a[j]; a[j] = x; ans += a[j];
        printf("%.8lf\n", ans/w);
    }
    return 0;
}