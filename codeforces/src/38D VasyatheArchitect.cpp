//
// Created by Psy.C on 2025/9/23.
//

#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1e2 + 10;
int n;
double x1, x2, y1, y2;

struct Node {
    double x1, x2, y1, y2;//矩形的边界坐标
    double x, y;//矩形的质心坐标
    double m;//质量（基于高度计算）
    Node() {}
    Node (int a, int b, int c, int d): x1(a), x2(c), y1(b), y2(d) {
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        x = (x1 + x2) / 2;//计算质心坐标
        y = (y1 + y2) / 2;
        m = y2 - y1;//计算质量：m = (y2-y1)³（高度的三次方）
        m = m * m * m;
    }
} b[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        b[i] = Node(x1, y1, x2, y2);//为每个物体创建Node对象并存储在数组b中
    }

    for (int i = 2; i <= n; ++i) {
        double x = b[i].x, y = b[i].y, m = b[i].m;
        for (int j = i - 1; j >= 1; --j) {
            if (x < b[j].x1 || x > b[j].x2 || y < b[j].y1 || y > b[j].y2) {
                printf("%d\n", i - 1);//表示前i-1个物体可以稳定堆叠
                return 0;
            }//新质心 = (m₁×质心₁ + m₂×质心₂)/(m₁ + m₂)
            x += (b[j].x - x) * b[j].m / (m + b[j].m);
            y += (b[j].y - y) * b[j].m / (m + b[j].m);
            m = m + b[j].m;//累加质量
        }
    }

    printf("%d\n", n);

    return 0;
}