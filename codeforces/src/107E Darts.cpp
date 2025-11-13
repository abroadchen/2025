//
// Created by Psy.C on 2025/11/13.
//
/*
*声明变量n（多边形数量）
声明pair数组c，用于存储交点信息
 *声明三维数组p，存储多边形顶点（最多600个多边形，每个多边形5个点）
 *
*定义符号函数sgn：
如果x接近0（在eps范围内），返回0
如果x > 0，返回1
如果x < 0，返回-1
用于处理浮点数比较
 *
*定义叉积函数cross：
计算向量(p1→p2)和向量(p1→p3)的叉积
用于判断点相对于线段的位置关系
 *
*定义线段参数计算函数seg：
计算点p1在直线p2→p3上的参数值
如果直线不是垂直的，用x坐标计算
否则用y坐标计算
 *
 *定义solve函数，用于计算总面积
*遍历每个多边形的每条边
初始化交点数组c，添加起点0和终点1
*对于其他多边形的每条边
计算端点相对于当前边的位置（通过叉积符号）
*如果两个端点都在当前边上（共线）：
计算方向向量
如果方向相同且编号较小，则记录交点参数
*如果边相交：
计算交点在当前边上的参数位置
记录交点信息（参数值和类型标记）
*对交点按参数排序
计算被覆盖的线段长度：
使用扫描线算法
d为覆盖计数器，0表示未被覆盖
累计未被覆盖的长度s
*计算当前边对总面积的贡献
累加到总和sum中
 *
*循环读入多边形数据直到文件结束
读入每个多边形的4个顶点
计算每个多边形的面积（使用鞋带公式）
如果面积为负，调整顶点顺序
输出总面积与solve()结果的比值
 *
 *
 *
 */
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

const double eps = 1e-10;
int n;
pair<double, int> c[10010];

struct Node { double x, y; } p[600][5];
int sgn(double x) {
    if (fabs(x) < eps) return 0;
    return x > 0 ? 1 : -1;
}

double cross(Node p1, Node p2, Node p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

double dot(Node a, Node b) { return a.x * b.x + a.y * b.y; }

double seg(Node p1, Node p2, Node p3) {
    if (sgn(p2.x - p3.x)) return (p1.x - p2.x) / (p3.x - p2.x);
    return (p1.y - p2.y) / (p3.y - p2.y);
}

double solve() {
    int i, j, ii, jj, ta, tb, r, d;
    double z, w, s, sum(0), tc, td;
    Node t1, t2;
    for (i = 0; i < n; ++i) for (ii = 0; ii < 4; ++ii) {
        r = 0;
        c[r++] = {0., 0}; c[r++] = {1., 0};
        for (j = 0; j < n; ++j) if (i - j) {
            for (jj = 0; jj < 4; ++jj) {
                ta = sgn(cross(p[i][ii], p[i][ii+1], p[j][jj]));
                tb = sgn(cross(p[i][ii], p[i][ii+1], p[j][jj+1]));
                if (!ta && !tb) {
                    t1.x = p[j][jj+1].x - p[j][jj].x;
                    t1.y = p[j][jj+1].y - p[j][jj].y;
                    t2.x = p[i][ii+1].x - p[i][ii].x;
                    t2.y = p[i][ii+1].y - p[i][ii].y;
                    if (sgn(dot(t1, t2)) > 0 && j < i) {
                        c[r++] = {seg(p[j][jj],p[i][ii],p[i][ii+1]), 1};
                        c[r++] = {seg(p[j][jj+1],p[i][ii],p[i][ii+1]), -1};
                    }
                } else if (ta >= 0 && tb < 0) {
                    tc = cross(p[j][jj],p[j][jj+1],p[i][ii]);
                    td = cross(p[j][jj],p[j][jj+1],p[i][ii+1]);
                    c[r++] = {tc/(tc-td), 1};
                } else if (ta < 0 && tb >= 0) {
                    tc = cross(p[j][jj],p[j][jj+1],p[i][ii]);
                    td = cross(p[j][jj],p[j][jj+1],p[i][ii+1]);
                    c[r++] = {tc/(tc-td), -1};
                }
            }
        }
        sort(c, c + r);
        z = min(max(c[0].first, 0.), 1.);
        d = c[0].second;
        s = 0;
        for (j = 1; j < r; ++j) {
            w = min(max(c[j].first, 0.), 1.);
            if (!d) s += w - z;
            d += c[j].second;
            z = w;
        }
        t1.x = t1.y = 0;
        sum += cross(t1, p[i][ii],p[i][ii+1])*s;
    }
    return sum;
}

int main() {
    int i, j; double area, t;
    while (~scanf("%d", &n)) {
        area = 0;
        for (i = 0; i < n; ++i) {
            for (j = 0; j < 4; ++j) scanf("%lf%lf", &p[i][j].x, &p[i][j].y);
            p[i][4] = p[i][0]; t = 0;
            for (j = 1; j <= 4; ++j)
                t += p[i][j - 1].x * p[i][j].y - p[i][j - 1].y * p[i][j].x;
            area += fabs(t);
            if (sgn(t) < 0) swap(p[i][1], p[i][3]);
        }
        printf("%.10lf\n", area/solve());
    }
    return 0;
}