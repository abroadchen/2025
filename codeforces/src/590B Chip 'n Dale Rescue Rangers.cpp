//
// Created by Psy.C on 2026/3/18.
//
/**
sqr(x): 计算x的平方
get(x, y): 计算点(x,y)到原点的距离（欧几里得距离）
vx, vy: 速度向量的x,y分量
px, py: 目标点坐标
v: 速率
t: 时间参数
check(x, flag): 检查函数
cx, cy: 在时间x时的位置
dis: 当前位置到目标点的距离
如果flag=1，减去v*t（调整距离）
如果距离≤v*x（可达），返回1
fx, fy: 起始点坐标
wx, wy: 第二种速度向量

将目标点坐标相对于起始点调整
计算时间t后第一个速度方向能达到的位置
计算该位置到目标的距离
如果在时间t内可以直接到达目标点
二分查找最小时间
check(mid, 0): 不减去v*t
输出精确到12位小数的结果
否则需要切换到第二套速度向量
将目标点调整为相对于时间t后位置的坐标
切换到新的速度向量(wx, wy)
二分查找额外所需时间
check(mid, 1): 减去v*t（考虑之前已走的时间）
输出总时间（已用时间t + 额外时间）


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-8
using namespace std;

double sqr(double x) { return x * x; }
double get(double x, double y) { return sqrt(sqr(x) + sqr(y)); }

double vx, vy, px, py, v, t;
int check(double x, int flag) {
    double cx = vx*x, cy = vy*x,
    dis = get(cx - px, cy - py);
    if (flag) dis -= v*t;
    if (dis <= v*x) return 1;
    return 0;
}

double fx, fy, wx, wy;
int main() {
    fast;
    cin >> fx >> fy >> px >> py >> v >> t >> vx >> vy >> wx >> wy;
    px -= fx, py -= fy;
    double cx = vx*t, cy = vy*t, dis = get(cx - px, cy - py);
    if (dis <= t*v) {
        double l = 0, r = t;
        while (r - l >= eps) {
            double mid = (l + r) / 2;
            if (check(mid, 0)) r = mid;
            else l = mid;
        }
        printf("%.12lf", l);
    } else {
        px -= cx, py -= cy; vx = wx, vy = wy;
        double l = 0, r = 1e9;
        while (r - l > eps) {
            double mid = (l + r) / 2;
            if (check(mid, 1)) r = mid;
            else l = mid;
        }
        printf("%.12lf", l + t);
    }
    return 0;
}