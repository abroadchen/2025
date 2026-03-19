//
// Created by Psy.C on 2026/3/19.
//
/**
r为圆弧半径，a,b为目标区间端点 l为圆弧长度
double x = l/r：计算圆心角（弧度制）
A = r*(1-cos(x))：水平位移（弦长的水平分量）
B = r*sin(x)：垂直位移（弦长的垂直分量）
sqrt(A*A+B*B)：弦长（直线距离）
l + sqrt(A*A+B*B) >= b - a：圆弧长度 + 弦长 是否大于等于目标区间长度

测试用例数、圆弧半径、速度 目标区间[a, b]

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

double r, a, b;
bool check(double l) {
    double x = l/r, A = r*(1-cos(x)), B = r*sin(x);
    return l + sqrt(A*A+B*B) >= b - a;
}

int n;
double v;
int main() {
    fast;
    cin >> n >> r >> v;
    for (int i = 1; i <= n; ++i) {
        cin >> a >> b;
        double l = 0, r = b - a, ans = 0;
        for (int j = 1; j <= 50; ++j) {
            if (double mid = (l + r) / 2.; check(mid))
                ans = mid, r = mid;
            else l = mid;
        }
        printf("%.10lf\n", ans/v);
    }
    return 0;
}