//
// Created by Psy.C on 2026/4/8.
//
/**
时间复杂度
O(M × n)，其中M = 2,000,000，n ≤ 20，总体约为4亿次操作。
精度分析
使用M=2,000,000个样本点进行采样
理论精度约为 1/√M ≈ 1/1414 ≈ 0.0007，能够保证输出6位小数的准确性

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 20, M = 2e6;
int n, a[N], b[N], s;
double ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 1; i <= M; ++i)
        for (int j = 1; j <= n; ++j)//检查每个条件
            if (i%a[j] == b[j]) {
                s++;
                break;
            }
    ans = s/2000000.;//概率
    printf("%.6lf", ans);
    return 0;
}