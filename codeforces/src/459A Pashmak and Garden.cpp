//
// Created by Psy.C on 2026/2/11.
//
/**
x1, y11：输入的第一个点坐标
x2, y2：输入的第二个点坐标
x3, y3, x4, y4：计算得出的另外两个点坐标（用于构造正方形）

时间复杂度：O(1)，直接计算得出结果
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int x1, x2, y11, y2, x3, x4, y3, y4;
bool ok() {
    if (x1 != x2 && y11 != y2) {//两点不在同一水平线或垂直线上（斜线）
        if (abs(x1 - x2) != abs(y11 - y2)) return false;//两点连线不是45度角
        x3 = x1; y3 = y2;
        x4 = x2; y4 = y11;
        return true;
    }
    if (y11 != y2) {//垂直线段
        const int d = abs(y11 - y2);//正方形边长
        x3 = x1 + d; y3 = y11;//向右平移d距离构造另外两个点
        x4 = x1 + d; y4 = y2;
        return true;
    }
    if (x1 != x2) {//水平线段
        const int d = abs(x1 - x2);
        x3 = x1; y3 = y11 + d;//向上平移d距离构造另外两个点
        x4 = x2; y4 = y2 + d;
        return true;
    }
    return false;
}

int main() {
    fast;
    cin >> x1 >> y11 >> x2 >> y2;
    if (ok()) cout << x3 << ' ' << y3 << ' ' << x4 << ' ' << y4 << '\n';
    else cout << "-1\n";
    return 0;
}