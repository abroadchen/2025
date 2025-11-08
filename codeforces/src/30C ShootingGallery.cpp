//
// Created by Psy.C on 2025/9/21.
//
/*
 *d[i]表示以节点i结尾能得到的最大收益
 *
 *
*条件来源于相对论中的时空间隔概念。将其变形为： (Δt)² - (Δx)² - (Δy)² ≥ 0

这表示从节点j到节点i的移动速度不超过光速（在这里是1），即在物理上是可能的转移
 *
 *
 *
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 1010;
int n;
double d[N];

struct Node {
    int x, y, t;// x,y坐标和时间t
    double p;// 该节点的收益值
    friend bool operator<(const Node& a, const Node& b) { return a.t < b.t; }
} a[N];// 节点数组

int main() {
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) scanf("%d %d %d %lf",&a[i].x, &a[i].y, &a[i].t, &a[i].p);

    double res = 0;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        d[i] = a[i].p;// 初始化：只选择当前节点的收益
        for (int j = 1; j < i; ++j) {// 检查所有在当前节点之前的时间节点
            if (pow(a[j].t - a[i].t, 2) - pow(a[i].x - a[j].x, 2) - pow(a[i].y - a[j].y, 2) > -1e-9)
                d[i] = max(d[i], d[j] + a[i].p);
        }
        res = max(res, d[i]);
    }

    printf("%.9lf\n", res);

    return 0;
}