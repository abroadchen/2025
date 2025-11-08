//
// Created by Psy.C on 2025/10/16.
//
/*
*定义一个最大顶点数为 40010 的常量 N。
变量 n 存储多边形顶点的数量
 *创建一个大小为 N 的数组 p[]，每个元素都是 vec 类型的对象，用于存储所有多边形顶点的位置
 *
 *使用双指针方法遍历每条边 (i, next(i))，同时维护另一个指针 j 来追踪最远点。
*当前向量 (next(j)-j) 与 (next(i)-i) 的夹角仍为锐角（内积大于零）时继续移动 j 指针；
更新累积面积 s，累加三角形面积（利用叉积绝对值）。
 *
*计算从当前点 i 到对面点 j 的垂线距离 b（垂直于边 i -> next(i)）：
c: 点 i 到 j 距离；
a: 投影长度（点到直线的距离在边上投影）；
b: 实际垂直高度。
 *
 *将当前面积差更新为更小的那个值。
 *移动起点后调整总面积 s，减去刚离开的那部分区域面积。
 *
 *
*p[i]: 多边形的第 i 个顶点的坐标位置（一个二维向量）
nxt(i): 返回 (i+1) % n，即第 i 个顶点的下一个顶点的索引
p[nxt(i)]: 多边形第 i 个顶点的下一个顶点的坐标位置
p[i] - p[nxt(i)]: 两个点坐标相减，得到从 p[nxt(i)] 指向 p[i] 的向量
 *
 *
 */
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 40010;
int n;

class vec {
public:
    double x, y;
    vec() {}
    vec(double dx, double dy) : x(dx), y(dy) {}
    double operator*(const vec& o) const { return x * o.y - y * o.x; }
    double operator^(const vec& o) const { return x * o.x + y * o.y; }
    vec operator-(const vec& o) const { return vec(x - o.x, y - o.y); }
    vec operator/(const double& o) const { return vec(x / o, y / o); }
    double len() { return sqrt(x * x + y * y); }
} p[N];
int nxt(int x) { return (x + 1) % n; }

double solve() {
    double ret(1e18), s(0);
    for (int i = 0, j = 1; i < n; ++i) {
        while (((p[nxt(j)] - p[j]) ^ (p[nxt(i)] - p[i])) > 0) {
            s += fabs((p[j] - p[i]) * (p[nxt(j)] - p[i]));
            j = nxt(j);
        }
        double c = (p[i] - p[j]).len(),
        a = ((p[i] - p[nxt(i)]) * (p[i] - p[j])) / (p[i] - p[nxt(i)]).len(),
        b = sqrt(c * c - a * a);
        ret = min(ret, fabs(fabs(s) - fabs(a * b)));
        s -= fabs((p[j] - p[i]) * (p[nxt(i)] - p[i]));
    }
    return ret / 2;
}


int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
    double ans = solve();
    reverse(p, p + n);
    ans = min(ans, solve());
    printf("%.12lf\n", ans);
    return 0;
}