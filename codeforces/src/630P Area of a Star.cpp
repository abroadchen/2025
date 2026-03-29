//
// Created by Psy.C on 2026/3/29.
//
/**
a + c + b = π/(2n) + π/n + π - 3π/(2n) = π/(2n) + 2π/(2n) + π - 3π/(2n) = π
使用正弦定理：C/sin(c) = r/sin(b)，所以 C = sin(c) * (r/sin(b))
三角形面积公式：S = 0.5 * 两边 * sin(夹角) = 0.5 * r * C * sin(a)
将单个三角形面积乘以 2*n，得到总面积

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pi acos(-1.)
using namespace std;

int n, r;
int main() {
    fast;
    cin >> n >> r;
    double a = pi*1./(2*n), c = pi*1./n, b = pi-a-c;
    double C = sin(c)*(r/sin(b)), S = 0.5*r*C*sin(a);
    S = S*2*n;
    printf("%.12lf\n", S);
    return 0;
}