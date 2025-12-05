//
// Created by Psy.C on 2025/12/5.
//
/*
*a, b：房间的长和宽
m：初始高度
vx, vy, vz：x, y, z三个方向的速度分量
 *
*计算小球落地时在宽度方向(b方向)的位置：
vy = -vy：反转y方向速度（可能是坐标系转换）
t = m / vy：计算落地时间（从高度m落到地面所需时间）
cnt = static_cast<int>(t * vz / b)：计算在宽度方向上反弹的次数
y1 = t * vz - cnt * b：计算最终在宽度方向上的相对位置
if (cnt % 2) y1 = b - y1：如果反弹奇数次，位置需要镜像
 *
*处理x方向速度：
ret：标记x方向是否需要反转
如果vx>0，保持不变，ret=false
如果vx≤0，取绝对值，ret=true
 *
*计算小球落地时在长度方向(a方向)的位置：
如果vx接近0（即小球几乎垂直下落），落在中心：y2 = a / 2
否则计算复杂轨迹：
s1 = 0.5 * a * vy / vx：计算到达墙壁所需的高度
如果初始高度m小于s1，直接计算落地点
否则减去s1，计算反弹后的轨迹

*根据之前的反转标记调整最终结果
输出结果，保留10位小数
 */
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-8
using namespace std;


int main() {
    fast;
    double a, b, m, vx, vy, vz;
    while (cin >> a >> b >> m) {
        cin >> vx >> vy >> vz;
        vy = -vy;
        double t = m / vy;
        int cnt = static_cast<int>(t * vz / b);
        double y1 = t * vz - cnt * b;
        if (cnt % 2) y1 = b - y1;
        bool ret;
        if (vx > 0) ret = false;
        else ret = true, vx = -vx;
        double y2;
        if (vx <= eps && -vx <= eps) y2 = a / 2.;
        else {
            const double s1 = 0.5 * a * vy / vx;
            if (m < s1) y2 = (s1 - m) * vx / vy;
            else {
                m = m - s1; t = m / vy;
                cnt = static_cast<int>(t * vx / a);
                y2 = t * vx - cnt * a;
                if (cnt % 2) y2 = a - y2;
            }
        }
        if (!ret) y2 = a - y2;
        cout << fixed << setprecision(10) << y2 << ' ' <<
            setprecision(10) << y1 << '\n';
    }
    return 0;
}