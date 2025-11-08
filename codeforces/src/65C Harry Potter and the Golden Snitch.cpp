//
// Created by Psy.C on 2025/10/30.
//
/*
*n：点的数量
sx, sy, sz：起点坐标
i：循环变量
tx, ty, tz：临时坐标变量
vp, vs：警察和小偷的速度
声明双精度浮点型数组t[N]：存储时间
 *
*定义Point结构体，包含三维坐标(x,y,z)
声明Point类型数组p[N]：存储所有点的坐标
 *
*循环读取n个点的坐标：
读取整数坐标到临时变量
转换为double类型存储到Point结构体中
 *读取警察速度(vp)、小偷速度(vs)和起点坐标(sx,sy,sz)
 *
 *定义检查函数，判断在时间s时是否能在p2点抓住小偷
*计算小偷从p1到p2所需的时间加上已有时间s：
使用欧几里得距离公式计算两点间距离
除以小偷速度vs得到时间
*计算警察从起点到p2点所需的时间：
计算警察起点到p2的距离
除以警察速度vp得到时间
 *返回警察是否能在小偷之前到达p2点（考虑浮点误差）
 *
*整型：循环变量i，二分查找边界l,r,mid
双精度：二分查找边界ll,rr,mmid
Point类型：临时点tp
*计算小偷到达每个点的时间：
累加从起点到各点的时间
每段距离除以小偷速度vs
 *如果在最后一条边上都无法抓住小偷，则输出"NO"并返回
*如果在第mid条边上可以抓住，则搜索左半部分
否则搜索右半部分
 *
 *初始化在线段上的参数范围[0,1]
*在选定的线段上进行二分查找精确定位：
精度要求为1e-11
 *计算线段上的中间点坐标（线性插值）
*如果可以在该点抓住小偷，则搜索左半部分
否则搜索右半部分
 *计算最终的抓捕点坐标
 *输出"YES"表示可以抓住小偷
 *
 *输出警察到达抓捕点所需的时间（保留10位小数）
 *输出抓捕点的三维坐标（保留10位小数）
 *
*粗略定位：使用二分查找确定在哪条线段上可以抓住小偷
精确定位：在该线段上再次二分查找确定具体的抓捕点
 */
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 10005;
int n, sx, sy, sz, i, tx, ty, tz, vp, vs;
double t[N];

struct Point { double x, y, z; } p[N];

void init() {
    scanf("%d", &n); n++;
    for (i = 1; i <= n; ++i) {
        scanf("%d%d%d", &tx, &ty, &tz);
        p[i].x = tx; p[i].y = ty; p[i].z = tz;
    }
    scanf("%d%d%d%d%d", &vp, &vs, &sx, &sy, &sz);
}

bool check(Point p1, Point p2, double s) {
    double t1, t2;
    t1 = s + sqrt((p2.x - p1.x) * (p2.x - p1.x) +
        (p2.y - p1.y) * (p2.y - p1.y) +
        (p2.z - p1.z) * (p2.z - p1.z)) / vs;
    t2 = sqrt((p2.x - sx) * (p2.x - sx) +
        (p2.y - sy) * (p2.y - sy) +
        (p2.z - sz) * (p2.z - sz)) / vp;
    return t2 <= t1 + 1e-15;
}

void solve() {
    int i, l, r, mid; double ll, rr, mmid; Point tp;
    for (i = 1; i < n; ++i) {
        t[i] = t[i - 1] + sqrt((p[i + 1].x - p[i].x) * (p[i + 1].x - p[i].x) +
            (p[i + 1].y - p[i].y) * (p[i + 1].y - p[i].y) +
            (p[i + 1].z - p[i].z) * (p[i + 1].z - p[i].z)) / vs;
    }
    l = 1, r = n - 1;
    if (!check(p[n - 1], p[n], t[n - 2])) { puts("NO"); return; }
    while (l < r) {
        mid = (l + r) >> 1;
        if (check(p[mid], p[mid + 1], t[mid - 1])) r = mid;
        else l = mid + 1;
    }
    ll = 0, rr = 1;
    while (rr >= ll + 1e-11) {
        mmid = (ll + rr) * 0.5;
        tp.x = p[l].x + (p[l + 1].x - p[l].x) * mmid;
        tp.y = p[l].y + (p[l + 1].y - p[l].y) * mmid;
        tp.z = p[l].z + (p[l + 1].z - p[l].z) * mmid;
        if (check(p[l], tp, t[l - 1])) rr = mmid;
        else ll = mmid;
    }
    tp.x = p[l].x + (p[l + 1].x - p[l].x) * rr;
    tp.y = p[l].y + (p[l + 1].y - p[l].y) * rr;
    tp.z = p[l].z + (p[l + 1].z - p[l].z) * rr;
    puts("YES");
    printf("%.10lf\n", sqrt((tp.x - sx) * (tp.x - sx) +
        (tp.y - sy) * (tp.y - sy) +
        (tp.z - sz) * (tp.z - sz)) / vp);
    printf("%.10lf %.10lf %.10lf\n", tp.x, tp.y, tp.z);
}

int main() {
    init(), solve();
    return 0;
}