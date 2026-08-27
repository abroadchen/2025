//
// Created by Psy.C on 2026/8/27.
//
/**
- - x ：点的横坐标。
- y ：点的纵坐标。
- a[5] ：存储 输入的三个顶点 （下标1~3使用，下标0预留）。
- ans[1000] ：存储 计算出的所有第四个顶点 （最多3个，留足余量）。
- int k = 0 ：计数器，记录当前已存储的答案数量，同时作为 ans 数组的写入下标。

快速添加一个答案点 到 ans 数组中：
- k++ ：先自增计数器（保证下标从1开始，与后续 for 循环输出匹配）。
- ans[k].x = x; ans[k].y = y ：将传入的坐标 (x, y) 存入 ans[k]

- A + D = B + C （中点公式： (A+D)/2 = (B+C)/2 ）
- 因此： D = B + C - A
- 第一行 ： D = a1 + a2 - a3 ，存入 ans[1] 。
- 第二行 ： D = a1 + a3 - a2 ，存入 ans[2] 。
- 第三行 ： D = a2 + a3 - a1 ，存入 ans[3]
- cout << k << '\n' ：第一行输出答案的数量（通常为3，若三点共线则可能少于3）。
- 循环输出每个答案 ： ans[i] 的横纵坐标用空格分隔，每个点占一行
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

struct node { int x, y; } a[5], ans[1000];

int k = 0;
void init(int x, int y) {
    k++;
    ans[k].x = x; ans[k].y = y;
}

int main() {
    fast;
    for (int i = 1; i <= 3; ++i)
        cin >> a[i].x >> a[i].y;//循环读取三个点的坐标
    //将三个点的坐标分别提取到局部变量 x1, y1, x2, y2, x3, y3
    int x1 = a[1].x, y1 = a[1].y, x2 = a[2].x, y2 = a[2].y, x3 = a[3].x, y3 = a[3].y;
    int a0 = x1 + x2 - x3, b0 = y1 + y2 - y3; init(a0, b0);
    a0 = x1 + x3 - x2, b0 = y1 + y3 - y2; init(a0, b0);
    a0 = x3 + x2 - x1, b0 = y2 + y3 - y1; init(a0, b0);
    cout << k << '\n';
    for (int i = 1; i <= k; ++i)
        cout << ans[i].x << ' ' << ans[i].y << '\n';
    return 0;
}