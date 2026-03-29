//
// Created by Psy.C on 2026/3/29.
//
/**
s1 = √3*a²/4: 正四面体底面（等边三角形）面积
h1 = √6*a/3: 正四面体的高
v1 = h1*s1/3: 体积 = (1/3)底面积高
正四面体体积公式为 V = a³/(6√2)
s2 = b²: 底面（正方形）面积
h2 = b/√2: 四棱锥的高
v2 = h2*s2/3: 体积 = (1/3)底面积高
高与边长的关系为 h = b/√2
tan(π/10) = tan(18°): 十度的正切值
cos(π/5) = cos(36°): 五度的余弦值
k: 与正五边形内切圆半径相关的系数
s3 = 5*k*cos(π/5)*c²/2: 正五边形底面面积
h3 = √(1-k²)*c: 五角锥的高
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pi acos(-1.)
using namespace std;

double a, b, c;
int main() {
    fast;
    cin >> a >> b >> c;
    double h1 = sqrt(6)*a/3, s1 = sqrt(3)*a*a/4, v1 = h1*s1/3;
    double h2 = b/sqrt(2), s2 = b*b, v2 = h2*s2/3;
    double k = 1/(2*tan(pi/10)*(1+cos(pi/5))),
    h3 = sqrt(1-k*k)*c, s3 = 5*k*cos(pi/5)*c*c/2, v3 = h3*s3/3;
    printf("%.10lf\n", v1 + v2 + v3);
    return 0;
}