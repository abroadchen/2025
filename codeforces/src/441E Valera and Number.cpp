//
// Created by Psy.C on 2026/2/8.
//
/**
f[N][N]: DP数组，f[i][j]表示经过i轮后有j个元素时的期望值
p: 概率值
x（初始值）、n（轮数）、t（百分比概率）

(x+i)的二进制表示中末尾连续0的个数
第0轮时有i个元素的初始期望值

遍历0到n-1轮
遍历0到n个元素的情况
如果j=0，则不能减1，所以需要if (j)判断

以概率p使元素数量翻倍，同时期望值+1
以概率(1-p)使元素数量-1
 */
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 310
using namespace std;

double f[N][N], p;

int main() {
    fast;
    int x, n, t; cin >> x >> n >> t;
    p = 1.*t/100;
    for (int i = 0; i <= n; ++i) f[0][i] = __builtin_ctz(x+i);
    for (int i = 0; i < n; ++i) for (int j = 0; j <= n; ++j) {
        if (j*2 <= n) f[i+1][j*2] += (f[i][j] + 1) * p;
        if (j) f[i+1][j-1] += f[i][j] * (1 - p);
    }
    //n轮后剩余0个元素的期望值
    cout << fixed << setprecision(10) << f[n][0] << '\n';
    return 0;
}