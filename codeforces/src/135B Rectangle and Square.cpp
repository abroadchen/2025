//
// Created by Psy.C on 2025/11/19.
//
/*
*x[9]和y[9]：用于存储点的坐标
p[]：初始化为{0,1,2,3,4,5,6,7,8}，用作排列索引数组
 *
*判断当前排列是否满足特定几何条件：
前4个点构成正方形：
四条边相等：d(1,2)=d(2,3)=d(3,4)=d(4,1)
两条对角线相等：d(1,3)=d(2,4)
后4个点构成正方形：
四条边相等：d(5,6)=d(7,8)=d(6,7)=d(5,8)
两条对角线相等：d(5,7)=d(6,8)
 *
 */
#include <cstdio>
#include <iostream>
#define sqr(x) ((x) * (x))
using namespace std;

int x[9], y[9], p[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8
};

int d(int a, int b) {
    return sqr(x[p[a]] - x[p[b]]) + sqr(y[p[a]] - y[p[b]]);//通过p数组间接访问坐标
}

int main() {
    for (int i = 1; i <= 8; ++i) scanf("%d%d", &x[i], &y[i]);
    do {
        if (d(1, 2) == d(2, 3) && d(2, 3) == d(3, 4) &&
            d(3, 4) == d(4, 1) && d(1, 3) == d(2, 4) &&
            d(5, 6) == d(7, 8) && d(6, 7) == d(5, 8) &&
            d(5, 7) == d(6, 8))
            return cout << "YES" << '\n' << p[1] << ' ' << p[2] << ' ' <<
                p[3] << ' ' << p[4] << ' ' << p[5] << ' ' << p[6] << ' ' <<
                    p[7] << ' ' << p[8] << '\n', 0;
    } while (next_permutation(p + 1, p + 9));
    cout << "NO" << '\n';
    return 0;
}