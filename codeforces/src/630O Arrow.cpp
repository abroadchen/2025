//
// Created by Psy.C on 2026/3/29.
//
/**
(px, py): 物体中心坐标
(vx, vy): 移动方向向量
a: 物体宽度
b: 物体长度（前进方向）
c: 物体宽度（侧向）
d: 物体长度（后退方向）
csx 和 csy 是方向余弦，表示运动方向的单位向量

点1：前方中点
在中心点沿运动方向前进距离b的位置
点2和点7：左右前侧点
这是垂直于运动方向的偏移
旋转90度：(csx, csy) → (-csy, csx) 和 (csy, -csx)
点3和点6：左右后侧点
与前侧点相似，但使用宽度c而不是a
点4和点5：后方角落点
从后侧点向反方向移动距离d

2 -------- 1 -------- 7
|                    |
|                    |
3 ------------------ 6
|                    |
4 ------------------ 5

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

double px, py, vx, vy, a, b, c, d, x[11], y[11];
int main() {
    fast;
    cin >> px >> py >> vx >> vy >> a >> b >> c >> d;
    double csx = vx/sqrt(vx*vx+vy*vy), csy = vy/sqrt(vx*vx+vy*vy);
    x[1] = px+b*csx; y[1] = py+b*csy;
    x[2]=px-(a/2)*csy;y[2]=py+(a/2)*csx;//左前方
    x[7]=px+(a/2)*csy;y[7]=py-(a/2)*csx;//右前方
    x[3]=px-(c/2)*csy;y[3]=py+(c/2)*csx;//左后方
    x[6]=px+(c/2)*csy;y[6]=py-(c/2)*csx;//右后方
    x[4]=x[3]-d*csx;y[4]=y[3]-d*csy;//左后角
    x[5]=x[6]-d*csx;y[5]=y[6]-d*csy;//右后角
    for(int i=1;i<=7;i++)
        printf("%.10lf %.10lf\n",x[i],y[i]);
    return 0;
}