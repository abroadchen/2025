//
// Created by Psy.C on 2025/12/12.
//
/*
*f数组用于存储期望值相关的计算结果
g数组用于存储概率累积相关的计算结果
 *
 *(g[i-1] + 1)表示在前一步基础上加1，然后乘以当前概率p
*计算f[i]的第一部分：从前一步的f值中减去g[i-1]的平方
这是在更新期望值的计算
 *
*第一行：将(g[i-1]+1)的平方加到f[i]上
第二行：将f[i]乘以当前概率p
这两步完成了对f[i]的一个重要更新
*将前一步的f值乘以(1-p)加到当前f[i]上
这考虑了不发生当前事件的情况
 *
 */
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100003
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    double f[N], g[N]; f[0] = 0; g[0] = 0;
    for (int i = 1; i <= n; ++i) {
        double p; cin >> p;
        g[i] = (g[i-1] + 1) * p;
        f[i] = f[i-1] - g[i-1] * g[i-1];
        f[i] += (g[i-1]+1) * (g[i-1]+1); f[i] *= p;
        f[i] += f[i-1] * (1. - p);
    }
    cout << fixed << setprecision(12) << f[n] << '\n';
    return 0;
}