//
// Created by Psy.C on 2025/9/26.
//
/*
*定义常量N为5005，表示最大点数
声明全局整型变量n，表示实际点数
 *
 *
*双重嵌套循环，遍历所有可能的点组合：
外层循环i从2到n
内层循环j从i+1到n
对于每组(i,j)组合，计算三角形的周长：
点1到点i的距离 + 点1到点j的距离 + 点i到点j的距离
使用min函数更新最小周长minn
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 5005;
int n;

struct Point {
    double x, y, z;
} p[N];

double dis(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) +
        (a.z - b.z) * (a.z - b.z));
}

int main() {

    double minn = 1e100;

    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].z);

    for (int i = 2; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            minn = min(minn, dis(p[1], p[i]) + dis(p[1], p[j]) +
                dis(p[i], p[j]));
    printf("%.10f\n", minn / 2.0);
    return 0;
}