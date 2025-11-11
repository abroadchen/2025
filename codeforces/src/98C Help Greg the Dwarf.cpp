//
// Created by Psy.C on 2025/11/11.
//
/*
*在角度范围[0, π/2]内，以eps为步长进行遍历
对每个角度t计算f(t)的值
更新ans为当前最小值
这是在寻找函数f(t)在第一象限内的最小值
 *
 */
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

const double pi = 3.1415926, eps = 1e-7, inf = 1e12;
int a, b, l;
double ans = inf;

double f(double t) {//角度t
    double s = sin(t), c = cos(t);
    return a * c + b * s - l * s * c;
}

int main() {
    scanf("%d%d%d", &a, &b, &l);
    if (l <= a) { printf("%.8lf\n", (double)min(l, b)); return 0;}
    if (l <= b) { printf("%.8lf\n", (double)min(l, a)); return 0;}
    for (double t = 0; t <= pi / 2; t += eps) {
        ans = min(ans, f(t));//寻找函数f(t)在第一象限内的最小值
    }
    if (ans < eps) printf("My poor head =(\n");
    else printf("%.8lf\n", ans);
    return 0;
}