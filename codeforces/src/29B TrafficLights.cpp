//
// Created by Psy.C on 2025/9/20.
//
/*
 *
*l: 总路程长度
d: 第一段路程长度（到交通灯处）
v: 速度
g: 绿灯持续时间
r: 红灯持续时间
 *
*计算到达交通灯处所需时间
t1 = 距离 / 速度
*计算从交通灯处到终点所需时间
t2 = 剩余距离 / 速度
 *
*计算在到达交通灯时，已经完整经历了多少个红绿灯周期
g + r 是一个完整的红绿灯周期时间
 *
*计算在当前周期内已经经过的时间
即在当前红绿灯周期中的位置
 *
*如果到达交通灯时已经是红灯时间（tl >= g），则需要等待到下一个绿灯
等待到下一个周期的开始，即 (u + 1) * (g + r)
 *
 *
 *
 *
 */

#include <cstdio>
using namespace std;

int main() {

    long l, d, v, g, r; scanf("%ld %ld %ld %ld %ld", &l, &d, &v, &g, &r);

    double t1 = 1.0 * d / v;
    double t2 = 1.0 * (l - d) / v;

    long u = t1 / (g + r);
    double tl = t1 - u * (g + r);
    if (tl >= g) t1 = (u + 1) * (g + r);

    printf("%.7lf\n", t1 + t2);

    return 0;
}