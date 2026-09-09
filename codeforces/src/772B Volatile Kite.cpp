//
// Created by Psy.C on 2026/9/9.
//
/**
N：数组大小 1e5+100，容纳最多 1e5 个点。
point：二维平面点，存储 x、y 坐标。默认构造 + 带参构造。
a[N]：全局数组，存放多边形所有顶点（按顺序）
以 p0 为基准求向量 p0→p1 与 p0→p2 的二维叉积（数值）。叉积绝对值 = 这两向量构成的平行四边形面积，即三角形 p0-p1-p2 面积的两倍
欧氏距离：两点间直线距离（勾股定理）
读入顶点数 n 和所有顶点坐标。
ans 初始化为极大值 0x7fffffff（约 21 亿，足够大）表示无穷大。
遍历每个顶点 i：
取三个连续顶点 a[i]、a[(i+1)%n]、a[(i+2)%n]（用取模实现环状取点）构成三角形。
area：这个三角形的面积（叉积绝对值 除 2）。
d：第 i 个点与第 i+2 个点（即夹着中间点的两端点）之间的距离，也就是三角形"底边"长度。
area / d：三角形面积 ÷ 底边长度 = 该底边上的高——即第 i+1 个顶点到过 a[i]、a[i+2] 连线的垂向距离。
ans = min(ans, ...)：对所有这样的"顶点到对边直线的垂距"取最小值。
输出最小值，保留 6 位小数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+100;
struct point {
    double x, y;
    point() = default;
    point(double _x, double _y) : x(_x), y(_y) {}
} a[N];

double x_mul(point p0, point p1, point p2) {
    return (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
}
double dis(point p1, point p2) {
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i].x >> a[i].y;
    double ans = 0x7fffffff;
    for (int i = 0; i < n; ++i) {
        double area = fabs(x_mul(a[(i+1)%n], a[i], a[(i+2)%n]))/2.0;
        double d = dis(a[i], a[(i+2)%n]);
        ans = min(ans, area/d);
    }
    printf("%.6f\n", ans);
    return 0;
}