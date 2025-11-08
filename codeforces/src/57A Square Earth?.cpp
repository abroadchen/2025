//
// Created by Psy.C on 2025/10/22.
//
/*
 *n表示正方形的边长，(x1,y1)和(x2,y2)是两个点的坐标
 *
*将第一个点的坐标(x1,y1)转换为一维距离表示
这是将正方形边界上的点映射到一条线段上的算法：
如果点在底边(y=0)，距离为x坐标值
如果点在右边(x=n)，距离为n+y坐标值
如果点在顶边(y=n)，距离为3*n-x坐标值
如果点在左边(x=0)，距离为4*n-y坐标值
 *对第二个点(x2,y2)进行相同的坐标转换处理
 *
*计算两点间在一维线段上的距离d
由于正方形边界是一个环形，两点间有两种路径：顺时针和逆时针
4*n-d表示另一种路径的长度
输出较短路径的长度
 *
 */
#include <cstdlib>
#include <ios>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    ll x, y, n, x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;

    if (y1 == 0) x = x1;
    else if (x1 == n) x = n + y1;
    else if (y1 == n) x = 3 * n - x1;
    else x = 4 * n - y1;

    if (y2 == 0) y = x2;
    else if (x2 == n) y = n + y2;
    else if (y2 == n) y = 3 * n - x2;
    else y = 4 * n - y2;

    ll d = abs(x - y);
    cout << min(d, 4 * n - d) << '\n';
    return 0;
}