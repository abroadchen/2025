//
// Created by Psy.C on 2025/11/20.
//
/*
 *判断是否能在大圆内放置n个小圆
*n: 要放置的小圆数量
R: 大圆的半径
r: 小圆的半径
 *
 *大圆半径必须大于等于小圆半径，否则无法放置
*acos(-1) = π（π的计算方法）
acos(-1)/n = π/n
 *
*当n个小圆紧密排列在大圆内时，它们的中心形成一个正n边形
正n边形的外接圆半径是 (R - r)
相邻两个小圆中心之间的距离是 2*(R-r)*sin(π/n)
为了不重叠，这个距离必须 ≥ 2*r
即：(R-r)*sin(π/n) ≥ r
 *
 *当 n = 0 或 n = 1 时，总是可以放置
 *
 */
#include <cmath>
#include <cstdio>
using namespace std;

int main() {
    int n, R, r; scanf("%d%d%d", &n, &R, &r);
    puts(R >= r && ((R - r) * sin(acos(-1)/n) >= r - 1e-8 || n < 2) ? "YES" : "NO");
    return 0;
}