//
// Created by Psy.C on 2025/10/20.
//
/*
 *声明Point类型的数组p，大小为N，用于存储多边形的顶点
 *读取多边形顶点数量n
 *读入n个顶点的坐标
 *将第一个点复制到第n个位置，方便后续循环处理边
 *读取查询点的数量t
 *读取查询点q的坐标
*检查查询点是否在多边形内部：

计算从查询点到每条边的两个端点的向量叉积
如果叉积小于等于0，则计数增加
这里使用了叉积判断点与边的相对位置关系
 *如果查询点不在多边形内部，则输出0并继续下一个查询
 *
 *初始化sum为组合数C(n,3)，即从n个顶点中选择3个构成三角形的总数
 *初始化num，用于记录对于当前点i可见的点的数量
*使用双指针技术找到从点i出发相对于查询点q可见的所有点：

当叉积小于等于0时，说明点j在从点i观察q的视线范围内
统计这样的点的数量
 *从总的三角形数量中减去那些包含不可见区域的三角形数量
 */
#include <cstdio>
#define eps 1e-8
using namespace std;

typedef long long ll;
const int N = 100100;
int sgn(double x) { return (x > eps) - (x < -eps); }
struct Point {
    double x, y;
    Point(double a=0, double b=0) : x(a), y(b) {}
    Point operator+(const Point& o) const { return Point(x+o.x, y+o.y); }
    Point operator-(const Point& o) const { return Point(x-o.x, y-o.y); }
    Point operator*(const double& o) const { return Point(x*o, y*o); }
    Point operator/(const double& o) const { return Point(x/o, y/o); }
    double operator*(const Point& o) const { return x*o.x + y*o.y; }
    double operator^(const Point& o) const { return x*o.y - y*o.x; }
} p[N];



int main() {

    ll n;
    while (scanf("%lld", &n) != EOF) {
        for (int i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
        p[n] = p[0];
        int t; scanf("%d", &t);
        while (t--) {
            Point q; scanf("%lf%lf", &q.x, &q.y);
            int f(0);
            for (int i = 0; i < n; ++i) {
                if (sgn((p[i] - q) ^ (p[i + 1] - q)) <= 0) f++;
            }
            if (f != n) {
                printf("0\n");
                continue;
            }
            ll num, sum(n * (n - 1) * (n - 2) / 6);
            int j(0);
            for (int i = 0; i < n; ++i) {
                if (i == 0) num = 0;
                else num = num - 1;
                while (sgn((p[i] - q) ^ (p[j] - q)) <= 0) {
                    if (j != i) num++;
                    j = (j + 1) % n;
                }
                sum -= num * (num - 1) / 2;
            }
            printf("%lld\n", sum);
        }
    }

    return 0;
}