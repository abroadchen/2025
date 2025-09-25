//
// Created by Psy.C on 2025/9/24.
//
/*
 *
 *计算点 (x, y) 到原点 (0, 0) 的欧几里得距离的平方（即 x² + y²），
 *并将结果存储在双精度浮点数变量 d 中
 *
 *
 *
 *
 */
#include <cmath>
#include <cstdio>
using namespace std;

int main() {

    long x, y; scanf("%ld %ld\n", &x, &y);
    double d = x * x + y * y;

    long ans = sqrt(d);
    if (ans * ans == d) puts("black");//表示该点正好位于某个整数半径的圆上/
    else {
        if (x * y < 0) ++ans;
        puts(ans % 2 ? "white" : "black");
    }
    return 0;
}