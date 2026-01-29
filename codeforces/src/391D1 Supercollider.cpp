//
// Created by Psy.C on 2026/1/29.
//
/**
* 起点 x 坐标、起点 y 坐标、终点 x 坐标、终点 y 坐标
声明两个数组：xl[N] 存储水平线段，yl[N] 存储垂直线段
 *
*参数 a 和 b 是两个线段
如果线段 a 的 y 坐标在 b 的 y 范围内（交叉判断条件）
并且线段 b 的 x 坐标在 a 的 x 范围内
 *
 * n（垂直线段数量）和 m（水平线段数量）
 *len（线段长度）
 *r[5]（临时存储4个距离值）
 *ans[M]（存储所有交点的距离） q（ans 数组的索引)
 *
*循环读入 n 个垂直线段
读取起点坐标 (sx, sy) 和线段长度
设置终点 x 坐标等于起点 x 坐标（垂直线段）
设置终点 y 坐标 = 起点 y 坐标 + 长度
*循环读入 m 个水平线段
读取起点坐标 (sx, sy) 和线段长度
设置终点 x 坐标 = 起点 x 坐标 + 长度（水平线段）
设置终点 y 坐标等于起点 y 坐标
 *
*x = yl[j].sx：交点的 x 坐标（垂直线段的 x 坐标）
y = xl[i].sy：交点的 y 坐标（水平线段的 y 坐标）
r[1] = sgn(x - xl[i].sx)：交点到水平线段起点的 x 方向距离
r[2] = sgn(x - xl[i].ex)：交点到水平线段终点的 x 方向距离
r[3] = sgn(y - yl[j].sy)：交点到垂直线段起点的 y 方向距离
r[4] = sgn(y - yl[j].ey)：交点到垂直线段终点的 y 方向距离
 *
*++q：q 自增1，准备存储下一个结果
ans[q] = r[1]：将第一个距离存入数组
循环比较并存储四个距离中的最小值到 ans[q]
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1200
#define M 1002000
using namespace std;

struct node { int sx, sy, ex, ey; } xl[N], yl[N];

int sgn(const int x) {//计算绝对值
    if (x >= 0) return x;
    return -x;
}

int cross(const node a, const node b) {
    if (a.sy > b.ey && a.sy < b.sy || a.sy < b.ey && a.sy > b.sy) {
        if (b.sx < a.sx && b.sx > a.ex || b.sx > a.sx && b.sx < a.ex)
            return 1;
    }
    return 0;
}

int main() {
    fast;
    int n, m; cin >> n >> m;
    int i, len, r[5], ans[M], q = -1;
    for (i = 0; i < n; ++i) {
        cin >> yl[i].sx >> yl[i].sy >> len;
        yl[i].ex = yl[i].sx;
        yl[i].ey = yl[i].sy + len;
    }
    for (i = 0; i < m; ++i) {
        cin >> xl[i].sx >> xl[i].sy >> len;
        xl[i].ex = xl[i].sx + len;
        xl[i].ey = xl[i].sy;
    }
    //检查所有水平线段与垂直线段的配对
    for (i = 0; i < m; ++i) for (int j = 0; j < n; ++j) if (cross(xl[i], yl[j])) {
        const int x = yl[j].sx, y = xl[i].sy;
        r[1] = sgn(x - xl[i].sx); r[2] = sgn(x - xl[i].ex);
        r[3] = sgn(y - yl[j].sy); r[4] = sgn(y - yl[j].ey);
        ans[++q] = r[1];
        for (int k = 2; k <= 4; ++k) ans[q] = min(ans[q], r[k]);
    }
    int mx = 0;
    for (i = 0; i <= q; ++i) mx = max(mx, ans[i]);
    cout << mx << '\n';
    return 0;
}