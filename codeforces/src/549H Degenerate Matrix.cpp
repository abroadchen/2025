//
// Created by Psy.C on 2026/3/9.
//
/**
a1, a2: a±m
b1, b2: b±m
c1, c2: c±m
d1, d2: d±m
t1: ad乘积的最小值（a±m, d±m的所有组合）
t2: bc乘积的最小值（b±m, c±m的所有组合）
x1: ad乘积的最大值
x2: bc乘积的最大值

如果 [t1, x1] 和 [t2, x2] 有交集，返回false
否则返回true
使得区间[a-m, a+m]×[d-m, d+m]和[b-m, b+m]×[c-m, c+m]的乘积范围不相交
找到最小的m使得两个乘积范围分离
时间复杂度：O(100) = O(1)（固定迭代次数）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

double a, b, c, d;
bool check(double m) {
    double a1 = a + m, a2 = a - m, b1 = b + m, b2 = b - m,
    c1 = c + m, c2 = c - m, d1 = d + m, d2 = d - m,
    t1 = min(min(a1*d1, a1*d2), min(a2*d1, a2*d2)),
    t2 = min(min(b1*c1, b1*c2), min(b2*c1, b2*c2)),
    x1 = max(max(a1*d1, a1*d2), max(a2*d1, a2*d2)),
    x2 = max(max(b1*c1, b1*c2), max(b2*c1, b2*c2));
    if (t1 <= x2 && t2 <= x1) return false;
    return true;
}

double ans;
void get(double l, double r) {
    for (int i = 1; i <= 100; ++i) {
        double mid = (l+r)/2;
        if (check(mid)) ans = l = mid;
        else r = mid;
    }
}


int main() {
    fast;
    cin >> a >> b >> c >> d;
    get(0, 1e9);
    printf("%.10lf\n", ans);
    return 0;
}