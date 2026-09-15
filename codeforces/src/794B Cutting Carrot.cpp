//
// Created by Psy.C on 2026/9/15.
//
/**
n 表示要等分的份数（合起来是 n 份），h 是三角形的高。两者用 double 接收以保留精度。
这里 n 同时充当了"底边水平长度"——这是这类题的常见打法：底的总区间看作 [0, n]，要切成 n 份。
循环 i = 1 到 n-1（不输出第 0 和第 n 个，因为那是端点和底边）。
公式：res = sqrt( h*h / n * i )
推导（关键）‍：三角形在底边方向上的横截面宽度与离顶点的垂直距离成正比（相似三角形）。若高为 h、总份数 n，第 i 份的"高度刻度"是 h·√(i/n)。把表达式拆开看：
h*h / n * i   =   h² · (i / n)
所以

res = sqrt( h² · (i/n) ) = h · √(i/n)
即第 i 个分界点的高度 = h·√(i/n)。

为什么是开根号？因为三角形的面积与高度的平方成正比（面积随高度平方增长）。要让相邻两份面积相等，高度刻度就必须按平方根递增——这正是 h·√(i/n) 的来历。
原式写成 sqrt(h*h/n*i) 等价于 h* sqrt(i/n)，只是把乘法因子全塞进根号里了
 */
#include <bits/stdc++.h>
using namespace std;


int main() {
    double n, h; cin >> n >> h;
    for (int i = 1; i < n; ++i) {
        double res = sqrt(h*h/n*i);
        printf("%.10f ", res);
    }
    cout << '\n';
    return 0;
}